#ifndef FACE_RECOGNIZER_H
#define FACE_RECOGNIZER_H

#define EUCLIDIAN_DISTANCE      0
#define MAHALANOBIS_DISTANCE    1

#define DEFAULT_TRAINING_DATA_FILE  "trainingData.xml"
#define AVERAGE_IMAGE_FILE          "outAverageImage.pgm"
#define EIGENFACES_IMAGE_FILE       "outEigenfacesImage.pgm"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <set>
#include <vector>

#include <opencv2/opencv.hpp>

#include "my_eigen_face_recognizer.h"

#define IN
#define OUT

using namespace cv;
using namespace std;

class face_recognizer{

// Construction & Destruction
public:
    face_recognizer();

   ~face_recognizer();

    bool load_training_data(const char *filename);
    void predict(const char *imgfile, OUT int &label, OUT double &confidence);
    void train(const char *trainlist);
    void train(InputArrayOfArrays src, InputArray labels);
    void save(const char *savepath);

private:

    Ptr<my_eigen_face_recognizer> model;
};

#endif // FACE_RECOGNIZER_H
