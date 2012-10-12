#ifndef FACE_RECOGNITION_H
#define FACE_RECOGNITION_H

#include <iostream>
#include <cstdio>
#include "opencv2/opencv.hpp"

#include "face_recognition/AffineTrans.h"
#include "face_recognition/MatrixOper.h"
#include "face_recognition/MemoryOper.h"

#define MIN_FACE_WIDTH 64
#define MIN_FACE_HEIGHT 80
//图像大小
#define IMG_WIDTH 640
#define IMG_HEIGHT 480
//
#define NORMAL_FACE_LEFT_EYE_X 16
#define NORMAL_FACE_LEFT_EYE_Y 30
#define NORMAL_FACE_RIGHT_EYE_X 47
#define NORMAL_FACE_RIGHT_EYE_Y 30

using namespace cv;
using namespace std;

typedef unsigned char byte;

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

//////// weighted pca model
class PCAModel
{
public:
    int m_nPCADim; //pca dim
    int m_nRawDim; //original image dim
    double* m_pMeanVec; //mean feature vector
    double* m_pEigenVec; //pca projection matrix
    double* m_pWeightMat; //weight matrix for weighted pca
    double* m_pSVal; //eigen value of the pca model
    double* m_pInput;
    PCAModel()
    {
        m_nPCADim = 0;
        m_nRawDim = 0;
        m_pMeanVec = NULL;
        m_pEigenVec = NULL;
        m_pWeightMat = NULL;
        m_pSVal = NULL;
        m_pInput = NULL;
    }
    PCAModel(char* strModelPath)
    {
        FILE* fp = fopen(strModelPath,"rb");

        fread(&m_nPCADim, sizeof(int), 1, fp);
        fread(&m_nRawDim, sizeof(int), 1, fp);

        m_pMeanVec  = new double[m_nRawDim];
        m_pSVal = new double[m_nPCADim];
        m_pEigenVec = new double[m_nPCADim*m_nRawDim];
        m_pWeightMat = new double[MIN_FACE_HEIGHT*MIN_FACE_WIDTH];
        m_pInput = new double[MIN_FACE_HEIGHT*MIN_FACE_WIDTH];

        fread(m_pMeanVec, sizeof(double), m_nRawDim, fp);
        fread(m_pEigenVec, sizeof(double), m_nPCADim*m_nRawDim, fp);
        fread(m_pWeightMat, sizeof(double), MIN_FACE_HEIGHT*MIN_FACE_WIDTH, fp);
        fread(m_pSVal, sizeof(double), m_nPCADim, fp);

        fclose(fp);
    }
    void LoadModel(char* strmodelpath)
    {
        FILE* fp = fopen(strmodelpath,"rb");

        fread(&m_nPCADim, sizeof(int), 1, fp);
        fread(&m_nRawDim, sizeof(int), 1, fp);

        m_pMeanVec  = new double[m_nRawDim];
        m_pSVal = new double[m_nPCADim];
        m_pEigenVec = new double[m_nPCADim*m_nRawDim];
        m_pWeightMat = new double[MIN_FACE_HEIGHT*MIN_FACE_WIDTH];
        m_pInput = new double[MIN_FACE_HEIGHT*MIN_FACE_WIDTH];

        fread(m_pMeanVec, sizeof(double), m_nRawDim, fp);
        fread(m_pEigenVec, sizeof(double), m_nPCADim*m_nRawDim, fp);
        fread(m_pWeightMat, sizeof(double), MIN_FACE_HEIGHT*MIN_FACE_WIDTH, fp);
        fread(m_pSVal, sizeof(double), m_nPCADim, fp);
        fclose(fp);
    }
    void ComputePCACoeff(byte* pInput, double* pOutput)
    {
        int i,j;
        for(i=0; i<m_nRawDim; i++)
        {
            m_pInput[i] = pInput[i] * m_pWeightMat[i];
            m_pInput[i] -= m_pMeanVec[i];
        }
        for(i=0; i<m_nPCADim; i++)
        {
            pOutput[i] = 0;
            for(j=0; j<m_nRawDim; j++)
            {
                pOutput[i] += m_pInput[j] * m_pEigenVec[i*m_nRawDim+j];
            }
            pOutput[i] = pOutput[i] / m_pSVal[i];
        }
    }
    ~PCAModel()
    {
        delete [] m_pMeanVec;
        delete [] m_pEigenVec;
        delete [] m_pWeightMat;
        delete [] m_pSVal;
        delete [] m_pInput;
    }
};

////////
class face_recognition
{
private:
int hihlkhkihl;
public:
    face_recognition();
};

double* LoadGalleryData(int &nGalleryPeopleNum, PCAModel* pPCAModel, char* strPeopleNumFile, char* strGalleryModel)
{
    FILE* fp = fopen(strPeopleNumFile,"r");
    fscanf(fp, "%d", &nGalleryPeopleNum);
    fclose(fp);

    fp = fopen(strGalleryModel, "rb");
    double* pGalleryFacePCACoeff = new double[pPCAModel->m_nPCADim*nGalleryPeopleNum];
    fread(pGalleryFacePCACoeff, pPCAModel->m_nPCADim*nGalleryPeopleNum, sizeof(double), fp);
    fclose(fp);

    return pGalleryFacePCACoeff;
}
// Load模型
int InitialFunc(PCAModel* pPCAModel, double* pGalleryFacePCACoeff, int &nGalleryPeopleNum)
{
    pPCAModel = new PCAModel("PCAModel.bin"); //读取人脸识别PCA模型
    pGalleryFacePCACoeff = LoadGalleryData(nGalleryPeopleNum, pPCAModel, "GalleryPeopleNum.ini", "GalleryPCACoeff.bin"); //读取罪犯人脸库
}

// 释放模型
int ReleaseFunc(PCAModel* pPCAModel, byte* pGalleryFacePCACoeff)
{
    delete pPCAModel;
    delete [] pGalleryFacePCACoeff;
}
///////////////////////////
double ComputeVecSim(double* pA, double* pB, int nDim)
{
    int i;
    double normA = 0;
    double normB = 0;
    double dotMul = 0;
    for(i=0; i<nDim; i++)
    {
        normA += pA[i]*pA[i];
    }
    normA = sqrt(normA);

    for(i=0; i<nDim; i++)
    {
        normB += pB[i]*pB[i];
    }

    normB = sqrt(normB);

    for(i=0; i<nDim; i++)
    {
        dotMul += pA[i]*pB[i];
    }

    return dotMul/(normA*normB);
}
/////////////////////////////////////////////////

// nPeopleID：从0开始
// pPCAModel：PCA模型 由InitialFunc得到
// pFaceImgGray：输入的Face，必须是灰度图 由Face Detection和Eye Location得到
// pGalleryFacePCACoeff：已经建模的人脸库中的Face的PCA系数 由InitialFunc得到
int FaceRecognition(PCAModel* pPCAModel, byte* pFaceImgGray, double* pGalleryFacePCACoeff, int nPeopleID, int nGalleryPeopleNum,double dThreshold)
{
    if(nPeopleID >= nGalleryPeopleNum)
    {
        return -1;
    }
    double* pInputFacePCACoeff = new double[pPCAModel->m_nPCADim];
    pPCAModel->ComputePCACoeff(pFaceImgGray, pInputFacePCACoeff);
    double curSim = ComputeVecSim(pInputFacePCACoeff, &pGalleryFacePCACoeff[nPeopleID*pPCAModel->m_nPCADim], pPCAModel->m_nPCADim);
    if (curSim >= dThreshold)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 根据眼睛定位的结果从原始图像中crop出face image
void GetFaceImg(Cgt_Eye* irisPoint, byte* pGrayImg, byte* pFaceImgGray)
{
        double OriginalFaceEyePosition[4];
        double NormalFaceEyePosition[4];
        double AffineMatrix[4];

        OriginalFaceEyePosition[0] = irisPoint->xleft;
        OriginalFaceEyePosition[1] = irisPoint->yleft;
        OriginalFaceEyePosition[2] = irisPoint->xright;
        OriginalFaceEyePosition[3] = irisPoint->yright;

        NormalFaceEyePosition[0] = NORMAL_FACE_LEFT_EYE_X;
        NormalFaceEyePosition[1] = NORMAL_FACE_LEFT_EYE_Y;
        NormalFaceEyePosition[2] = NORMAL_FACE_RIGHT_EYE_X;
        NormalFaceEyePosition[3] = NORMAL_FACE_RIGHT_EYE_Y;

        GetAffineMatrix_Pts(AffineMatrix, NormalFaceEyePosition, OriginalFaceEyePosition, 2);
        double dR = sqrt(AffineMatrix[0]*AffineMatrix[0] + AffineMatrix[1]*AffineMatrix[1]);

        s_Point NormReferPt;
        s_Point OriReferPt;
        NormReferPt.x = NORMAL_FACE_LEFT_EYE_X;
        NormReferPt.y = NORMAL_FACE_LEFT_EYE_Y;
        OriReferPt.x = OriginalFaceEyePosition[0];
        OriReferPt.y = OriginalFaceEyePosition[1];

        float cosAngle = AffineMatrix[0] / dR;
        float sinAngle = AffineMatrix[1] / dR;


        AffineTranImg_CenterSizeAngle_1D(pFaceImgGray, MIN_FACE_WIDTH, MIN_FACE_HEIGHT, NormReferPt,
            pGrayImg, IMG_WIDTH, IMG_HEIGHT, OriReferPt, sinAngle, cosAngle, dR, 1, 2);

}

// 人脸检测 和 眼睛定位
bool GetFaceParameters(byte* gray_image,int w,int h,Cgt_Rect* area,Cgt_Eye* irisPoint)
{
    static CascadeClassifier cascadeFace;
    static CascadeClassifier cascadeEye, cascadeLeftEye, cascadeRightEye;
    String cascadeFaceName = "haarcascade_frontalface_alt.xml";
    String cascadeEyeName = "haarcascade_eye.xml";
//String cascadeEyeName = "haarcascade_eye_tree_eyeglasses.xml";
    String cascadeRightEyeName = "haarcascade_lefteye_2splits.xml"; //这个左右眼的分类器似乎是针对镜像的人脸图像，这里需要反过来用
    String cascadeLeftEyeName = "haarcascade_righteye_2splits.xml";
    bool useSingleEyeClassifier=true;

    bool nRetCode=false;
    vector<Rect> faces;
    static bool classifierInitialized = false;

    if(classifierInitialized==false) {
        //load classifier
        if( !cascadeFace.load( cascadeFaceName ) ) {
            //MessageBox(NULL, "Could not load face classifier cascade!", "Error", MB_OK);
            exit(1);
        }
        if(useSingleEyeClassifier) {
            if( !cascadeEye.load( cascadeEyeName ) ) {
                // MessageBox(NULL, "Could not load eye classifier cascade!", "Error", MB_OK);
                exit(1);
            }
        } else {
            if( !cascadeLeftEye.load( cascadeLeftEyeName ) ) {
                // MessageBox(NULL, "Could not load left eye classifier cascade!", "Error", MB_OK);
                exit(1);
            }
            if( !cascadeRightEye.load( cascadeRightEyeName ) ) {
                // MessageBox(NULL, "Could not load right eye classifier cascade!", "Error", MB_OK);
                exit(1);
            }
        }

        classifierInitialized= true;
    }
// 似乎刚打开摄像头时可能w/h<=0，在这里判断一下。
    if( (gray_image == NULL) || (w<=0) || (h<=0) )
        return false;
//将输入的gray_image转换为IplImage类型，然后转为Mat
    IplImage* IplOrigImage = cvCreateImageHeader(cvSize(w,h), IPL_DEPTH_8U, 1);
//IplOrigImage->origin = ~IplOrigImage->origin;  //origin控制图像自上而下还是自下而上
    cvSetData(IplOrigImage, gray_image, w*1);
    Mat matImg = IplOrigImage;
//imshow("flipped img", matImg);
//cvWaitKey(0);
//cvDestroyWindow("flipped img");

    cascadeFace.detectMultiScale( matImg, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    if(faces.empty() == false) {
        //取最大的脸
        Rect largestFace;
        largestFace.width=0;
        largestFace.height=0;
        for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++) {
            if( (r->width*r->height) > (largestFace.width*largestFace.height) )
                largestFace = *r;
        }

        // 将最大人脸区域赋给area
        area->left  = largestFace.x;
        area->right  = largestFace.x + largestFace.width;
        area->top  = largestFace.y;
        area->bottom = largestFace.y + largestFace.height;
        ///////////针对最大的脸检测人眼////////////////////////////////
        Mat smallImgROI;
        Rect eyeArea = largestFace;
        eyeArea.height = eyeArea.height/2; //仅对人脸的上半部分检测人眼，以减少错误率
        smallImgROI = matImg(eyeArea);
        Rect leftEyeRect(0,0,0,0), rightEyeRect(0,0,0,0);
        if(useSingleEyeClassifier) {
            // 使用双眼一起的单分类器检测眼
            vector<Rect> eyes;
            cascadeEye.detectMultiScale( smallImgROI, eyes, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(20, 20) );
            if(eyes.size()>=2) { //必须至少有两只眼被检出
                vector<Rect>::const_iterator nr = eyes.begin();
                leftEyeRect = *nr;
                nr++;
                rightEyeRect = *nr;
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

        irisPoint->xleft = cvRound(largestFace.x + leftEyeRect.x + leftEyeRect.width*0.5);  //左眼中心的x坐标
        irisPoint->yleft = cvRound(largestFace.y + leftEyeRect.y + leftEyeRect.height*0.5);  //左眼中心的y坐标
        irisPoint->xright = cvRound(largestFace.x + rightEyeRect.x + rightEyeRect.width*0.5);  //右眼中心的x坐标
        irisPoint->yright = cvRound(largestFace.y + rightEyeRect.y + rightEyeRect.height*0.5); //右眼中心的y坐标
        nRetCode = true;
        //对眼睛的后期验证：
        //不允许左眼在右眼右边
        if(irisPoint->xleft >= irisPoint->xright )
            nRetCode = false;
        //不允许眼睛在边界（由于，初始化的值为0，这也意味着如果少于两个眼检测出来，则认为检测失败）
        if( (irisPoint->xleft==0) || (irisPoint->yleft==0) ||(irisPoint->xright==0) || (irisPoint->yright==0) )
            nRetCode = false;
        //不允许两只眼上下倾斜过多（也防止一些误检）
        if(abs(irisPoint->yright-irisPoint->yleft) > (largestFace.width/3) )
            nRetCode = false;
        //不允许两只眼左右间距小于1/4人脸宽度（也防止一些误检）
        if(abs(irisPoint->xright-irisPoint->xleft) < (largestFace.width/4) )
            nRetCode = false;
        // 输入的gray_image水平是反转的，虽然并不影响这个函数的执行，
        // 但是为了达到左眼是右眼，右眼是左眼，在最后需要把左右眼对调一下。
        int tmpSwap;
        tmpSwap = irisPoint->xleft;
        irisPoint->xleft = irisPoint->xright;
        irisPoint->xright = tmpSwap;
        tmpSwap = irisPoint->yleft;
        irisPoint->yleft = irisPoint->yright;
        irisPoint->yright = tmpSwap;
        //画出框到的人脸，验证调试用
        //Point left_top, right_bottom;
        //left_top.x = area->left;
        //left_top.y = area->top;
        //right_bottom.x = area->right;
        //right_bottom.y = area->bottom;
        //rectangle(matImg, left_top, right_bottom, CV_RGB(0,255,0), 2, 8, 0);
        //cv::imshow("face area", matImg);
        //cvWaitKey(0);
        //cvDestroyWindow("face area");

    }

    return nRetCode;
}


#endif // FACE_RECOGNITION_H
