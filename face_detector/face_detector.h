#ifndef FACE_DETECTOR_H
#define FACE_DETECTOR_H

#include <iostream>
#include <cstdio>
#include "opencv2/opencv.hpp"
#include "BasicDataType.h"
#include "AffineTrans.h"

//图像大小
#define IMG_WIDTH 640
#define IMG_HEIGHT 480
//
#define NORMAL_FACE_LEFT_EYE_X 23
#define NORMAL_FACE_LEFT_EYE_Y 50
#define NORMAL_FACE_RIGHT_EYE_X 69
#define NORMAL_FACE_RIGHT_EYE_Y 50

#define MIN_FACE_WIDTH 92
#define MIN_FACE_HEIGHT 112

using namespace cv;
using namespace std;

typedef struct {
    int    x_left;
    int    y_left;
    int    x_right;
    int    y_right;
} cgt_eye;

typedef struct {
    int left;
    int top;
    int right;
    int bottom;
} cgt_rect;

typedef struct {
    int x;
    int y;
} s_point;

typedef struct {
    int xleft,yleft,xright,yright;
    float confidence;//50.0 to 100.0
} Cgt_Eye;

typedef struct {
    int left,right,top,bottom;
} Cgt_Rect;


class face_detector
{
public:
    int w, h;
    IplImage *input_img;
    IplImage *face_img;
    Cgt_Rect area;
    Cgt_Eye iris_point;
    unsigned char face_img_gray[MIN_FACE_HEIGHT * MIN_FACE_WIDTH];

    face_detector();
    void set_input_image(IplImage *img);
    IplImage *get_face_img();
    // 人脸检测 和 眼睛定位
    bool get_face_parameters();

    bool useSingleEyeClassifier;
    bool classifierInitialized;
    CascadeClassifier cascadeFace;
    CascadeClassifier cascadeEye, cascadeLeftEye, cascadeRightEye;
    String cascadeFaceName;
    String cascadeEyeName;
    String cascadeRightEyeName;
    String cascadeLeftEyeName;
};

#endif // FACE_DETECTOR_H
