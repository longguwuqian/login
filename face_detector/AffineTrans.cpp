// AffineTrans.cpp: implementation of the CAffineTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "AffineTrans.h"

//#include "matrix.h"
#include "MatrixOper.h"

#include "memory.h"
#include "math.h"

double invers_a_at[4*4];
double m[4]; // 仿射变换系数，分别为c=s*cos(theta),d=s*sin(theta), tx, ty

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
		float sinAngle, float cosAngle, float sizeRatio, int gradNum, int procCase)
{
	// 得到由目标坐标系到源坐标系的变换关系
	double mTrans[4];
	mTrans[0] = cosAngle*sizeRatio;
	mTrans[1] = sinAngle*sizeRatio;
	double temp0 = desReferPoint.x;
	double temp1 = desReferPoint.y;
	mTrans[2] = (double)(-mTrans[0]*temp0+mTrans[1]*temp1+srcReferPoint.x);
	mTrans[3] = (double)(-mTrans[0]*temp1-mTrans[1]*temp0+srcReferPoint.y);

	int ret = TransImage_Affine_1D_8u(mTrans[0], mTrans[1], mTrans[2], mTrans[3], 
		pDesImg, desWd, desHt, pSrcImg, srcWd, srcHt, 0, 0, gradNum, procCase);

	return(ret);
}

// 确定由点集pOrganPtPosArray到点集pStdOrganPtArray的仿射变换关系
// 将原始图像ppSrcImg根据此仿射变换关系变换到目标图像
// 将放射后图像再经过mTrans变换，mTrans对应仿射变换的四个数值
// 其中，目标图像只取desRect中部分保存在pClipImg中
// mTrans 为求取仿射变换后对图像所继续做的变换
// procCase用来指定处理的方式，如果为0，则表示采用最近邻法取点，如果为1，则表示双线性法取点，如果为2，则表示平均法取点
// 如果gradNum=1，则表示一个通道，为灰度图，如果gradNum=3，则表示3个通道，为BGR或RGB图像，三个通道图像buffer大小均为srcWd，srcHt
// 返回值大于等于0时，为超出边界的点的数目，如果为0，表示没有点越界
// 返回值为-1，表示调用出错，应该进行容错处理
int AffineTransClipImg_1D(byte *pClipImg, int clipWidth, int clipHeight, byte *pSrcImg, int srcWidth, int srcHeight, 
		s_Rect desRect, double *pStdOrganPtArray, double *pOrganPtPosArray, int pointNum, double *mTrans, int gradNum, int procCase)
{
	int stdFaceWidth = desRect.right-desRect.left;
	int stdFaceHeight = desRect.bottom-desRect.top;
	
	double c;
	double d;
	double tx;
	double ty;
	
	int ret;
	
	// 确定仿射变换关系，共有 pointNum 点
	GetAffineMatrix_Pts(m, pStdOrganPtArray, pOrganPtPosArray, pointNum);
	
	// 确定最终的仿射变换系数等于
	c = m[0]*mTrans[0]-m[1]*mTrans[1]; // c*c'-d*d'
	d = m[1]*mTrans[0]+m[0]*mTrans[1]; // d*c'+c*d'
	tx = m[0]*mTrans[2]-m[1]*mTrans[3]+m[2]; // c*tx'-d*ty'+tx
	ty = m[1]*mTrans[2]+m[0]*mTrans[3]+m[3]; // d*tx'+c*ty'+ty
	
	m[0] = c;
	m[1] = d;
	m[2] = tx;
	m[3] = ty;
	
	// 将图像根据仿射变换关系转换
	ret = TransImage_Affine_1D_8u(m[0], m[1], m[2], m[3], pClipImg, stdFaceWidth, stdFaceHeight, 
		pSrcImg, srcWidth, srcHeight, desRect.left, desRect.top, gradNum, procCase);
	
	return(ret);
}

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
				int leftShift, int topShift, int gradNum, int procCase)
{
	if(procCase == 0) // 直接最近邻法取点
	{
		return(TransImage_Affine_1D_8u_Nearest(rot_s_x, rot_s_y, move_x, move_y, 
			pDesImg, wd, ht, pSrcImg, oriwd, oriht, leftShift, topShift, gradNum));
	}
	else if(procCase == 1)
	{
		return(TransImage_Affine_1D_8u_Bilinear(rot_s_x, rot_s_y, move_x, move_y, 
			pDesImg, wd, ht, pSrcImg, oriwd, oriht, leftShift, topShift, gradNum));
	}
	else if(procCase == 2)
	{
		return(TransImage_Affine_1D_8u_Smooth(rot_s_x, rot_s_y, move_x, move_y, 
			pDesImg, wd, ht, pSrcImg, oriwd, oriht, leftShift, topShift, gradNum));
	}
	else
	{
		return(-1);
	}
}

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
 			int leftShift, int topShift, int gradNum)
{
	int i;
	int j;
	int x1;
	int y1;
	int shifti;
	int shiftj;
	double *rc;
	double *rd;
	double tx1;
	double ty1;
	int t;
	int desIndex;

	int max_ht_wd = max(ht+topShift, wd+leftShift) + 1;
	int twd = oriwd;
	int tht = oriht;
	
	int overPointNum = 0;

	rc = (double *)malloc(sizeof(double)*max_ht_wd);
	rd = (double *)malloc(sizeof(double)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
 		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
 		memset(rd, 0, sizeof(double)*max_ht_wd);
	}
	else
	{
 		for(i = 0;i < max_ht_wd; ++i)	
 		{
 			rd[i] = rot_s_y*i;
 		}
	}

	for(i = 0; i < ht; ++i)
	{
 		shifti = i+topShift;
 		tx1 = -rd[shifti] + move_x;
 		ty1 = rc[shifti] + move_y;
 		for(j = 0; j < wd; ++j)
 		{
 			shiftj = j+leftShift;

			// 计算得到目标图中点(i, j)在原图中的对应整点坐标
 			x1 = int(rc[shiftj] + tx1 + 0.5);
 			y1 = int(rd[shiftj] + ty1 + 0.5);
 			
			// 如果超出原图范围，则置为0
			if(x1 < 0 || y1 < 0 || x1 > (twd-1) || y1 > (tht-1))
			{
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = 0;
				}

				overPointNum ++;
 			}
 			else
 			{
				// 取原图中对应整点作为目标点的值
				desIndex = (i*wd+j)*gradNum;
 				for(t = 0; t< gradNum; ++ t)
 				{
 					pDesImg[desIndex+t] = pSrcImg[(y1*oriwd+x1)*gradNum+t];
 				}
 			}
 		}
	}

	FREE(rc);
	FREE(rd);

	return(overPointNum);
}

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像左上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 仿射变换参数为目标点到源点的变换参数
// 目标图像中只取变换后图像中leftShift, topShift的部分，即pDesImg中点(i,j)在转换目标图像中为(i+leftShift,j+topShift)
// 输入图像为1D的图像，可以为1个通道也可以为多个通道
// 采用目标点在原图中对应点附近多个点的均值作为目标点的值
// 返回值大于等于0时，为超出边界的点的数目，如果为0，表示没有点越界
int TransImage_Affine_1D_8u_Smooth(double rot_s_x, double rot_s_y, double move_x, double move_y, 
 			byte *pDesImg, int wd, int ht, byte *pSrcImg, int oriwd, int oriht, 
 			int leftShift, int topShift, int gradNum)
{
	int i;
	int j;
	int k;
	int l;
	int n;
	int x1;
	int y1;
	int shifti;
	int shiftj;
	double *rc;
	double *rd;
	int maxx;
	int maxy;
	int minx;
	int miny;
	double tx1;
	double ty1;
	int sht;
	int swd;
	int t;
	int desIndex;

	int sum[3];
	
	int max_ht_wd = max(ht+topShift, wd+leftShift) + 1;
	int twd = oriwd;
	int tht = oriht;

	int overPointNum = 0;
	
	const double smoothRatio = 1.0;
	swd = max(int(sqrt(rot_s_x*rot_s_x + rot_s_y*rot_s_y)*smoothRatio + 0.5), 1);
	sht = swd;

	rc = (double *)malloc(sizeof(double)*max_ht_wd);
	rd = (double *)malloc(sizeof(double)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
 		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
 		memset(rd, 0, sizeof(double)*max_ht_wd);
	}
	else
	{
 		for(i = 0;i < max_ht_wd; ++i)	
 		{
 			rd[i] = rot_s_y*i;
 		}
	}

	for(i = 0; i < ht; ++i)
	{
 		shifti = i+topShift;
 		tx1 = -rd[shifti] + move_x;
 		ty1 = rc[shifti] + move_y;
 		for(j = 0; j < wd; ++j)
 		{
 			shiftj = j+leftShift;

			// 计算目标点在源坐标系中对应点的坐标
 			x1 = int(rc[shiftj] + tx1 + 0.5);
 			y1 = int(rd[shiftj] + ty1 + 0.5);
 			
			// 将目标点限制在源坐标系的范围内
 			minx = min(max(x1, 0), twd);
 			miny = min(max(y1, 0), tht);
 			maxx = min(max(x1 + swd, 0), twd);
 			maxy = min(max(y1 + sht, 0), tht);

			// 计算源坐标系中目标点的对应点附近的整点，根据所取范围内整点的均值作为目标点的值
 			n = 0;
 			memset(sum, 0x00, sizeof(int)*gradNum);

 			for(k = miny;k < maxy; ++k)
 			{
 				for(l = minx;l < maxx; ++l)
 				{
 					for(t = 0; t< gradNum; ++ t)
 					{
 						sum[t] += pSrcImg[(k*oriwd+l)*gradNum+t];
 					}

 					n ++;
 				}
 			}
			
			if(!n) // 所有点都不在原图范围内，补0
			{
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = 0;
				}
				
				++ overPointNum;
 			}
 			else
 			{
				// 将所有整点的均值作为目标点的值
				desIndex = (i*wd+j)*gradNum;
 				for(t = 0; t< gradNum; ++ t)
 				{
 					pDesImg[desIndex+t] = (byte)CLIP(sum[t]/n);
 				}
 			}
 		}
	}

	FREE(rc);
	FREE(rd);

	return(overPointNum);
}

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像左上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 仿射变换参数为目标点到源点的变换参数
// 目标图像中只取变换后图像中leftShift, topShift的部分，即pDesImg中点(i,j)在转换目标图像中为(i+leftShift,j+topShift)
// 如果原始图像分辨率大于目标图像，则根据比例进行平滑，否则采用最近的四个整点进行双线性插获得
// 返回值大于等于0时，为超出边界的点的数目，如果为0，表示没有点越界
int TransImage_Affine_1D_8u_Bilinear(double rot_s_x, double rot_s_y, double move_x, double move_y, 
				byte *pDesImg, int wd, int ht, byte *pSrcImg, int oriwd, int oriht, 
				int leftShift, int topShift, int gradNum)
{
	int i;
	int j;
	int x1;
	int y1;
	int x2;
	int y2;
	int shifti;
	int shiftj;
	double *rc;
	double *rd;
	double tx1;
	double ty1;
	int t;
	int desIndex;
	int srcIndex;

	double area11;
	double area12;
	double area21;
	double area22;
	
	int max_ht_wd = max(ht+topShift, wd+leftShift) + 1;
	int twd = oriwd;
	int tht = oriht;

	double temp;
	
	int overPointNum = 0;
	
	rc = (double *)malloc(sizeof(double)*max_ht_wd);
	rd = (double *)malloc(sizeof(double)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
		memset(rd, 0, sizeof(double)*max_ht_wd);
	}
	else
	{
		for(i = 0;i < max_ht_wd; ++i)	
		{
			rd[i] = rot_s_y*i;
		}
	}

	for(i = 0; i < ht; ++i)
	{
		shifti = i+topShift;
		tx1 = -rd[shifti] + move_x;
		ty1 = rc[shifti] + move_y;
		for(j = 0; j < wd; ++j)
		{
			shiftj = j+leftShift;
			
			// 计算目标图像中当前点在源图中对应点浮点坐标
			double dx = rc[shiftj] + tx1;
			double dy = rd[shiftj] + ty1;
			
			x1 = int(dx);
			y1 = int(dy);
			x2 = x1+1;
			y2 = y1+1;

			// 如果超出范围，则置为0
			if(x1 < 0 || y1 < 0 || x2 > (twd-1) || y2 > (tht-1))
			{
				desIndex = (i*wd+j)*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					pDesImg[desIndex+t] = 0;
				}
				
				++ overPointNum;
			}
			else
			{
				// 计算各块面积
				area11 = (dx-x1)*(dy-y1); // 左上角点
				area12 = (x2-dx)*(dy-y1); // 右上角点
				area21 = (dx-x1)*(y2-dy); // 左下角点
				area22 = (x2-dx)*(y2-dy); // 右下角点

				srcIndex = (y1*oriwd+x1)*gradNum; // 源坐标系中左上角点序号
				desIndex = (i*wd+j)*gradNum; // 目标坐标系中当前点序号
				for(t = 0; t< gradNum; ++ t)
				{
					// 各点所占比重和对角位置面积成正比
					temp = pSrcImg[srcIndex+t]*area22+pSrcImg[srcIndex+1+t]*area21
						+pSrcImg[srcIndex+oriwd+t]*area12+pSrcImg[srcIndex+oriwd+1+t]*area11;

					pDesImg[desIndex+t] = CLIP(ROUND_int32(temp));
				}
			}
		}
	}

	FREE(rc);
	FREE(rd);

	return(overPointNum);
}

// 确定由点集pOrganPtPosArray到点集pStdOrganPtArray的仿射变换关系
// 将原始图像ppSrcImg根据此仿射变换关系变换到目标图像
// 将放射后图像再经过mTrans变换，mTrans对应仿射变换的四个数值
// 其中，目标图像只取desRect中部分保存在pClipImg中
// mTrans 为求取仿射变换后对图像所继续做的变换
// 返回越过边界的点的数目，返回0，则表示没有越界像素
int AffineTransClipImg_2D(byte ** ppClipImg, int clipWidth, int clipHeight, byte ** ppSrcImg, int srcWidth, int srcHeight, 
				s_Rect desRect, double* pStdOrganPtArray, double* pOrganPtPosArray, int pointNum, double* mTrans, int gradNum)
{
	int stdFaceWidth = desRect.right-desRect.left;
	int stdFaceHeight = desRect.bottom-desRect.top;

	double c;
	double d;
	double tx;
	double ty;

	int overPointNum;

	// 确定仿射变换关系，共有 pointNum 点
	GetAffineMatrix_Pts(m, pStdOrganPtArray, pOrganPtPosArray, pointNum);

	// 确定最终的仿射变换系数等于
	// m'' = mTrans*m
//	c = mTrans[0]*m[0]-mTrans[1]*m[1]; // c'*c-d'*d
//	d = mTrans[1]*m[0]+mTrans[0]*m[1]; // d'*c+c'*d
//	tx = mTrans[0]*m[2]-mTrans[1]*m[3]+mTrans[2]; // c'*tx-d'*ty+tx'
//	ty = mTrans[1]*m[2]+mTrans[0]*m[3]+mTrans[3]; // d'*tx+c'*ty+ty'
	// m''= m*mTrans
	c = m[0]*mTrans[0]-m[1]*mTrans[1]; // c*c'-d*d'
	d = m[1]*mTrans[0]+m[0]*mTrans[1]; // d*c'+c*d'
	tx = m[0]*mTrans[2]-m[1]*mTrans[3]+m[2]; // c*tx'-d*ty'+tx
	ty = m[1]*mTrans[2]+m[0]*mTrans[3]+m[3]; // d*tx'+c*ty'+ty

	m[0] = c;
	m[1] = d;
	m[2] = tx;
	m[3] = ty;

  // 将图像根据仿射变换关系转换
	overPointNum = TransImage_Affine_2D_8u(m[0], m[1], m[2], m[3], ppClipImg, stdFaceWidth, stdFaceHeight, 
		ppSrcImg, srcWidth, srcHeight, desRect.left, desRect.top, gradNum);

	return(overPointNum);
}

//获取指定位置的经过仿射变换后的人脸图像
// int leftShift, int topShift分别为目标图像坐上点在仿射变换后目标坐标系中的横坐标和纵坐标
// gradNum为1或3，分别为灰度图和RGB三分量图
// 更快可以采用递推的方式进行
// 变换参数为目标点到源点的变换参数，即由目标点得到源点的变换参数
// 对输入的2D图像采用平均法进行仿射变换
// 返回越过边界的点的数目，返回0，则表示没有越界像素
int TransImage_Affine_2D_8u(double rot_s_x, double rot_s_y, double move_x, double move_y, 
				byte **ppDesImg, int wd, int ht, byte **ori_image, int oriwd, int oriht, 
				int leftShift, int topShift, int gradNum)
{
	int i,j,k,l,n;
	int x,y;
	int x1, y1;
	int shifti, shiftj;
	double *rc, *rd;
	int maxx, maxy, minx, miny;
	int max_ht_wd = max(ht+topShift, wd+leftShift) + 1;
	double tx1, ty1;
	int twd = oriwd, tht = oriht;
	int sht, swd;
	int sum[3];
	int t;
	int desIndex;

	int overPointNum = false;

	double smoothRatio = 1.0;
	sht = swd = max(int(sqrt(rot_s_x*rot_s_x + rot_s_y*rot_s_y)*smoothRatio + 0.5), 1);

	rc = (double *)malloc(sizeof(double)*max_ht_wd);
	rd = (double *)malloc(sizeof(double)*max_ht_wd);
	for(i = 0;i < max_ht_wd; ++i)
	{
		rc[i] = rot_s_x*i;
	}

	if(rot_s_y == 0)
	{
		memset(rd, 0, sizeof(double)*max_ht_wd);
	}
	else
	{
		for(i = 0;i < max_ht_wd; ++i)	
		{
			rd[i] = rot_s_y*i;
		}
	}
	
	for(i = 0;i < ht; ++i)
	{
		shifti = i+topShift;
		tx1 = -rd[shifti] + move_x;
		ty1 = rc[shifti] + move_y;
		for(j = 0;j < wd; ++j)
		{
			shiftj = j+leftShift;

			x1 = int(rc[shiftj] + tx1 + 0.5);
			y1 = int(rd[shiftj] + ty1 + 0.5);
			
			minx = min(max(x1, 0), twd);
			miny = min(max(y1, 0), tht);
			maxx = min(max(x1 + swd, 0), twd);
			maxy = min(max(y1 + sht, 0), tht);

			n = 0;
			memset(sum, 0x00, sizeof(int)*gradNum);
			for(k = miny;k < maxy; ++k)
			{
				for(l = minx;l < maxx; ++l)
				{
					x = l*gradNum;
					y = k;
					for(t = 0; t< gradNum; ++ t)
					{
						sum[t] += ori_image[y][x+t];
					}
					n ++;
				}
			}
			
			if(!n)
			{
				desIndex = j*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					ppDesImg[i][desIndex+t] = 0;
				}

				overPointNum ++;
			}
			else
			{
				desIndex = j*gradNum;
				for(t = 0; t< gradNum; ++ t)
				{
					ppDesImg[i][desIndex+t] = (byte)CLIP(sum[t]/n);
				}
			}
		}
	}

	FREE(rc);
	FREE(rd);

	return(overPointNum);
}

// 确定点集origPtPos到点集desPtPos的仿射变换关系
// 此仿射变换关系共四个参数
void GetAffineMatrix_Pts(double* affineMatrix, double* origPtPos, double* desPtPos, int ptNum)
{
	double temp[4];

	int ptOrder;
	int arrayOrder;
	double x;
	double y;

	int ptCoordNum = (ptNum<<1);

	double* a = (double *)malloc(sizeof(double)*ptCoordNum*4);
	double* at = (double *)malloc(sizeof(double)*ptCoordNum*4);

	for(ptOrder = 0; ptOrder< ptNum; ptOrder ++)
	{
		x = origPtPos[(ptOrder<<1)];
		y = origPtPos[(ptOrder<<1)+1];
		
		arrayOrder = (ptOrder<<3);
		
		a[arrayOrder] = x;
		a[arrayOrder+1] = -y;
		a[arrayOrder+2] = 1;
		a[arrayOrder+3] = 0;

		a[arrayOrder+4] = y;
		a[arrayOrder+5] = x;
		a[arrayOrder+6] = 0;
		a[arrayOrder+7] = 1;
	}

//	ShowMatrixToFile("d:\\1.txt", a, ptCoordNum, 4);

/*
	a[0] = pOrganPointSet->leftEye.x;
	a[1] = pOrganPointSet->leftEye.y;
	a[4] = pOrganPointSet->rightEye.x;
	a[5] = pOrganPointSet->rightEye.y;
	a[8] = pOrganPointSet->mouth.x;
	a[9] = pOrganPointSet->mouth.y;
*/

	//MatrixTranspose(a, ptCoordNum, 4, at);
	MatrixTransPos(at, a, 4, ptCoordNum);

	//MatrixMulti(at, 4, ptCoordNum, a, ptCoordNum, 4, invers_a_at);
	MatrixMul(invers_a_at, at, ptCoordNum, 4, a, 4, ptCoordNum);

	//MatrixInverse(invers_a_at, 4, 4);
	MatrixInvert(invers_a_at, invers_a_at, 4, 4);

	//MatrixMulti(at, 4, ptCoordNum, desPtPos, ptCoordNum, 1, temp);
	MatrixMul(temp, at, ptCoordNum, 4, desPtPos, 1, ptCoordNum);

	//MatrixMulti(invers_a_at, 4, 4, temp, 4, 1, affineMatrix);
	MatrixMul(affineMatrix, invers_a_at, 4, 4, temp, 1, 4);


/*
	c = m[0];
	d = m[1];
	tx = m[2];
	ty = m[3];

	pOrganPointSet->leftEye.x = int(c*a[0]-d*a[1]+tx+0.5);
	pOrganPointSet->leftEye.y = int(d*a[0]+c*a[1]+ty+0.5);
	pOrganPointSet->rightEye.x = int(c*a[4]-d*a[5]+tx+0.5);
	pOrganPointSet->rightEye.y = int(d*a[4]+c*a[5]+ty+0.5);
	pOrganPointSet->mouth.x = int(c*a[8]-d*a[9]+tx+0.5);
	pOrganPointSet->mouth.y = int(d*a[8]+c*a[9]+ty+0.5);*/

	FREE(a);
	FREE(at);
}

// 计算仿射矩阵的逆矩阵
void GetReverseAffineMatrix(double* m)
{
	double c = m[0];
	double d = m[1];
	double tx = m[2];
	double ty = m[3];
	double temp = c*c+d*d;
	m[0] = c/temp; // c'
	m[1] = -d/temp; // d'
	m[2] = -m[0]*tx+m[1]*ty;
	m[3] = -m[1]*tx-m[0]*ty;
}

// 计算联合仿射矩阵
// 将先进行m0，再进行m1的仿射变换合并到一个变换
void MergeAffineMatrix(double* mergeM, double *m0, double *m1)
{
	mergeM[0] = m0[0]*m1[0]-m0[1]*m1[1]; // c'*c-d'*d
	mergeM[1] = m1[0]*m0[1]+m1[1]*m0[0]; // c'*d+d'*c
	mergeM[2] = m1[0]*m0[2]-m1[2]*m0[3]+m1[2]; // c'*tx-d'*ty+tx'
	mergeM[3] = m1[2]*m0[3]+m1[0]*m0[3]+m1[3]; // d'*tx+c'*ty+ty'
}

// 通过仿射变换矩阵计算多个点仿射变换后点的坐标
void AffineTransPt(double* desPtPos, double* origPtPos, int ptNum, double* affineMatrix)
{
	int ptOrder;
	double x;
	double y;
	double c = affineMatrix[0];
	double d = affineMatrix[1];
	double tx = affineMatrix[2];
	double ty = affineMatrix[3];
	for(ptOrder = 0; ptOrder< ptNum; ptOrder ++)
	{
		x = origPtPos[(ptOrder<<1)];
		y = origPtPos[(ptOrder<<1)+1];
		desPtPos[(ptOrder<<1)] = c*x-d*y+tx;
		desPtPos[(ptOrder<<1)+1] = d*x+c*y+ty;
	}
}

// 计算源点经过仿射变换后点的坐标
s_Point AffineRotatePoint(s_Point srcPoint, double rot_s_x, double rot_s_y, double move_x, double move_y)
{
	s_Point desPoint;

	desPoint.x = ROUND_int32(rot_s_x*srcPoint.x-rot_s_y*srcPoint.y+move_x);
	desPoint.y = ROUND_int32(rot_s_y*srcPoint.x+rot_s_x*srcPoint.y+move_y);

	return(desPoint);
}

