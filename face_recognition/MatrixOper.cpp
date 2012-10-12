#include "MatrixOper.h"

//#define FREE(p) if (p != NULL){free(p); p = NULL;}


/*************************************************************************************************/
/* 矩阵加法 ,   dstMatrix =  srcMatrix1 + srcMatrix2,矩阵为width列，height行                     */
/*************************************************************************************************/
bool MatrixAdd( OUT MatrixType *dstData, MatrixType *srcData1, MatrixType *srcData2, const int width, const int height)
{
#ifdef USE_OPENCV
	CvMat *pmatSrc1;
	pmatSrc1 = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pmatSrc1 == NULL)
	{
		return false;
	}

	CvMat *pmatSrc2;
	pmatSrc2 = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pmatSrc2 == NULL)
	{
		cvReleaseMatHeader(&pmatSrc1);
		return false;
	}

	CvMat *pmatDst;
	pmatDst = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pmatDst == NULL)
	{
		cvReleaseMatHeader(&pmatSrc1);
		cvReleaseMatHeader(&pmatSrc2);
		return false;
	}

	cvSetData(pmatSrc1, srcData1, pmatSrc1->step);
	cvSetData(pmatSrc2, srcData2, pmatSrc2->step);
	cvSetData(pmatDst,  dstData,  pmatDst->step);

	cvAdd(pmatSrc1, pmatSrc2, pmatDst);

	cvReleaseMatHeader(&pmatSrc1);
	cvReleaseMatHeader(&pmatSrc2);
	cvReleaseMatHeader(&pmatDst);
	return true;

#else
	int i,j;
	for(i = 0;i < height; ++i)
		for(j = 0;j < width; ++j)
			dstData[i*width + j] = srcData1[i*width + j] + srcData2[i*width + j];

	return true;
#endif
}



/*************************************************************************************************/
/* 矩阵减法 ,   dstMatrix =  srcMatrix1 + srcMatrix2,矩阵为width列，height行                     */
/*************************************************************************************************/
bool MatrixSub(OUT MatrixType *dstData,  MatrixType *srcData1, MatrixType *srcData2, const int width, const int height)
{
#ifdef USE_OPENCV
	CvMat *pmatSrc1;
	pmatSrc1 = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pmatSrc1 == NULL)
	{
		return false;
	}

	CvMat *pmatSrc2;
	pmatSrc2 = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pmatSrc2 == NULL)
	{
		cvReleaseMatHeader(&pmatSrc1);
		return false;
	}

	CvMat *pmatDst;
	pmatDst = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pmatDst == NULL)
	{
		cvReleaseMatHeader(&pmatSrc1);
		cvReleaseMatHeader(&pmatSrc2);
		return false;
	}

	cvSetData(pmatSrc1, srcData1, pmatSrc1->step);
	cvSetData(pmatSrc2, srcData2, pmatSrc2->step);
	cvSetData(pmatDst, dstData, pmatDst->step);

	cvSub(pmatSrc1, pmatSrc2, pmatDst);

	cvReleaseMatHeader(&pmatSrc1);
	cvReleaseMatHeader(&pmatSrc2);
	cvReleaseMatHeader(&pmatDst);
	return true;

#else
	int i,j;
	for(i = 0;i < height; ++i)
		for(j = 0;j < width; ++j)
			dstData[i*width + j] = srcData1[i*width + j] - srcData2[i*width + j];

	return true;
#endif
}


/*************************************************************************************************/
/* 矩阵乘法 ,   dstMatrix为矩阵C， srcMatrix1为h1 * w1 维矩阵A，srcMatrix2为h2 *w2维矩阵B        */
/*       C = AB,C为h1 * w2维矩阵                                                                 */
/*************************************************************************************************/
int MatrixMul(OUT MatrixType *dstData, MatrixType *srcData1, const int w1,const int h1, MatrixType *srcData2, const int w2, const int h2)
{
	if(w1 != h2)
	{
		return WandHnotmatch;
	}

#ifdef USE_OPENCV
	CvMat *pmatSrc1;
	pmatSrc1 = cvCreateMatHeader(h1, w1, CV_DATA_TYPE);
	if (pmatSrc1 == NULL)
	{
		return CannotCreateMatHead;
	}

	CvMat *pmatSrc2;
	pmatSrc2 = cvCreateMatHeader(h2, w2, CV_DATA_TYPE);
	if (pmatSrc2 == NULL)
	{
		cvReleaseMatHeader(&pmatSrc1);
		return CannotCreateMatHead;
	}

	CvMat *pmatDst;
	pmatDst = cvCreateMatHeader( h1, w2, CV_DATA_TYPE);
	if (pmatDst == NULL)
	{
		cvReleaseMatHeader(&pmatSrc1);
		cvReleaseMatHeader(&pmatSrc2);
		return CannotCreateMatHead;	
	}

	cvSetData(pmatSrc1, srcData1, pmatSrc1->step);
	cvSetData(pmatSrc2, srcData2, pmatSrc2->step);
	cvSetData(pmatDst, dstData, pmatDst->step);

	//cvMatMul(pmatSrc1, pmatSrc2, pmatDst);
	cvMatMulAdd(pmatSrc1, pmatSrc2, 0, pmatDst);

	cvReleaseMatHeader(&pmatSrc1);
	cvReleaseMatHeader(&pmatSrc2);
	cvReleaseMatHeader(&pmatDst);
	return Success;
#else
	int i,j,k;
	for(i = 0;i < h1; ++i)
		for(j = 0;j < w2; ++j)
		{
			MatrixType sum = 0;
			for(k = 0;k < w1; ++k)
				sum += srcData1[i*w1 + k]*srcData2[k*w2 + j];
			dstData[i*w2 + j] = sum;
		}
	return Success;
#endif
}

/************************************************************************/
/* 矩阵求逆srcMatrix为width * height的矩阵，dstMatrix为其逆或者伪逆矩阵 */
/* inverttype为使用的方法 Matrix_LU, 最佳主元选取的gauss消元法          */
/*                        Matrix_SUV,奇异值分解法                       */
/*                        Matrix_SUV_SYM,当输入为对称正定矩阵的SUV方法  */
/*不建议使用LU，LU方法在不符合条件时会把dst全赋值为零，不好查错         */
/************************************************************************/
bool MatrixInvert(OUT MatrixType *dstData, MatrixType *srcData, const int width, const int height, const Invert_type inverttype)
{
#ifdef USE_OPENCV
	CvMat *pmatSrc;
	pmatSrc = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if(pmatSrc == NULL)
	{
		return false;
	}

	CvMat *pmatDst;
	pmatDst = cvCreateMatHeader(width, height, CV_DATA_TYPE);
	if(pmatDst == NULL)
	{
		cvReleaseMatHeader(&pmatSrc);
		return false;
	}

	cvSetData(pmatSrc, srcData, pmatSrc->step);
	cvSetData(pmatDst, dstData, pmatDst->step);

	switch (inverttype)
	{
	case Matrix_LU:
		cvInvert(pmatSrc, pmatDst, CV_LU);
		break;
	case Matrix_SUV:
		cvInvert(pmatSrc, pmatDst, CV_SVD);
		break;
	case Matrix_SUV_SYM:
		cvInvert(pmatSrc, pmatDst, CV_SVD_SYM);
		break;
	default:
		break;
	}

	cvReleaseMatHeader(&pmatSrc);
	cvReleaseMatHeader(&pmatDst);
	return true;

#else
	int i,j,k;
	MatrixType div,temp;
	MatrixType *out;
	int *is,*js;

	if(width != height)
		return false;

	out = (MatrixType *)malloc(sizeof(MatrixType)*height*width);
	is = (int *)malloc(sizeof(int)*height);
	js = (int *)malloc(sizeof(int)*height);
	for(i = 0;i < height; ++i)
	{
		is[i] = i;
		js[i] = i;
	}

	// start from first column to the next 
	for(k = 0;k < height; ++k)
	{
		div = 0;
		for(i = k;i < height; ++i)
			for(j = k;j < height; ++j)
			{
				if(fabs(srcData[i*width + j]) > div)
				{
					div = fabs(srcData[i*width + j]);
					is[k] = i;
					js[k] = j;
				}
			}
			if(fabs(div) < 1e-10)
			{
				FREE( out );
				FREE( is );
				FREE( js );
				return false;
			}
			if(is[k] != k)
			{
				for(j = 0;j < height; ++j)
				{
					temp = srcData[k*width + j];
					dstData[k*width + j] = srcData[is[k]*width + j];
					dstData[is[k]*width + j] = temp;
				}
			}
			if(js[k] != k)
			{
				for(i = 0;i < height; ++i)
				{
					temp = srcData[i*width + k];
					dstData[i*width + k] = srcData[i*width + js[k]];
					dstData[i*width + js[k]] = temp;
				}
			}
			dstData[k*width + k] = 1/srcData[k*width + k];
			for(j = 0;j < height; ++j)
			{
				if(j != k)
					dstData[k*width + j] = srcData[k*width + j]*srcData[k*width + k];
			}
			for(i = 0;i < height; ++i)
			{
				if(i != k)
				{
					for(j = 0;j < height; ++j)
					{
						if(j != k)
							dstData[i*width + j] -= srcData[i*width + k]*srcData[k*width + j];
					}
				}
			}
			for(i = 0;i < height; ++i)
			{
				if(i != k)
					dstData[i*width + k] = -srcData[i*width + k]*srcData[k*width + k];
			}							
	}

	for(k = height - 1;k >= 0; --k)
	{
		for(j = 0;j < height; ++j)
			if(js[k] != k)
			{
				temp = srcData[k*width + j];
				dstData[k*width + j] = srcData[js[k]*width + j];
				dstData[js[k]*width + j] = temp;
			}
			for(i = 0;i < height; ++i)
				if(is[k] != k)
				{
					temp = srcData[i*width + k];
					dstData[i*width + k] = srcData[i*width + is[k]];
					dstData[i*width + is[k]] = temp;
				}
	}
	FREE( is );
	FREE( js );
	FREE( out );
	return true;
#endif
}

bool MatrixTransPos(OUT MatrixType *pDstData, MatrixType *pSrcData, int w, int h)
{
#ifdef USE_OPENCV
	CvMat *pSrc;
	pSrc = cvCreateMatHeader(h, w, CV_DATA_TYPE);
	cvSetData(pSrc, pSrcData, pSrc->step);

	CvMat *pDst;
	pDst = cvCreateMatHeader(w, h, CV_DATA_TYPE);
	cvSetData(pDst, pDstData, pDst->step);

	cvTranspose(pSrc, pDst);

	cvReleaseMatHeader(&pSrc);
	cvReleaseMatHeader(&pDst);
	return true;
#else
	int i,j;
	if(pDstData == NULL)//转置结果保留在原矩阵中
	{
		MatrixType *m3;

		m3 = (MatrixType *)malloc(sizeof(MatrixType)*h*w);
		for(i = 0;i < w; ++i)
			for(j = 0;j < h; ++j)
			{
				m3[i*h + j] = pSrcData[j*w + i];
			}
			for(i = 0;i < h; ++i)
				for(j = 0;j < w; ++j)
					pDstData[i*w + j] = m3[j*w + i];
			FREE( m3 );
	}
	else
	{
		for(i = 0;i < w; ++i)
			for(j = 0;j < h; ++j)
			{
				pDstData[i*h + j] = pSrcData[j*w + i];
			}
	}
	return true;
#endif
}

#ifdef USE_OPENCV
/*************************************************************************************************/
/* 返回矩阵行列式值，输入需要为方阵                                                              */	
/*************************************************************************************************/
MatrixType MatrixDet(MatrixType* srcData,  const int width)
{
	CvMat *pmatSrc;
	pmatSrc = cvCreateMatHeader(width, width, CV_DATA_TYPE);

	cvSetData(pmatSrc, srcData, pmatSrc->step);

	MatrixType det = cvDet(pmatSrc);

	cvReleaseMatHeader(&pmatSrc);

	return det;
}


/*************************************************************************************************/
/*svd分解，A M*N 的输入矩阵                                                                      */        
/*         W 结果奇异值矩阵 (M*N 或者 N*N) 或者 向量 (N*1).                                      */
/*		   U 可选的左部正交矩阵 (M*M or M*N).                                                    */                            
/*		   V 可选右部正交矩阵(N*N)                                                               */
/*         A = UW(V)T;(V)T表示V的转秩                                                            */
/*************************************************************************************************/
bool MatrixSUV(OUT MatrixType *matrix_W, OUT MatrixType *matrix_U, OUT MatrixType *matrix_V, MatrixType *matrix_A, const int width, const int height)
{
	CvMat *pMatA;
	pMatA = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pMatA == NULL)
	{
		return false;
	}

	CvMat *pMatW;
	pMatW = cvCreateMatHeader(height, width, CV_DATA_TYPE);
	if (pMatW == NULL)
	{
		cvReleaseMatHeader(&pMatA);
		return false;
	}

	CvMat *pMatU;
	pMatU = cvCreateMatHeader(height, height, CV_DATA_TYPE);
	if (pMatU == NULL)
	{
		cvReleaseMatHeader(&pMatA);
		cvReleaseMatHeader(&pMatW);
		return false;
	}

	CvMat *pMatV;
	pMatV = cvCreateMatHeader(width, width, CV_DATA_TYPE);
	if (pMatV == NULL)
	{
		cvReleaseMatHeader(&pMatA);
		cvReleaseMatHeader(&pMatW);
		cvReleaseMatHeader(&pMatU);
		return false;
	}

	cvSetData(pMatA, matrix_A, pMatA->step);
	cvSetData(pMatU, matrix_U, pMatU->step);
	cvSetData(pMatV, matrix_V, pMatV->step);
	cvSetData(pMatW, matrix_W, pMatW->step);

	cvSVD(pMatA, pMatW, pMatV, pMatU, CV_SVD_MODIFY_A);

	cvReleaseMatHeader(&pMatA);
	cvReleaseMatHeader(&pMatU);
	cvReleaseMatHeader(&pMatV);
	cvReleaseMatHeader(&pMatW);

	return true;
}


/***********************************************************************  
协方差矩阵输出为sample * sample维的
************************************************************************/
bool CalcCovarMatrix_Sample(OUT MatrixType *cov_matrix, OUT MatrixType *average_matrix, MatrixType *matrixvect, const int matrixvectnum, const int matrixdim)
{
	CvMat *pCov_Mat;
	pCov_Mat = cvCreateMatHeader(matrixvectnum, matrixvectnum, CV_DATA_TYPE);
	cvSetData(pCov_Mat, cov_matrix, pCov_Mat->step);

	CvMat *pAve_Mat;
	pAve_Mat = cvCreateMatHeader(1, matrixdim, CV_DATA_TYPE);
	cvSetData(pAve_Mat, average_matrix, pAve_Mat->step);
	CvMat **pMatVect;
	pMatVect = (CvMat **)malloc(matrixvectnum * sizeof(CvMat*));
	int i = 0;
	for (i = 0; i < matrixvectnum; i ++)
	{
		*(pMatVect + i) = cvCreateMatHeader(1, matrixdim, CV_DATA_TYPE);
		cvSetData(*(pMatVect + i), &(*(matrixvect + i * matrixdim)), (*(pMatVect + i))->step);
	}


	cvCalcCovarMatrix((const CvArr**)pMatVect, matrixvectnum, pCov_Mat, pAve_Mat,CV_COVAR_SCRAMBLED);

	cvReleaseMatHeader(&pAve_Mat);
	cvReleaseMatHeader(&pCov_Mat);
	for (i = 0; i < matrixvectnum; i ++)
	{
		cvReleaseMatHeader((pMatVect + i));
	}
	FREE(pMatVect);
	return true;
}

/***********************************************************************  
协方差矩阵输出为dim * dim维的
************************************************************************/
bool CalcCovarMatrix_Dim(OUT MatrixType *cov_matrix, OUT MatrixType *average_matrix, OUT MatrixType *matrixvect, const int matrixvectnum, const int matrixdim)
{
	CvMat *pCov_Mat;
	pCov_Mat = cvCreateMatHeader(matrixdim, matrixdim, CV_DATA_TYPE);
	cvSetData(pCov_Mat, cov_matrix, pCov_Mat->step);

	CvMat *pAve_Mat;
	pAve_Mat = cvCreateMatHeader(1, matrixdim, CV_DATA_TYPE);
	cvSetData(pAve_Mat, average_matrix, pAve_Mat->step);
	CvMat **pMatVect;
	pMatVect = (CvMat **)malloc(matrixvectnum * sizeof(CvMat*));

	int i = 0;
	for (i = 0; i < matrixvectnum; i ++)
	{
		*(pMatVect + i) = cvCreateMatHeader(1, matrixdim, CV_DATA_TYPE);
		cvSetData(*(pMatVect + i), &(*(matrixvect + i * matrixdim)), (*(pMatVect + i))->step);
	}

	cvCalcCovarMatrix((const CvArr**)pMatVect, matrixvectnum, pCov_Mat, pAve_Mat, CV_COVAR_NORMAL);

	cvReleaseMatHeader(&pAve_Mat);
	cvReleaseMatHeader(&pCov_Mat);
	for (i = 0; i < matrixvectnum; i ++)
	{
		cvReleaseMatHeader((pMatVect + i));
	}
	FREE(pMatVect);
	return true;
}

void MatrixEigenVV(OUT double* vect,            //输出特征向量
				   OUT double* val,             //输出特征值
				   IN  const double* srcData,   //输入方阵
				   IN  const int width)          //方阵宽
{
	CvMat *pMatSrc = NULL;
	pMatSrc = cvCreateMatHeader(width, width, CV_64FC1);
	/*	cvZero(pMatSrc);*/

	CvMat *pMatVect = NULL;
	pMatVect = cvCreateMatHeader(width, width, CV_64FC1);
	/*	cvZero(pMatVect);*/

	CvMat *pMatVel = NULL;
	pMatVel = cvCreateMatHeader(1, width, CV_64FC1);
	/*	cvZero(pMatVel);*/

	int memsize = sizeof(double) * width * width;
	double* srctemp = NULL;
	srctemp = (double *)malloc( memsize );
	memcpy(srctemp, srcData, memsize);

	cvSetData(pMatSrc, srctemp, pMatSrc->step);
	cvSetData(pMatVect, vect, pMatVect->step);
	cvSetData(pMatVel, val, pMatVel->step);

	cvEigenVV(pMatSrc, pMatVect, pMatVel, 0.0000000000000001);

	// 	GetMatData(vect, pMatVect, type_double);
	// 	GetMatData(val, pMatVel, type_double);

	cvReleaseMatHeader(&pMatSrc);
	cvReleaseMatHeader(&pMatVect);
	cvReleaseMatHeader(&pMatVel);

	FREE(srctemp);
}

int MatrixSolve(OUT double* pdx, IN double* pdELeft, IN double* pdERight, IN int nN)
{
	if ( (!pdx) || (!pdELeft) || (!pdERight) || (nN<=0) )
	{
		return -1;
	}

	CvMat* pmatSrc1 = cvCreateMatHeader(nN, nN, CV_64FC1);
	CvMat* pmatSrc2 = cvCreateMatHeader(nN, 1, CV_64FC1);
	CvMat* pmatDst = cvCreateMatHeader(nN, 1, CV_64FC1);

	cvSetData(pmatSrc1, pdELeft, pmatSrc1->step);
	cvSetData(pmatSrc2, pdERight, pmatSrc2->step);
	cvSetData(pmatDst, pdx, pmatDst->step);
	cvZero(pmatDst);

	cvSolve(pmatSrc1, pmatSrc2, pmatDst);

	cvReleaseMatHeader(&pmatSrc1);
	cvReleaseMatHeader(&pmatSrc2);
	cvReleaseMatHeader(&pmatDst);

	return 0;
}

#endif

//计算特征向量和特征值,并按特征值由大向小排列
void JacobiFeatValue(MatrixType **inMatrix, MatrixType *featl, MatrixType **featv, int N)
{
	int i,j;
	MatrixType **S, **R;//特征向量矩阵
	MatrixType maxa,t;
	MatrixType mine = 1e-9f; // 0.0001;
	int p, q, sw;
	MatrixType omega;
	MatrixType m, n;
	MatrixType sint2, sint, cost, cost2;
	int *swap;
	//FILE *fp;
	
	//fp = fopen("d:\\temp1.txt", "w+");
	//if( fp == NULL )
	//{
	//	return;
	//}

	swap = (int *)malloc(sizeof(int)*N);

	S = CreateMemory_2D_64f(N, N);
	R = CreateMemory_2D_64f(N, N);
	for(i = 0;i < N; ++i)
	{
		for(j = 0;j < N; ++j)
		{
			S[i][j] = 0;
		}
		S[i][i] = 1;
	}
	while(1)
	{		
		maxa = fabs(inMatrix[0][1]);
		p = 0;q = 1;
		for(i = 0;i < N; ++i)
		{
			for(j = i + 1;j < N; ++j)
			{
				if(fabs(inMatrix[i][j]) > maxa)
				{
					maxa = fabs(inMatrix[i][j]);
					p = i;q = j;
				}
			}
		}
		//fprintf(fp, "max:%.12f\n", maxa);

		
		if(maxa < mine)
			break;
		m = -inMatrix[p][q];
		n = (inMatrix[q][q] - inMatrix[p][p])/2;
		omega = sgn(n)*m/(sqrt(m*m + n*n));
		sint2 = omega;
		cost2 = sqrt(1 - sint2*sint2);
		sint = omega/(sqrt(2*(1 + cost2)));
		cost = sqrt(1 - sint*sint);
		for(i = 0;i < N; ++i)
			memcpy(R[i], inMatrix[i], sizeof(MatrixType)*N);
		R[p][p] = inMatrix[p][p]*cost*cost + inMatrix[q][q]*sint*sint + inMatrix[p][q]*sint2;
		R[q][q] = inMatrix[p][p]*sint*sint + inMatrix[q][q]*cost*cost - inMatrix[p][q]*sint2;
		R[q][p] = R[p][q] = (inMatrix[q][q] - inMatrix[p][p])*sint2/2 + inMatrix[p][q]*cost2;
		for(i = 0;i < N; ++i)
		{
			if(i == q||i == p)
				continue;
			R[i][p] = R[p][i] = inMatrix[p][i]*cost + inMatrix[q][i]*sint;
			R[i][q] = R[q][i] = -inMatrix[p][i]*sint + inMatrix[q][i]*cost;			 
		}
		for(i = 0;i < N; ++i)
			memcpy(inMatrix[i], R[i], sizeof(MatrixType)*N);		
		for(i = 0;i < N; ++i)
		{
			t = S[i][p];
			S[i][p] = t*cost + S[i][q]*sint;
			S[i][q] = -t*sint + S[i][q]*cost;
		}
	}

	//对特征值进行排序
	for(i = 0;i < N; ++i)
	{
		featl[i] = inMatrix[i][i];
		swap[i] = i;
	}

	for(i = 0;i < N - 1; ++i)
		for(j = i + 1;j < N; ++j)
		{
			if(featl[i] < featl[j])
			{
				t = featl[i];
				featl[i] = featl[j];
				featl[j] = t;
				sw = swap[i];
				swap[i] = swap[j];
				swap[j] = sw;
			}
		}
	for(i = 0;i < N; ++i)
		for(j = 0;j < N; ++j)
			featv[j][i] = S[j][swap[i]];

	//fclose( fp );
	FREE( swap );
	ReleaseMemory_2D_64f( R, N, N );
	ReleaseMemory_2D_64f( S, N, N );
}

void CalLeastSquareResult(MatrixType *A, MatrixType *b, int row, int col, MatrixType *X)
{
	MatrixType *temp1, *temp2;

	temp1 = (MatrixType *)malloc(sizeof(MatrixType)*col*row);
	temp2 = (MatrixType *)malloc(sizeof(MatrixType)*col*row);
	
	//MatrixTransPos(A, row, col, temp1);	
	MatrixTransPos(temp1, A, col, row);	
	//MatrixMul(temp1, col, row, A, row, col, temp2);
	MatrixMul(temp2, temp1, row, col, A, col, row);
	//MatrixInvert(temp2, col, col);
	MatrixInvert(temp2, temp2, col, col);
	//MatrixMul(temp1, col, row, b, row, 1, A);
	MatrixMul(A, temp1, row, col, b, 1, row);
	//MatrixMul(temp2, col, col, A, col, 1, X);
	MatrixMul(X, temp2, col, col, A, 1, col);

	FREE( temp1 );
	FREE( temp2 );
}

//计算特征向量和特征值,并按特征值由大向小排列
//void JacobiFeatValue_1(MatrixType **inMatrix, MatrixType *featl, MatrixType **featv, int N)
void cjcbj(double *a, int n,double *v,double eps)
{
	int i,j,k,p,q,u,w,t,s;
	double ff,fm,cn,sn,omega,x,y,d;
	char flag = 0;

	for (i=0; i<=n-1; i++)
	{
		v[i*n+i]=1.0;
		for (j=0; j<=n-1; j++)
			if (i!=j)
				v[i*n+j]=0.0;
	}
	ff=0.0;
	for (i=1; i<=n-1; i++)
		for (j=0; j<=i-1; j++)
		{
			d=a[i*n+j]; 
			ff=ff+d*d; 
		}	

	ff=sqrt(2.0*ff);
    while(1)
	{
		if(!flag)
		{
			flag = 0;
			ff=ff/(1.0*n);
		}
		else
			flag = 0;
		
		for (i=1; i<=n-1; i++)
		{
			for (j=0; j<=i-1; j++)
			{
				d=fabs(a[i*n+j]);
				if (d>ff)
				{
					p=i; q=j;
					u=p*n+q; w=p*n+p; t=q*n+p; s=q*n+q;
					x=-a[u]; y=(a[s]-a[w])/2.0;
					omega=x/sqrt(x*x+y*y);
					if (y<0.0)
					omega=-omega;
					sn=1.0+sqrt(1.0-omega*omega);
					sn=omega/sqrt(2.0*sn);
					cn=sqrt(1.0-sn*sn);
					fm=a[w];
					a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega;
					a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega;
					a[u]=0.0; a[t]=0.0;
					for (k=0; k<=n-1; k++)
						if ((k!=p)&&(k!=q))
						{
							u=p*n+k; w=q*n+k;
							fm=a[u];
							a[u]=fm*cn+a[w]*sn;
							a[w]=-fm*sn+a[w]*cn;
						}
					for (k=0; k<=n-1; k++)
						if ((k!=p)&&(k!=q))
					{
						u=k*n+p; w=k*n+q;
						fm=a[u];
						a[u]=fm*cn+a[w]*sn;
						a[w]=-fm*sn+a[w]*cn;
					}
					for (k=0; k<=n-1; k++)
					{
						u=k*n+p; w=k*n+q;
						fm=v[u];
						v[u]=fm*cn+v[w]*sn;
						v[w]=-fm*sn+v[w]*cn;
					}	
					break;
				}
			}
			if(j <= i - 1)
			{
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			if (ff<eps) 
				break;	
		}
	}
	//对特征值进行排序
/*	for(i = 0;i < N; ++i)
	{
		featl[i] = inMatrix[i][i];
		swap[i] = i;
	}

	for(i = 0;i < N - 1; ++i)
		for(j = i + 1;j < N; ++j)
		{
			if(featl[i] < featl[j])
			{
				t = featl[i];
				featl[i] = featl[j];
				featl[j] = t;
				sw = swap[i];
				swap[i] = swap[j];
				swap[j] = sw;
			}
		}
	for(i = 0;i < N; ++i)
		for(j = 0;j < N; ++j)
			featv[j][i] = S[j][swap[i]];*/
}

