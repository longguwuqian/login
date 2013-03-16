#pragma once
#include "MemoryOper.h"

# define        sgn(A)        ((A)<0?-1:1)

//#define USE_OPENCV

//#define  MATRIXFLOAT
#ifdef  MATRIXFLOAT
typedef float MatrixType;
#ifdef USE_OPENCV
#define CV_DATA_TYPE CV_32FC1
#endif
#endif

#define MATRIXDOUBLE
#ifdef MATRIXDOUBLE
typedef double MatrixType;
#ifdef USE_OPENCV
#define  CV_DATA_TYPE CV_64FC1
#endif
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifdef USE_OPENCV

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#pragma comment(lib, "cv.lib")
#pragma comment(lib, "cxcore.lib")
#pragma comment(lib, "highgui.lib")
#endif

typedef enum mul_ero{WandHnotmatch, CannotCreateMatHead, Success};
typedef enum Invert_type{Matrix_LU, Matrix_SUV, Matrix_SUV_SYM};

/*************************************************************************************************/
/* 矩阵加法 ,   dstMatrix =  srcMatrix1 + srcMatrix2,矩阵为width列，height行                     */
/*************************************************************************************************/
bool MatrixAdd( OUT MatrixType *dstData, MatrixType *srcData1, MatrixType *srcData2, const int width, const int height);

/*************************************************************************************************/
/* 矩阵减法 ,   dstMatrix =  srcMatrix1 + srcMatrix2,矩阵为width列，height行                     */
/*************************************************************************************************/
bool MatrixSub(OUT MatrixType *dstData,  MatrixType *srcData1, MatrixType *srcData2, const int width, const int height); 

bool MatrixTransPos(OUT MatrixType *pDstData, MatrixType *pSrcData, int w, int h);
/*bool MatrixTransPos(OUT MatrixType *pDstData, MatrixType *pSrcData, const int w, const int h);*/

/*************************************************************************************************/
/* 矩阵乘法 ,   dstMatrix为矩阵C， srcMatrix1为h1 * w1 维矩阵A，srcMatrix2为h2 *w2维矩阵B        */
/*       C = AB,C为h1 * w2维矩阵                                                                 */
/*************************************************************************************************/
int MatrixMul(OUT MatrixType *dstData, MatrixType *srcData1, const int w1,const int h1, 
			  MatrixType *srcData2, const int w2, const int h2);

/************************************************************************/
/* 矩阵求逆srcMatrix为width * height的矩阵，dstMatrix为其逆或者伪逆矩阵 */
/* inverttype为使用的方法 Matrix_LU, 最佳主元选取的gauss消元法          */
/*                        Matrix_SUV,奇异值分解法                       */
/*                        Matrix_SUV_SYM,当输入为对称正定矩阵的SUV方法  */
/*不建议使用LU，LU方法在不符合条件时会把dst全赋值为零，不好查错         */
/************************************************************************/
bool MatrixInvert(OUT MatrixType *dstData, MatrixType *srcData, const int width, const int height, const Invert_type inverttype=Matrix_LU); 

#ifdef USE_OPENCV

/*************************************************************************************************/
/* 返回矩阵行列式值，输入需要为方阵                                                              */	
/*************************************************************************************************/
MatrixType MatrixDet(MatrixType *srcData,  const int width);


/*************************************************************************************************/
/*svd分解，A M*N 的输入矩阵                                                                      */        
/*         W 结果奇异值矩阵 (M*N 或者 N*N) 或者 向量 (N*1).                                      */
/*		   U 可选的左部正交矩阵 (M*M or M*N).                                                    */                            
/*		   V 可选右部正交矩阵(N*N)                                                               */
/*         A = UW(V)T;(V)T表示V的转秩                                                            */
/*************************************************************************************************/
bool MatrixSUV(OUT MatrixType *matrix_W, OUT MatrixType *matrix_U, OUT MatrixType *matrix_V,  MatrixType *matrix_A, const int width, const int height);

/***********************************************************************  
协方差矩阵输出为sample * sample维的
************************************************************************/
bool CalcCovarMatrix_Sample(OUT MatrixType *cov_matrix, OUT MatrixType *average_matrix, MatrixType *matrixvect, const int matrixvectnum, const int matrixdim);

/***********************************************************************  
协方差矩阵输出为dim * dim维的
************************************************************************/
bool CalcCovarMatrix_Dim(OUT MatrixType *cov_matrix, OUT MatrixType *average_matrix, OUT MatrixType *matrixvect, const int matrixvectnum, const int matrixdim);

void MatrixEigenVV(OUT double* vect,            //输出特征向量
				   OUT double* val,             //输出特征值
				   IN  const double* srcData,   //输入方阵
				   IN  const int width);          //方阵宽

int MatrixSolve(OUT double* pdx, IN double* pdELeft, IN double* pdERight, IN int nN);
#endif

void JacobiFeatValue(MatrixType **inMatrix, MatrixType *featl, MatrixType **featv, int N);

void CalLeastSquareResult(MatrixType *A, MatrixType *b, int row, int col, MatrixType *X);

void cjcbj(double *a, int n,double *v,double eps);



