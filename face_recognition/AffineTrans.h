// AffineTrans.h: interface for the CAffineTrans class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFFINE_TRANS
#define AFFINE_TRANS

#include "face_recognition/BasicDataType.h"

// 根据目标坐标系和源坐标系的点对应关系，以及放缩尺度和旋转方向，得到变换后的目标图像
// sinAngle, cosAngle, sizeRatio 等仿射变换参数为目标点到源点的变换参数，角度在图像坐标系中顺时针为正
// srcReferPoint为源图像中参考点坐标，即以该点为中心进行旋转
// desReferPoint为目标图中参考点，即以该点为中心进行旋转
// procCase用来指定处理的方式，如果为0，则表示采用最近邻法取点，如果为1，则表示双线性法取点，如果为2，则表示平均法取点
// 如果gradNum=1，则表示一个通道，为灰度图，如果gradNum=3，则表示3个通道，为BGR或RGB图像，三个通道图像buffer大小均为srcWd，srcHt
// 返回值大于等于0时，为超出边界的点的数目，如果为0，表示没有点越界
// 返回值为-1，表示调用出错，应该进行容错处理
int AffineTranImg_CenterSizeAngle_1D(byte *pDesImg, int desWd, int desHt, s_Point desReferPoint, 
									 byte *pSrcImg, int srcWd, int srcHt, s_Point srcReferPoint, 
									 float sinAngle, float cosAngle, float sizeRatio, int gradNum, int procCase);

// 确定由点集pOrganPtPosArray到点集pStdOrganPtArray的仿射变换关系
// 将原始图像pSrcImg根据此仿射变换关系变换到目标图像
// 将放射后图像再经过mTrans变换，mTrans对应仿射变换的四个数值
// 其中，目标图像只取desRect中部分保存在pClipImg中
// mTrans 为求取仿射变换后对图像所继续做的变换
// procCase用来指定处理的方式，如果为0，则表示采用最近邻法取点，如果为1，则表示双线性法取点，如果为2，则表示平均法取点
// 如果gradNum=1，则表示一个通道，为灰度图，如果gradNum=3，则表示3个通道，为BGR或RGB图像，三个通道图像buffer大小均为srcWd，srcHt
// 返回值大于等于0时，为超出边界的点的数目，如果为0，表示没有点越界
// 返回值为-1，表示调用出错，应该进行容错处理
int AffineTransClipImg_1D(byte *pClipImg, int clipWidth, int clipHeight, byte *pSrcImg, int srcWidth, int srcHeight, 
						  s_Rect desRect, double *pStdOrganPtArray, double *pOrganPtPosArray, int pointNum, double *mTrans, 
						  int gradNum, int procCase);

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像左上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 仿射变换参数为目标点到源点的变换参数
// 目标图像中只取变换后图像中leftShift, topShift的部分，即pDesImg中点(i,j)在转换目标图像中为(i+leftShift,j+topShift)
// 如果原始图像分辨率大于目标图像，则根据比例进行平滑
// procCase用来指定处理的方式，如果为0，则表示采用最近邻法取点，如果为1，则表示双线性法取点，如果为2，则表示平均法取点
// 返回值大于等于0时，为超出边界的点的数目，如果为0，表示没有点越界
// 返回值为-1，表示调用出错，应该进行容错处理
int TransImage_Affine_1D_8u(double rot_s_x, double rot_s_y, double move_x, double move_y, 
							byte *pDesImg, int wd, int ht, byte *pSrcImg, int oriwd, int oriht, 
							int leftShift, int topShift, int gradNum, int procCase);

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像左上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 仿射变换参数为目标点到源点的变换参数
// 目标图像中只取变换后图像中leftShift, topShift的部分，即pDesImg中点(i,j)在转换目标图像中为(i+leftShift,j+topShift)
// 输入图像为1D的图像，可以为1个通道也可以为多个通道
// 采用目标点在原图中对应点的近似整点的值作为目标点的值
// 返回值为超出边界的点的数目，如果为0，表示没有点越界
int TransImage_Affine_1D_8u_Nearest(double rot_s_x, double rot_s_y, double move_x, double move_y, 
									 byte *pDesImg, int wd, int ht, byte *pSrcImg, int oriwd, int oriht, 
									 int leftShift, int topShift, int gradNum);

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像左上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 仿射变换参数为目标点到源点的变换参数
// 目标图像中只取变换后图像中leftShift, topShift的部分，即pDesImg中点(i,j)在转换目标图像中为(i+leftShift,j+topShift)
// 输入图像为1D的图像，可以为1个通道也可以为多个通道
// 采用目标点在原图中对应点附近多个点的均值作为目标点的值
// 返回值为超出边界的点的数目，如果为0，表示没有点越界
int TransImage_Affine_1D_8u_Smooth(double rot_s_x, double rot_s_y, double move_x, double move_y, 
									byte *pDesImg, int wd, int ht, byte *pSrcImg, int oriwd, int oriht, 
									int leftShift, int topShift, int gradNum);

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像左上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 仿射变换参数为目标点到源点的变换参数
// 目标图像中只取变换后图像中leftShift, topShift的部分，即pDesImg中点(i,j)在转换目标图像中为(i+leftShift,j+topShift)
// 如果原始图像分辨率大于目标图像，则根据比例进行平滑，否则采用最近的四个整点进行双线性插获得
// 返回值为超出边界的点的数目，如果为0，表示没有点越界
int TransImage_Affine_1D_8u_Bilinear(double rot_s_x, double rot_s_y, double move_x, double move_y, 
									  byte *pDesImg, int wd, int ht, byte *pSrcImg, int oriwd, int oriht, 
									  int leftShift, int topShift, int gradNum);

// 确定由点集pOrganPtPosArray到点集pStdOrganPtArray的仿射变换关系
// 将原始图像ppSrcImg根据此仿射变换关系变换到目标图像
// 将放射后图像再经过mTrans变换，mTrans对应仿射变换的四个数值
// 其中，目标图像只取desRect中部分保存在pClipImg中
// mTrans 为求取仿射变换后对图像所继续做的变换
// 返回越过边界的点的数目，返回0，则表示没有越界像素
int AffineTransClipImg_2D(byte ** ppClipImg, int clipWidth, int clipHeight, byte ** ppSrcImg, int srcWidth, int srcHeight, 
				s_Rect desRect, double* pStdOrganPtArray, double* pOrganPtPosArray, int pointNum, double* mTrans, int gradNum);

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像坐上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 变换参数为目标点到源点的变换参数，即由目标点得到源点的变换参数
// 对输入的2D图像采用平均法进行仿射变换
// 返回越过边界的点的数目，返回0，则表示没有越界像素
int TransImage_Affine_2D_8u(double rot_s_x, double rot_s_y, double move_x, double move_y, 
							 byte **ppDesImg, int wd, int ht, byte **ori_image, int oriwd, int oriht, 
							 int leftShift, int topShift, int gradNum);

// 确定点集origPtPos到点集desPtPos的仿射变换关系
// 此仿射变换关系共四个参数
void GetAffineMatrix_Pts(double* affineMatrix, double* origPtPos, double* desPtPos, int ptNum);

// 计算仿射矩阵的逆矩阵
void GetReverseAffineMatrix(double* m);

// 计算联合仿射矩阵
// 将先进行m0，再进行m1的仿射变换合并到一个变换
void MergeAffineMatrix( double* mergeM, double *m0, double *m1 );

// 通过仿射变换矩阵计算多个点仿射变换后点的坐标
void AffineTransPt(double* desPtPos, double* origPtPos, int ptNum, double* affineMatrix);

// 计算源点经过仿射变换后点的坐标
s_Point AffineRotatePoint( s_Point srcPoint, double rot_s_x, double rot_s_y, double move_x, double move_y );

#endif

