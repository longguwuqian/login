#include "face_detector.h"
#include <cstdio>

face_detector::face_detector()
{
    this->input_img = NULL;

    cascadeFaceName = "haarcascade_frontalface_alt2.xml";
    cascadeEyeName = "haarcascade_eye.xml";
    //cascadeEyeName = "haarcascade_eye_tree_eyeglasses.xml";
    cascadeRightEyeName = "haarcascade_lefteye_2splits.xml"; //这个左右眼的分类器似乎是针对镜像的人脸图像，这里需要反过来用
    cascadeLeftEyeName = "haarcascade_righteye_2splits.xml";

    useSingleEyeClassifier = true;
    classifierInitialized = false;

    if(classifierInitialized == false) {
        //load classifier
        if(!cascadeFace.load( cascadeFaceName)) {
            fprintf(stderr, "Could not load face classifier cascade!");
            exit(1);
        }
        if(useSingleEyeClassifier) {
            if(!cascadeEye.load( cascadeEyeName)) {
                fprintf(stderr, "Could not load eye classifier cascade!");
                exit(1);
            }
        } else {
            if(!cascadeLeftEye.load(cascadeLeftEyeName)) {
                fprintf(stderr, "Could not load left eye classifier cascade!");
                exit(1);
            }
            if(!cascadeRightEye.load(cascadeRightEyeName)) {
                fprintf(stderr, "Could not load right eye classifier cascade!");
                exit(1);
            }
        }
        classifierInitialized = true;
    }

}
void face_detector::set_input_image(IplImage *img)
{
    this->input_img = img;
}

IplImage *face_detector::get_face_img()
{
//    double OriginalFaceEyePosition[4];
//    double NormalFaceEyePosition[4];
//    double AffineMatrix[4];

//    OriginalFaceEyePosition[0] = iris_point.xleft;
//    OriginalFaceEyePosition[1] = iris_point.yleft;
//    OriginalFaceEyePosition[2] = iris_point.xright;
//    OriginalFaceEyePosition[3] = iris_point.yright;

//    NormalFaceEyePosition[0] = NORMAL_FACE_LEFT_EYE_X;
//    NormalFaceEyePosition[1] = NORMAL_FACE_LEFT_EYE_Y;
//    NormalFaceEyePosition[2] = NORMAL_FACE_RIGHT_EYE_X;
//    NormalFaceEyePosition[3] = NORMAL_FACE_RIGHT_EYE_Y;

//    GetAffineMatrix_Pts(AffineMatrix, NormalFaceEyePosition, OriginalFaceEyePosition, 2);
//    double dR = sqrt(AffineMatrix[0]*AffineMatrix[0] + AffineMatrix[1]*AffineMatrix[1]);

//    s_Point NormReferPt;
//    s_Point OriReferPt;
//    NormReferPt.x = NORMAL_FACE_LEFT_EYE_X;
//    NormReferPt.y = NORMAL_FACE_LEFT_EYE_Y;
//    OriReferPt.x = OriginalFaceEyePosition[0];
//    OriReferPt.y = OriginalFaceEyePosition[1];

//    float cosAngle = AffineMatrix[0] / dR;
//    float sinAngle = AffineMatrix[1] / dR;


//    AffineTranImg_CenterSizeAngle_1D(face_img_gray, MIN_FACE_WIDTH, MIN_FACE_HEIGHT, NormReferPt,
//                                     (unsigned char*)input_img->imageDataOrigin, IMG_WIDTH, IMG_HEIGHT, OriReferPt, sinAngle, cosAngle, dR, 1, 2);
    face_img = cvCreateImage(cvSize(MIN_FACE_WIDTH, MIN_FACE_HEIGHT), IPL_DEPTH_8U, 1);
//    cvSetData(face_img, face_img_gray, MIN_FACE_WIDTH);

//    return face_img;

    CvRect roi = cvRect(this->area.left, this->area.top, this->area.right - this->area.left, this->area.bottom - this->area.top);
    cvSetImageROI(this->input_img, roi);
    cvResize(this->input_img, this->face_img);
    cvResetImageROI(this->input_img);
    return this->face_img;
}

bool face_detector::get_face_parameters()
{
    bool nRetCode = false;
    vector<Rect> faces;

    IplImage *orig_img = cvCloneImage(input_img);
    Mat matImg = orig_img;
    cascadeFace.detectMultiScale(matImg, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(25, 25));

    if(faces.empty() == false) {
        //取最大的脸
        Rect largestFace;
        largestFace.width=0;
        largestFace.height=0;
        for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++) {
            if( (r->width * r->height) > (largestFace.width * largestFace.height) )
                largestFace = *r;
        }

        // 将最大人脸区域赋给area
        area.left  = largestFace.x;
        area.right  = largestFace.x + largestFace.width;
        area.top  = largestFace.y;
        area.bottom = largestFace.y + largestFace.height;
        /*********/
        printf("left:%d, right: %d, top: %d, bottom: %d\n", area.left, area.right, area.top, area.bottom);
        /*********/
        ///////////针对最大的脸检测人眼////////////////////////////////
        Mat smallImgROI;
        Rect eyeArea = largestFace;
        eyeArea.height = eyeArea.height/1.2; //仅对人脸的上半部分检测人眼，以减少错误率 //调整一下参数，只对上半部分有时检测不出来
        smallImgROI = matImg(eyeArea);
        Rect leftEyeRect(0,0,0,0), rightEyeRect(0,0,0,0);
        if(useSingleEyeClassifier) {
            // 使用双眼一起的单分类器检测眼
            vector<Rect> eyes;
            cascadeEye.detectMultiScale( smallImgROI, eyes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
            if(eyes.size()>=2) { //必须至少有两只眼被检出
                vector<Rect>::const_iterator nr = eyes.begin();
                leftEyeRect = *nr;
                nr++;
                rightEyeRect = *nr;
            } else {
                fprintf(stderr, "必须至少有两只眼被检出!\n");
            }
        } else {
            //使用左右眼分开的两个分类器检测眼
            vector<Rect> leftEye, rightEye;
            cascadeLeftEye.detectMultiScale( smallImgROI, leftEye, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(20, 20) );
            cascadeRightEye.detectMultiScale( smallImgROI, rightEye, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(20, 20) );
            if(leftEye.empty() == false)
                leftEyeRect = *(leftEye.begin());
            if(rightEye.empty() == false)
                rightEyeRect = *(rightEye.begin());
        }

        iris_point.xleft = cvRound(largestFace.x + leftEyeRect.x + leftEyeRect.width*0.5);  //左眼中心的x坐标
        iris_point.yleft = cvRound(largestFace.y + leftEyeRect.y + leftEyeRect.height*0.5);  //左眼中心的y坐标
        iris_point.xright = cvRound(largestFace.x + rightEyeRect.x + rightEyeRect.width*0.5);  //右眼中心的x坐标
        iris_point.yright = cvRound(largestFace.y + rightEyeRect.y + rightEyeRect.height*0.5); //右眼中心的y坐标
        nRetCode = true;
        //对眼睛的后期验证：
        //不允许左眼在右眼右边
//        if(iris_point.xleft >= iris_point.xright )
//            fprintf(stderr, "11111111111"), nRetCode = false;
        //不允许眼睛在边界（由于，初始化的值为0，这也意味着如果少于两个眼检测出来，则认为检测失败）
        if( (iris_point.xleft==0) || (iris_point.yleft==0) ||(iris_point.xright==0) || (iris_point.yright==0) )
            fprintf(stderr, "22222222222222222\n"), nRetCode = false;
        //不允许两只眼上下倾斜过多（也防止一些误检）
        if(abs(iris_point.yright-iris_point.yleft) > (largestFace.width/3) )
            fprintf(stderr, "3333333333333333\n"), nRetCode = false;
        //不允许两只眼左右间距小于1/4人脸宽度（也防止一些误检）
        if(abs(iris_point.xright-iris_point.xleft) < (largestFace.width/4) )
            fprintf(stderr, "4444444444\n"), nRetCode = false;
        // 输入的gray_image水平是反转的，虽然并不影响这个函数的执行，
        // 但是为了达到左眼是右眼，右眼是左眼，在最后需要把左右眼对调一下。
//        int tmpSwap;
//        tmpSwap = iris_point.xleft;
//        iris_point.xleft = iris_point.xright;
//        iris_point.xright = tmpSwap;
//        tmpSwap = iris_point.yleft;
//        iris_point.yleft = iris_point.yright;
//        iris_point.yright = tmpSwap;
        /******************/
        printf("xleft: %d, xright: %d, yleft: %d, yright: %d\n", iris_point.xleft, iris_point.xright, iris_point.yleft, iris_point.yright);
        /******************/
        //画出框到的人脸，验证调试用
        Point left_top, right_bottom;
        left_top.x = area.left;
        left_top.y = area.top;
        right_bottom.x = area.right;
        right_bottom.y = area.bottom;
        rectangle(matImg, left_top, right_bottom, CV_RGB(0,255,0), 2, 8, 0);
        left_top.x = iris_point.xleft;
        left_top.y = iris_point.yleft;
        right_bottom.x = left_top.x;
        right_bottom.y = left_top.y;
        rectangle(matImg, left_top, right_bottom, CV_RGB(90, 255, 0), 2, 8, 0);
        left_top.x = iris_point.xright;
        left_top.y = iris_point.yright;
        right_bottom.x = left_top.x;
        right_bottom.y = left_top.y;
        rectangle(matImg, left_top, right_bottom, CV_RGB(0, 255, 0), 2, 8, 0);
        cv::imshow("face area", matImg);
        cvWaitKey(0);
        cvDestroyWindow("face area");
    }
    cvReleaseImage(&orig_img);
    return nRetCode;
}

