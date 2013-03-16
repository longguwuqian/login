#include "my_eigen_face_recognizer.h"


// Reads a sequence from a FileNode::SEQ with type _Tp into a result vector.
template<typename _Tp>
inline void readFileNodeList(const FileNode& fn, vector<_Tp>& result) {
    if (fn.type() == FileNode::SEQ) {
        for (FileNodeIterator it = fn.begin(); it != fn.end();) {
            _Tp item;
            it >> item;
            result.push_back(item);
        }
    }
}

// Writes the a list of given items to a cv::FileStorage.
template<typename _Tp>
inline void writeFileNodeList(FileStorage& fs, const string& name,
                              const vector<_Tp>& items) {
    // typedefs
    typedef typename vector<_Tp>::const_iterator constVecIterator;
    // write the elements in item to fs
    fs << name << "[";
    for (constVecIterator it = items.begin(); it != items.end(); ++it) {
        fs << *it;
    }
    fs << "]";
}


static Mat asRowMatrix(InputArrayOfArrays src, int rtype, double alpha=1, double beta=0) {
    // make sure the input data is a vector of matrices or vector of vector
    if(src.kind() != _InputArray::STD_VECTOR_MAT && src.kind() != _InputArray::STD_VECTOR_VECTOR) {
        string error_message = "The data is expected as InputArray::STD_VECTOR_MAT (a std::vector<Mat>) or _InputArray::STD_VECTOR_VECTOR (a std::vector< vector<...> >).";
        CV_Error(CV_StsBadArg, error_message);
    }
    // number of samples
    size_t n = src.total();
    // return empty matrix if no matrices given
    if(n == 0)
        return Mat();
    // dimensionality of (reshaped) samples
    size_t d = src.getMat(0).total();
    // create data matrix
    Mat data((int)n, (int)d, rtype);
    // now copy data
    for(unsigned int i = 0; i < n; i++) {
        // make sure data can be reshaped, throw exception if not!
        if(src.getMat(i).total() != d) {
            string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src.getMat(i).total());
            CV_Error(CV_StsBadArg, error_message);
        }
        // get a hold of the current row
        Mat xi = data.row(i);
        // make reshape happy by cloning for non-continuous matrices
        if(src.getMat(i).isContinuous()) {
            src.getMat(i).reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        } else {
            src.getMat(i).clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        }
    }
    return data;
}

//------------------------------------------------------------------------------
// FaceRecognizer
//------------------------------------------------------------------------------
void FaceRecognizer::save(const string& filename) const {
    FileStorage fs(filename, FileStorage::WRITE);
    if (!fs.isOpened())
        CV_Error(CV_StsError, "File can't be opened for writing!");
    this->save(fs);
    fs.release();
}

void FaceRecognizer::load(const string& filename) {
    FileStorage fs(filename, FileStorage::READ);
    if (!fs.isOpened())
        CV_Error(CV_StsError, "File can't be opened for writing!");
    this->load(fs);
    fs.release();
}

//------------------------------------------------------------------------------
// my_eigen_face_recognizer
//------------------------------------------------------------------------------

void my_eigen_face_recognizer::train(InputArrayOfArrays src, InputArray local_labels) {
    if(src.total() == 0) {
        string error_message = format("Empty training data was given. You'll need more than one sample to learn a model.");
        CV_Error(CV_StsBadArg, error_message);
    } else if(local_labels.getMat().type() != CV_32SC1) {
        string error_message = format("Labels must be given as integer (CV_32SC1). Expected %d, but was %d.", CV_32SC1, local_labels.type());
        CV_Error(CV_StsBadArg, error_message);
    }
    // make sure data has correct size
    if(src.total() > 1) {
        for(int i = 1; i < static_cast<int>(src.total()); i++) {
            if(src.getMat(i-1).total() != src.getMat(i).total()) {
                string error_message = format("In the Eigenfaces method all input samples (training images) must be of equal size! Expected %d pixels, but was %d pixels.", src.getMat(i-1).total(), src.getMat(i).total());
                CV_Error(CV_StsUnsupportedFormat, error_message);
            }
        }
    }
    // get labels
    Mat labels = local_labels.getMat();
    //按行观察
    Mat data = asRowMatrix(src, CV_64FC1);

    // number of samples
    int n = data.rows;
    // assert there are as much samples as labels
    if(static_cast<int>(labels.total()) != n) {
        string error_message = format("The number of samples (src) must equal the number of labels (labels)! len(src)=%d, len(labels)=%d.", n, labels.total());
        CV_Error(CV_StsBadArg, error_message);
    }
    // clear existing model data
    this->_labels.release();
    this->_projections.clear();
    // clip number of components to be valid
    if((this->_num_components <= 0) || (this->_num_components > n))
        this->_num_components = n;

    // perform the PCA
    PCA pca(data, Mat(), CV_PCA_DATA_AS_ROW, this->_num_components);
    // copy the PCA results
    this->_mean = pca.mean.reshape(1,1); // store the mean vector
    this->_eigenvalues = pca.eigenvalues.clone(); // eigenvalues by row
    transpose(pca.eigenvectors, this->_eigenvectors); // eigenvectors by column
    // store labels for prediction
    this->_labels = labels.clone();
    // save projections
    for(int sampleIdx = 0; sampleIdx < data.rows; sampleIdx++) {
        Mat p = subspaceProject(this->_eigenvectors, this->_mean, data.row(sampleIdx));
        this->_projections.push_back(p);
    }
}


void my_eigen_face_recognizer::predict(InputArray _src, int &minClass, double &minDist) const {
    // get data
    Mat src = _src.getMat();
    // make sure the user is passing correct data
    if(this->_projections.empty()) {
        // throw error if no data (or simply return -1?)
        string error_message = "This Eigenfaces model is not computed yet. Did you call Eigenfaces::train?";
        CV_Error(CV_StsError, error_message);
    } else if(this->_eigenvectors.rows != static_cast<int>(src.total())) {
        // check data alignment just for clearer exception messages
        string error_message = format("Wrong input image size. Reason: Training and Test images must be of equal size! Expected an image with %d elements, but got %d.", _eigenvectors.rows, src.total());
        CV_Error(CV_StsBadArg, error_message);
    }
    // project into PCA subspace
    Mat q = subspaceProject(this->_eigenvectors, this->_mean, src.reshape(1,1));
    minDist = DBL_MAX;
    minClass = -1;
    for(size_t sampleIdx = 0; sampleIdx < this->_projections.size(); sampleIdx++) {
        double dist = norm(this->_projections[sampleIdx], q, NORM_L2);
        if((dist < minDist) && (dist < this->_threshold)) {
            minDist = dist;
            minClass = this->_labels.at<int>((int)sampleIdx);
        }
    }
}

int my_eigen_face_recognizer::predict(InputArray src) const {
    int label;
    double dummy;
    predict(src, label, dummy);
    return label;
}

void my_eigen_face_recognizer::load(const FileStorage& fs) {
    //read matrices
    fs["num_components"] >> _num_components;
    fs["mean"] >> _mean;
    fs["eigenvalues"] >> _eigenvalues;
    fs["eigenvectors"] >> _eigenvectors;
    // read sequences
    readFileNodeList(fs["projections"], _projections);
    fs["labels"] >> _labels;
}

void my_eigen_face_recognizer::save(FileStorage& fs) const {
    // write matrices
    fs << "num_components" << _num_components;
    fs << "mean" << _mean;
    fs << "eigenvalues" << _eigenvalues;
    fs << "eigenvectors" << _eigenvectors;
    // write sequences
    writeFileNodeList(fs, "projections", _projections);
    fs << "labels" << _labels;
}

Ptr<FaceRecognizer> create_my_eigen_face_recognizer(int num_components, double threshold)
{
    return new my_eigen_face_recognizer(num_components, threshold);
}

CV_INIT_ALGORITHM(my_eigen_face_recognizer, "FaceRecognizer.my_eigen_face_recognizer",
                  obj.info()->addParam(obj, "ncomponents", obj._num_components);
                  obj.info()->addParam(obj, "threshold", obj._threshold);
                  obj.info()->addParam(obj, "projections", obj._projections, true);
                  obj.info()->addParam(obj, "labels", obj._labels, true);
                  obj.info()->addParam(obj, "eigenvectors", obj._eigenvectors, true);
                  obj.info()->addParam(obj, "eigenvalues", obj._eigenvalues, true);
                  obj.info()->addParam(obj, "mean", obj._mean, true));


//-------------------
// LOAD ALL
//-------------------

void my_eigen_face_recognizer::load_num_components(int n)
{
    this->_num_components = n;
}

void my_eigen_face_recognizer::load_labels(int cols, int data[])
{
    this->_labels.release();
    this->_labels.create(1, cols, CV_32SC1);
    for (int i = 0; i < cols; i++) {
        this->_labels.at<int>(1, i) = data[i];
    }
}

void my_eigen_face_recognizer::load_mean(int cols, double data[])
{
    this->_mean.release();
    this->_mean.create(1, cols, CV_64FC1);
    for (int i = 0; i < cols; i++) {
        this->_labels.at<double>(1, i) = data[i];
    }
}

void my_eigen_face_recognizer::load_eigen_values(int rows, double data[])
{
    this->_eigenvalues.release();
    this->_eigenvalues.create(rows, 1, CV_64FC1);
    for (int i = 0; i < rows; i++) {
        this->_eigenvalues.at<double>(i, 1) = data[i];
    }
}

void my_eigen_face_recognizer::load_eigen_vectors(int rows, int cols, double data[])
{
    this->_eigenvalues.release();
    this->_eigenvalues.create(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            this->_eigenvectors.at<double>(i, j) = data[j + i * cols];
        }
    }
}

void my_eigen_face_recognizer::load_projections(int num, int cols, double data[])
{
    this->_projections.clear();
    for (int i = 0; i < num; i++) {
        Mat m = Mat(1, cols, CV_64FC1);
        for (int j = 0; j < cols; j++) {
            m.at<double>(1, j) = data[j + i * cols];
        }
        this->_projections.push_back(m);
    }
}












