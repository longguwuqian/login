/*
 * File:   recognizer.cpp
 * Author: Octavian Sima
 *
 * recognizer module implementation
 */

#include "face_recognizer.h"

face_recognizer::face_recognizer() {
    this->model = create_my_eigen_face_recognizer();
}

face_recognizer::~face_recognizer()
{

}

bool face_recognizer::load_training_data(const char *filename)
{
    this->model->load(filename);
    return true;
}

void face_recognizer::predict(const char *imgfile, OUT int &label, OUT double &confidence)
{
    Mat img = imread(imgfile, CV_LOAD_IMAGE_GRAYSCALE);
    this->model->predict(img, label, confidence);
}

void face_recognizer::train(const char *trainlist)
{
    vector<Mat> images;
    vector<int> labels;
    char path[256];
    int id;
    //open file
    FILE *fp;
    fp = fopen(trainlist, "r");

    while (fscanf(fp, "%i %s", &id, path) == 2) {
        images.push_back(imread(path, CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(id);
    }
    this->model->train(images, labels);

    fclose(fp);
}

void face_recognizer::train(InputArrayOfArrays src, InputArray labels)
{
    this->model->train(src, labels);
}

void face_recognizer::save(const char *savepath)
{
    this->model->save(savepath);
}

