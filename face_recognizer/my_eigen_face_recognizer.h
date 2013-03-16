#ifndef MY_EIGEN_FACE_RECOGNIZER_H
#define MY_EIGEN_FACE_RECOGNIZER_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/internal.hpp>

#define IN
#define OUT

using namespace std;
using namespace cv;

CV_EXPORTS_W Ptr<FaceRecognizer> create_my_eigen_face_recognizer(int num_components = 0, double threshold = DBL_MAX);

class my_eigen_face_recognizer : public FaceRecognizer
{
private:
    int _num_components;
    double _threshold;
    vector<Mat> _projections;
    Mat _labels;
    Mat _eigenvectors;
    Mat _eigenvalues;
    Mat _mean;
public:
    using FaceRecognizer::save;
    using FaceRecognizer::load;

    my_eigen_face_recognizer(int n = 0, double t = DBL_MAX) :
        _num_components(n), _threshold(t) {}
    my_eigen_face_recognizer(InputArrayOfArrays src, InputArray labels, int n = 0, double t = DBL_MAX) :
        _num_components(n), _threshold(t) {
        train(src, labels);
    }

    void train(InputArrayOfArrays src, InputArray _labels);
    int predict(InputArray src) const;
    void predict(InputArray src, int &label, double &dist) const;
    void load(const FileStorage &fs);
    void save(FileStorage &fs) const;
    AlgorithmInfo* info() const;


    // LOAD ALL
    void load_num_components(int n);
    void load_mean(int cols, double data[]);
    void load_labels(int cols, int data[]);
    void load_eigen_vectors(int rows, int cols, double data[]);
    void load_eigen_values(int rows, double data[]);
    void load_projections(int num, int cols, double data[]);

    //SAVE ALL
    void save_num_components(OUT int &n) const;
    void save_mean(OUT int &cols, OUT double *data) const;
    void save_labels(OUT int &cols, OUT double *data) const;
    void save_eigen_vectors(OUT int &rows, OUT int &cols, OUT double *data) const;
    void save_eigen_values(OUT int &rows, OUT double *data) const;
    void save_projections(OUT int &num, OUT int &col, OUT double *data) const;

};

#endif // MY_EIGEN_FACE_RECOGNIZER_H
