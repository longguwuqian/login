// BasicDataType.h: interface for the CBasicDataType class.


#if !defined(AFX_BASICDATATYPE_H__AB497EBE_BDF7_45C4_9B78_C54592D6410E__INCLUDED_)
#define AFX_BASICDATATYPE_H__AB497EBE_BDF7_45C4_9B78_C54592D6410E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <stdlib.h>
#include "stdio.h"
#include <time.h> 
#include <iostream>
using namespace std;

#define OUT

//typedef int int;
typedef unsigned long dword;
//typedef double double;
typedef unsigned char byte;
typedef unsigned long dword;
//typedef char char;
//typedef long bool;
//typedef byte BYTE;
typedef short int int16;
//typedef bool BOOL;

#define INT_MAX0 2147483647
#define INT_MIN0 (-2147483647-1)

#define ROUND_int32(f) ((f)>0 ? ( (int)((f)+0.5) ) : ( (int)((f)-0.5) ))
#define ROUND_uint32(f) ((int)((f)+0.5))
#define FREE( p ) if( NULL!=p ) { free( p ); p = NULL; }

#ifndef CLIP
#define CLIP(a) ((a)>255?255:((a)<0?0:(a)))
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef PI
#define PI 3.1415926536
#endif

#ifndef NEAR_ZERO
#define NEAR_ZERO (1e-20f)
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif



typedef struct s_Point
{
	int x;
	int y;
}
s_Point;

typedef struct s_Point_32f
{
	float x;
	float y;
}
s_Point_32f;

typedef struct s_Point_f64
{
	double x;
	double y;
}
s_Point_f64;

typedef struct s_PointArray
{
	int maxNum;
	int actNum;
	s_Point * pArray;
}
s_PointArray;

typedef struct s_RectSize
{
	int width;
	int height;
}
s_RectSize;

typedef struct s_Rect
{
	int left;
	int top;
	int right;
	int bottom;
}
s_Rect;

typedef struct s_RectArray
{
	s_Rect * pArray;
	int maxNum;
	int actNum;
}
s_RectArray;

typedef struct s_VifdRect_ltsize
{
	s_Point ltPt;
	s_RectSize rectSize;
}
s_VifdRect_ltsize;

typedef struct s_Rect_f64
{
	double left;
	double top;
	double right;
	double bottom;
}
s_Rect_f64;

typedef struct s_Ellipse
{
	s_Point centerPoint; //��Բ����
	int rad_x; //�����귽����Բ�İ뾶
	int rad_y; //�����귽����Բ�İ뾶
}
s_Ellipse;

typedef struct s_RealData
{
	double real_data;
	double img_data;
}
s_RealData;

typedef struct s_VldData
{
	int bVld;
	double data;
}
s_VldData;

typedef struct s_VldRealData
{
	s_VldData real;
	s_VldData img;
}
s_VldRealData;

typedef struct s_Data_2D_8u
{
	int width;
	int height;
	byte ** ppData;
}
s_Data_2D_8u;

typedef struct s_Data_2D_32i
{
	int width;
	int height;
	int ** ppData;
}
s_Data_2D_32i;

typedef struct s_Data_2D_64f
{
	int width;
	int height;
	double ** ppData;
}
s_Data_2D_64f;

typedef struct s_Data_2D_32f
{
	int width;
	int height;
	float ** ppData;
}
s_Data_2D_32f;

typedef struct s_Data_1D_8u
{
	int width;
	int height;
	byte * pData;
}
s_Data_1D_8u;

typedef struct s_Data_1D_32i
{
	int width;
	int height;
	int * pData;
}
s_Data_1D_32i;

typedef struct s_Data_1D_64f
{
	int width;
	int height;
	double * pData;
}
s_Data_1D_64f;

typedef struct s_Data_1D_32f
{
	int width;
	int height;
	float * pData;
}
s_Data_1D_32f;

typedef struct s_CommonMem
{
	byte * pBuf;
	int bufSize;
}
s_CommonMem;

typedef struct s_Img_8u
{
	int width;
	int height;
	byte * pImgData;
	byte ** ppImgIndex;
	//	int grad;
}
s_Img_8u;
//
//typedef struct s_Img_16s
//{
//	int width;
//	int height;
//	int16 * pImgData;
//	int16 ** ppImgIndex;
//}
//s_Img_16s;

typedef struct s_Img_32i
{
	int width;
	int height;
	int * pImgData;
	int ** ppImgIndex;
}
s_Img_32i;
//
//typedef struct s_IntegImg_32i
//{
//	int caseNum;
//	int ** ppIntegImg;
//	int width;
//	int height;
//}
//s_IntegImg_32i;
// typedef struct s_ReferScope
// {
// 	s_Point referPoint;
// 	s_Rect scopeRect;
// }
// s_ReferScope;

typedef struct
{
	int width;
	int height;
	double whRatio; // width/height
}
s_RectSizeInfo;

typedef struct s_RotateAngle
{
	int x;
	int y;
	int r;
	int halfr;
}
s_RotateAngle;

// ��������
typedef enum e_NormType 
{ 
	n1_norm, n2_norm, max_norm 
}
e_NormType;

//��������
typedef enum data_type 
{
	type_int32, type_double, type_int16, type_byte, type_float 
}
data_type;

//ͼ������
typedef enum ImageType
{
	it_gray, it_flipgray, it_RGB24, it_flipRGB24, it_BGR24, it_flipBGR24, it_YUV444, it_YUV422,
}ImageType;

// ������ʾ�������飬���ڼ���ĳЩ���������ֱ��ͼ����
typedef struct s_RegFeat
{
	int normCase;
	s_Rect rect;
	int area;
}
s_RegFeat;

typedef struct s_RegFeatArray
{
	s_RegFeat * pFeatArray;
	int featNum;
}
s_RegFeatArray;

// ���ڶ���haar΢�ṹ��Ϣ
typedef struct s_HaarPara
{
	int modelWidth;
	int modelHeight;
}
s_HaarPara;

#define MAX_RECT_NUM 4
typedef struct s_HaarFeat
{
	int haarCase;
	int times[MAX_RECT_NUM]; // shift to right����times��ʾ��������չ
	s_Rect rect[MAX_RECT_NUM];
	int area[MAX_RECT_NUM];
	int rectNum;
}
s_HaarFeat;

typedef struct s_HaarFeatPool
{
	s_HaarFeat * pFeatArray;
	int featNum;
	int modelWidth;
	int modelHeight;
}
s_HaarFeatPool;

//����ͼ��Ķ���
typedef struct s_IntegIntegSqImg
{
	int planeNum;
	int width;
	int height;
	double **ppData;
}
s_IntegIntegSqImg;

// ָ��ÿ����һ��HOG�����ľ�����Ŀ�Ͷ����������
typedef struct s_NormedHOGReg
{
	int rectNum;
	s_Rect *pRegArray;
}
s_NormedHOGReg;

// ���ڼ�¼���ٹ�һ��HOG����
// HOGRegNumΪHOG������Ŀ��ÿ����Ӧ���ڵ�һ�����
// directNumָ��HOG�Ĺ�һ������
// bSignedָ��HOG�ķ����Ƿ�Ϊ�з��ŵ�
typedef struct s_NormedHOGRegArray
{
	int bSigned;
	int directNum;
	int HOGRegNum;
	s_NormedHOGReg * pNormedHOGRegArray;
}
s_NormedHOGRegArray;

extern "C"
{
	//////////////////////////////////////////////////////////////////////////
	//�������ܣ�����ָ���������͵ĳ���                                      //
	//////////////////////////////////////////////////////////////////////////
	static inline int GetDataSize( const data_type dataType )
	{
		int dataSize;

		switch( dataType )
		{
		case type_int32:
			dataSize = (sizeof(int));
			break;
		case type_double:
			dataSize = (sizeof(double));
			break;
		case type_byte:
			dataSize = (sizeof(byte));
			break;
		case type_int16:
			dataSize = (sizeof(int16));
			break;
		case type_float:
			dataSize = (sizeof(float));
			break;
		default:
			return(false);
			break;
		}

		return( dataSize );
	};

	//����dword�͵�ƽ����
	static inline dword Sqrt( dword sqVal )
	{
		unsigned long divisor;
		int i;

		dword root = 0; // ����
		unsigned long rem = 0;// ÿ�δ���������

		for( i=0; i<16; i++ )
		{
			root <<= 1;
			rem = ((rem << 2) + (sqVal >> 30));
			sqVal <<= 2;
			divisor = (root<<1) + 1;
			if( divisor <= rem )
			{
				rem -= divisor;
				root++;
			}
		}

		return( root );
	};
	
	static inline void StartRand()
	{
		srand( (unsigned)time( NULL ) );
	}

	//////////////////////////////////////////////////////////////////////////
	//�������ܣ�����[min��max]��Χ�ڵ�int�͵������ ��                      //
	//          ��min < max ,����(min��max)��Χ�ڵ�int�͵������            //
	//          ��min = max ,����min                                        //
	//          ��min > max ,����min - 1                                    //
	//////////////////////////////////////////////////////////////////////////
	static inline int GetRand( int Min, int Max )
	{
		if( Min < Max )
		{
			double temp1 = (double)rand()/(double)RAND_MAX;
			int temp2 = Max-Min;
			int temp3 = (int)( temp1*temp2+0.5 );
			if( temp3 < 0 )
			{
				temp3 = 0;
			}
			else if( temp3 > temp2 )
			{
				temp3 = temp2;
			}
			return( temp3 + Min );
		}
		else 
			if( Min == Max )
			{
				return( Min );
			}
			else
			{
				return( Min-1 );
			}
	};


	//////////////////////////////////////////////////////////////////////////
	//�������ܣ�����[min��max]��Χ�ڵ�double�͵������ ��                   //
	//          ��min < max ,����(min��max)��Χ�ڵ�double�͵������         //
	//          ��min = max ,����min                                        //
	//          ��min > max ,����min - 1                                    //
	//////////////////////////////////////////////////////////////////////////
	static inline double GetRand_64f( double Min, double Max )
	{
		if( Min < Max )
		{
			double temp1 = rand()/(double)RAND_MAX;
			double temp2 = Max-Min;
			double temp3 = temp1*temp2;
			if( temp3 < 0 )
			{
				temp3 = 0;
			}
			else if( temp3 > temp2 )
			{
				temp3 = temp2;
			}
			return( temp3 + Min );
		}
		else 
			if( fabs(Min-Max) < 1e-20 )
			{
				return( Min );
			}
			else
			{
				return( Min-1 );
			}
	};



	// ����true�ĸ���ԼΪrandRatio
	static inline bool BeRandVld( double randRatio )
	{
		int curRand = rand();

		return( curRand/(double)RAND_MAX < randRatio );
	}



	//----------------------------�����--------------------------------------------------------------//
	
	//Ϊs_Point�ṹ��ֵ
	static inline s_Point SetPoint( int x, int y )
	{
		s_Point tempPoint;
		tempPoint.x = x;
		tempPoint.y = y;
		return( tempPoint );
	};

	//����ƫ���ˣ�shiftx��shifty��������
	static inline s_Point ShiftPoint( s_Point srcPoint, int shiftx, int shifty )
	{
		s_Point tempPoint;
		tempPoint.x = srcPoint.x + shiftx;
		tempPoint.y = srcPoint.y + shifty;
		return( tempPoint );
	};

	//����ƫ���ˣ�shiftx��shifty��������
	static inline s_Point_f64 ShiftPoint_f64( s_Point_f64 srcPoint, int shiftx, int shifty )
	{
		s_Point_f64 tempPoint;
		tempPoint.x = srcPoint.x + shiftx;
		tempPoint.y = srcPoint.y + shifty;
		return( tempPoint );
	};

	//����������ŷ�Ͼ���
	static inline int GetPointDis( s_Point point1, s_Point point2 )
	{
		int xDis = point1.x - point2.x;
		int yDis = point1.y - point2.y;

		return( Sqrt( xDis * xDis + yDis * yDis ) );
	};

	//����������ŷ�Ͼ���
	static inline double GetPointDis_f64( s_Point point1, s_Point point2 )
	{
		double xDis = point1.x - point2.x;
		double yDis = point1.y - point2.y;

		return( sqrt( xDis * xDis + yDis * yDis ) );
	};

	//�������������ĵ�
	static inline s_Point GetCenterPoint( s_Point point1, s_Point point2 )
	{
		return( SetPoint( ( point1.x + point2.x + 1 ) / 2 , ( point1.y + point2.y + 1 ) / 2 ) );
	};

	static inline s_Point ZoomPoint_64f( s_Point * pPoint, double zoomRatio )
	{
		s_Point desPoint;
		desPoint.x = (int)( pPoint->x * zoomRatio );
		desPoint.y = (int)( pPoint->y * zoomRatio );
		return( desPoint );
	};




	//----------------------------�������--------------------------------------------------------------//
	//Ϊrect��ֵ
	static inline s_Rect SetVifdRect( int left, int top, int right, int bottom )
	{
		s_Rect tempRect;
		tempRect.left = left;
		tempRect.top = top;
		tempRect.right = right;
		tempRect.bottom = bottom;
		return( tempRect );
	};

	//����rectָ���������
	static inline int GetRectArea( s_Rect rect )
	{
		return( (rect.right - rect.left) * (rect.bottom-rect.top) );
	};

	//�����������
	static inline int GetRectArea_Size( s_RectSize rectSize )
	{
		return( rectSize.width*rectSize.height );
	};

	//��val�޶���[min,max]��
	static inline void  LimitVal_basc( int* pVal, int minVal, int maxVal )
	{
		if( (*pVal) < minVal )
		{
			(*pVal) = minVal;
		}
		else 
			if( (*pVal) > maxVal )
			{
				(*pVal) = maxVal;
			}
	}

	//�ж�pRect�Ƿ���ָ������limitRange��
	static inline bool LimitRect( s_Rect * pRect, s_Rect limitRange )
	{
		LimitVal_basc( &(pRect->left), limitRange.left, limitRange.right );
		LimitVal_basc( &(pRect->right), limitRange.left, limitRange.right );
		LimitVal_basc( &(pRect->top), limitRange.top, limitRange.bottom );
		LimitVal_basc( &(pRect->bottom), limitRange.top, limitRange.bottom );

		return( pRect->right > pRect->left && pRect->bottom > pRect->top );
	};


	//�������ܣ����ؿ�ΪdesWidth�� ��ΪdesHeight������srcRectӵ�й�ͬ���ĵ������
	static inline s_Rect GetRectSameCenter( s_Rect srcRect, int desWidth, int desHeight )
	{
		int srcWidth = srcRect.right - srcRect.left;
		int srcHeight = srcRect.bottom - srcRect.top;
		int leftShift = (desWidth - srcWidth) / 2;
		int rightShift = (desWidth - srcWidth) - leftShift;
		int topShift = (desHeight - srcHeight) / 2;
		int bottomShift = (desHeight - srcHeight) - topShift;
		s_Rect desRect;
		desRect.left = srcRect.left - leftShift;
		desRect.right = srcRect.right + rightShift;
		desRect.top = srcRect.top - topShift;
		desRect.bottom = srcRect.bottom + bottomShift;
		return(desRect);
	};

	//�õ���ָ������int leftLimit, int topLimit, int rightLimit, int bottomLimi���ڣ�
	//ָ�����ĵ㣨centerX, centerY����ָ����rectWidth, ָ����int rectHeight������
	static inline s_Rect GetValidRect(  int centerX, int centerY, int rectWidth, int rectHeight, int leftLimit, int topLimit, 
		int rightLimit, int bottomLimit )
	{
		int halfWidth = rectWidth / 2;
		int halfHeight = rectHeight / 2;
		s_Rect validRect;
		if( (centerX - halfWidth) - leftLimit< rightLimit - (centerX + halfWidth) )
		{
			validRect.left = max( leftLimit, centerX - halfWidth );
			validRect.right = validRect.left + rectWidth;
		}
		else
		{
			validRect.right = min( rightLimit, centerX+halfWidth );
			validRect.left = validRect.right - rectWidth;
		}

		if( (centerY - halfHeight) - topLimit < bottomLimit - (centerY + halfHeight) )
		{
			validRect.top = max( topLimit, centerY - halfHeight);
			validRect.bottom = validRect.top + rectHeight;
		}
		else
		{
			validRect.bottom = min( bottomLimit, centerY + halfHeight );
			validRect.top = validRect.bottom - rectHeight;
		}

		return( validRect );
	};

	//����pRect�Ƿ������� int leftLimit, int topLimit, int rightLimit, int bottomLimit����
	static inline bool IsValidRect(  s_Rect* pRect, int leftLimit, int topLimit, int rightLimit, int bottomLimit )
	{
		if( pRect->left >= leftLimit && pRect->top >= topLimit && pRect->right <= rightLimit && pRect->bottom <= bottomLimit )
		{
			return( true );
		}
		else
		{
			return( false );
		}
	};

	//�õ�rect�Ŀ��
	static inline s_RectSize GetRectSize( s_Rect rect )
	{
		s_RectSize rectSize;
		rectSize.width = rect.right - rect.left;
		rectSize.height = rect.bottom - rect.top;
		return( rectSize );
	};

	//�õ�rect�Ŀ��
	static inline void GetRectSize_WH( int* pWidth, int* pHeight, s_Rect rect )
	{
		(*pWidth) = rect.right - rect.left;
		(*pHeight) = rect.bottom - rect.top;
	};

	//�õ�
	static inline s_Rect GetVerFlipRect( s_Rect srcRect, int width )
	{
		return( SetVifdRect( width - srcRect.right, srcRect.top, width - srcRect.left, srcRect.bottom ) );
	};

	//�õ�rect�����ĵ�
	static inline s_Point GetRectCenterPoint( s_Rect rect )
	{
		return( SetPoint( ((rect.left + rect.right+1)>>1), ((rect.top + rect.bottom+1)>>1) ) );
	};

	// ��Ծ������ķ������Σ��������겻�䣬����������������
	// ��Ҫ�Դ����������Ƿ񳬳�ͼ��Χ�ж�
	static inline s_Rect EnlargeRect_64f( s_Rect * pRect, double widthZoomRatio, double heightZoomRatio )
	{
		double widthStep;
		double heightStep;

		s_Rect desRect = (*pRect);
		if( fabs( widthZoomRatio-1) > 1e-20 )
		{
			widthStep = (pRect->right - pRect->left)*(widthZoomRatio - 1)/2;

			desRect.left = ROUND_uint32( pRect->left - widthStep );
			desRect.right = ROUND_uint32( pRect->right + widthStep );
		}

		if( fabs( heightZoomRatio-1) > 1e-20 )
		{
			heightStep = (pRect->bottom - pRect->top) * (heightZoomRatio - 1) / 2;

			desRect.top = ROUND_uint32( pRect->top - heightStep );
			desRect.bottom = ROUND_uint32( pRect->bottom + heightStep );
		}

		return( desRect );
	};

	// �������ϣ��£�������������� zoomRatio ��
	// ����λ��Ҳ�Ŵ��� zoomRatio ��
	static inline s_Rect ZoomRect_64f( s_Rect rect, double zoomRatio )
	{
		return( SetVifdRect( ROUND_uint32(rect.left*zoomRatio), ROUND_uint32(rect.top*zoomRatio), 
			ROUND_uint32(rect.right*zoomRatio), ROUND_uint32(rect.bottom*zoomRatio) ) );
	};

	//�������ϣ��£�������������� zoomRatio ��
	static inline void ResizeRect( s_Rect * pDesRect, s_Rect srcRect, double sizeRatio )
	{
		pDesRect->left = (int)(srcRect.left*sizeRatio + 0.5);
		pDesRect->top = (int)(srcRect.top*sizeRatio + 0.5);
		pDesRect->right = (int)( srcRect.right*sizeRatio + 0.5 );
		pDesRect->bottom = (int)( srcRect.bottom*sizeRatio + 0.5 );
	};

	//Ϊs_RectSize��ֵ
	static inline s_RectSize SetVifdRectSize( int width, int height )
	{
		s_RectSize tempRectSize;
		tempRectSize.width = width;
		tempRectSize.height = height;
		return( tempRectSize );
	};

	//�õ�����rect��ƽ��size
	static inline s_RectSize GetAverageRectSize( s_RectSize tempRectSize1, s_RectSize tempRectSize2 )
	{
		return( SetVifdRectSize( (tempRectSize1.width + tempRectSize2.width+1) / 2, (tempRectSize1.height + tempRectSize2.height + 1 ) / 2 ) );

	};

	//�õ�ָ�����ĵ�Ϳ�ߵ�rect
	static inline s_Rect SetRect_CenterSize( int centerX, int centerY, int width, int height )
	{
		s_Rect rect;
		rect.left = centerX-(width+1)/2;
		rect.right = rect.left+width;
		rect.top = centerY-(height+1)/2;
		rect.bottom = rect.top + height;

		return( rect );
	};

	static inline void ExchangeToSortData( int* pMin, int* pMax )
	{
		int temp;
		if( (*pMin) > (*pMax) )
		{
			temp = (*pMin);
			(*pMin) = (*pMax);
			(*pMax) = temp;
		}
	};

	//��ƫ�ƺ��rect
	static inline s_Rect ShiftRect( s_Rect srcRect, int shiftx, int shifty )
	{
		srcRect.left += shiftx;
		srcRect.right +=  shiftx;

		srcRect.top += shifty;
		srcRect.bottom += shifty;
		return( srcRect );
	};

	// if rect.bottom < rect.top, exchange
	// if rect.right < rect.left, exchange
	// shift rect to make left = 0, top = 0;
	static inline s_Rect NormRect( s_Rect rect )
	{
		ExchangeToSortData( &rect.left, &rect.right );
		ExchangeToSortData( &rect.top, &rect.bottom );
		ShiftRect( rect, -rect.left, -rect.top );
		return( rect );
	};


	//���ط�Χ��ָ�������ڵ�һ�������ΪfixedRatio���������
	static inline bool GetRandRect_FixedRatio( s_Rect * pRandRect, s_Rect * pRegion, int minWidth, double fixedRatio )
	{
		int maxWidth = min( pRegion->right - pRegion->left, (int)( (pRegion->bottom-pRegion->top) / fixedRatio ) );

		if( minWidth > maxWidth )
		{
			return( false );
		}
		else
		{
			int width = GetRand( minWidth, maxWidth );
			int height = (int)( width*fixedRatio );

			pRandRect->left = GetRand( pRegion->left, (pRegion->right - width) );
			pRandRect->right = pRandRect->left+width;
			pRandRect->top = GetRand( pRegion->top, (pRegion->bottom - height) );
			pRandRect->bottom = pRandRect->top+height;

			return( true );
		}
	};



	//----------------------------��������ϲ���--------------------------------------------------------------//
	//�ж�һ���Ƿ���������
	static inline bool IsPointInRect( s_Point point, s_Rect rect )
	{
		if( point.x >= rect.left && point.x < rect.right && point.y >= rect.top && point.y < rect.bottom )
		{
			return( true );
		}
		else
		{
			return( false );
		}
	};

	//�ж�����rect�Ƿ��н������򣬲��õ�����ȥ
	static inline bool GetIntersectRect( s_Rect* pInterSectRect, s_Rect* pRect1, s_Rect* pRect2 )
	{
		pInterSectRect->left = max( pRect1->left, pRect2->left );
		pInterSectRect->right = min( pRect1->right, pRect2->right );
		pInterSectRect->top = max( pRect1->top, pRect2->top );
		pInterSectRect->bottom = min( pRect1->bottom, pRect2->bottom );

		return( (pInterSectRect->right >= pInterSectRect->left) && (pInterSectRect->bottom >= pInterSectRect->top) );
	};

	//�õ����������������
	static inline int GetIntersectRectArea( s_Rect * pRect1, s_Rect * pRect2 )
	{
		int left = max( pRect1->left, pRect2->left );
		int right = min( pRect1->right, pRect2->right );
		int top = max( pRect1->top, pRect2->top );
		int bottom = min( pRect1->bottom, pRect2->bottom );
		if( right > left && bottom > top )
		{
			return( (right - left)*(bottom - top) );
		}
		else
		{
			return( 0 );
		}
	};

	//������rect��Ŀ�߱ȵĳ˻�
	static inline double GetSizeSimRatio( s_Rect* pRect1, s_Rect* pRect2 )
	{
		int width1 = pRect1->right - pRect1->left;
		int height1 = pRect1->bottom - pRect1->top;

		int width2 = pRect2->right - pRect2->left;
		int height2 = pRect2->bottom - pRect2->top;

		double widthRatio;
		double heightRatio;

		if( ( width1 == 0 && width2 != 0 ) || ( width1 != 0 && width2 == 0 ) )
		{
			return( 0.0 );
		}
		else if( width1 == 0 && width2 == 0 )
		{
			return( 1.0 );
		}
		else
		{
			widthRatio = (double)width2 / (double)width1;
			if( widthRatio > 1 )
			{
				widthRatio = 1 / widthRatio;
			}

			heightRatio = (double)height2 / (double)height1;
			if( heightRatio > 1 )
			{
				heightRatio = 1 / heightRatio;
			}

			return( widthRatio * heightRatio );
		}
	};

	//
	static inline bool DoesSimRect( s_Rect * pRect0, s_Rect * pRect1, double disRatioThresh, double sizeSimRatioThresh )
	{
		int disThresh = max( 1, (int)( ( ( pRect0->right - pRect0->left + pRect0->bottom - pRect0->top
			+pRect1->right - pRect1->left + pRect1->bottom - pRect1->top ) >> 2 ) * disRatioThresh+0.5 ) );

		if( GetPointDis( GetRectCenterPoint( *pRect0 ), GetRectCenterPoint(*pRect1) ) < disThresh
			&& GetSizeSimRatio( pRect0, pRect1 ) > sizeSimRatioThresh )
		{
			return( true );
		}
		else
		{
			return( false );
		}
	}
	static inline bool DoesSimRectExist( s_Rect* pRectArray, int rectNum, s_Rect* pRandRect, double disRatioThresh, double sizeSimRatioThresh )
	{
		for( int order = 0; order < rectNum; ++ order )
		{
			if( DoesSimRect( pRectArray+order, pRandRect, disRatioThresh, sizeSimRatioThresh ) )
			{
				return( true );
			}
		}

		return( false );
	};


	static inline bool DoesSimRectInArray( s_Rect * pRectArray, int rectNum, s_Rect * pRect1, double disRatioThresh, double sizeSimRatioThresh )
	{
		int i;

		for( i = 0; i< rectNum; ++ i )
		{
			if( DoesSimRect( &(pRectArray[i]), pRect1, disRatioThresh, sizeSimRatioThresh ) )
			{
				return( true );
			}
		}

		return( false );
	};

	//

	//static inline bool IsSameObject( s_Rect tempObject1, s_Rect tempObject2 )
	



	static inline double GetRectCoverRatio( s_Rect tempObject1, s_Rect tempObject2 )
	{
		int coverLeft = max( tempObject1.left, tempObject2.left );
		int coverRight = min( tempObject1.right, tempObject2.right );
		int coverTop = max( tempObject1.top, tempObject2.top );
		int coverBottom = min( tempObject1.bottom, tempObject2.bottom );

		int area1;
		int area2;
		int minArea;
		int coverArea;

		if( coverLeft < coverRight && coverTop < coverBottom ) // ����
		{
			area1 = GetRectArea( tempObject1 );
			area2 = GetRectArea( tempObject2 );
			minArea = min( area1, area2 );
			coverArea = (coverRight-coverLeft)*(coverBottom-coverTop);

			return( coverArea/(double)minArea );
		}
		else
		{
			return( 0 );
		}
	};

	//ɾ��rectNum��С���������С��minSize�����򣬲�����ʣ�����������
	static inline int DeleteSmallRect( s_Rect *pRectArray, int rectNum, int minSize )
	{
		int vldOrder;
		int i;

		vldOrder = 0;

		for( i = 0; i< rectNum; ++ i )
		{
			if( ( pRectArray[i].right - pRectArray[i].left ) * ( pRectArray[i].bottom-pRectArray[i].top ) >= minSize )
			{
				pRectArray[vldOrder] = pRectArray[i];
				vldOrder ++;
			}
		}

		return( vldOrder );
	};

	//�ж��������ο��Ƿ�ˮƽ����
	// �߶ȱ�Ҫ����һ����������ֱ���򽻵�����Ҫ����һ��Ҫ�󣬾���С��һ���̶�
	static inline bool IsHorNeighborRect( s_Rect tempObject1, s_Rect tempObject2, float sizeRatioThresh, float coverRatioThresh, float disRatioThresh )
	{
		int width1 = tempObject1.right-tempObject1.left;
		int height1 = tempObject1.bottom-tempObject1.top;
		int width2 = tempObject2.right-tempObject2.left;
		int height2 = tempObject2.bottom-tempObject2.top;

		float heightratio = height2/(float)height1;
		if( heightratio > 1 )
		{
			heightratio = 1.0f/heightratio;
		}

		// ����߶ȱ����̫������Ϊ�������ھ���
		if( heightratio < sizeRatioThresh )
		{
			return( false );
		}

		int avgHeight = (height1+height2+1)/2;
		int coverTop = max( tempObject1.top, tempObject2.top );
		int coverBottom = min( tempObject1.bottom, tempObject2.bottom );
		int coverHeight = coverBottom-coverTop;

		// ��ֱ�����Ͻ�������̫С������Ϊ�����ڽ���
		if( coverHeight <= 0 || (coverHeight/(float)avgHeight) < coverRatioThresh )
		{
			return( false );
		}

		int coverLeft = max( tempObject1.left, tempObject2.left );
		int coverRight = min( tempObject1.right, tempObject2.right );

		int coverWidth = coverRight-coverLeft;
		//	int avgWidth = (width1+width2+1)/2;

		// ���ˮƽ����С��һ���̶ȣ�����Ϊ�ཻ
		return( coverWidth >= 0 || (-coverWidth)/(float)max(width1, width2) < disRatioThresh );
	};

	// �ж��������ο��Ƿ�ֱ����
	// ��ȱ�Ҫ����һ��������ˮƽ���򽻵�����Ҫ����һ��Ҫ�󣬴�ֱ����С��һ���̶�
	static inline bool IsVerNeighborRect( s_Rect tempObject1, s_Rect tempObject2, float sizeRatioThresh, float coverRatioThresh, float disRatioThresh )
	{
		int width1 = tempObject1.right-tempObject1.left;
		int height1 = tempObject1.bottom-tempObject1.top;
		int width2 = tempObject2.right-tempObject2.left;
		int height2 = tempObject2.bottom-tempObject2.top;

		float widthratio = width2/(float)width1;
		if( widthratio > 1 )
		{
			widthratio = 1.0f/widthratio;
		}

		// �����ȱ����̫������Ϊ�������ھ���
		if( widthratio < sizeRatioThresh )
		{
			return( false );
		}

		int coverLeft = max( tempObject1.left, tempObject2.left );
		int coverRight = min( tempObject1.right, tempObject2.right );

		int coverWidth = coverRight-coverLeft;
		int avgWidth = (width1+width2+1)/2;

		// ˮƽ�����Ͻ�������̫С������Ϊ�����ڽ���
		if( coverWidth <= 0 || (coverWidth/(float)avgWidth) < coverRatioThresh )
		{
			return( false );
		}

		int coverTop = max( tempObject1.top, tempObject2.top );
		int coverBottom = min( tempObject1.bottom, tempObject2.bottom );

		int coverHeight = coverBottom-coverTop;
		//	int avgHeight = (width1+width2+1)/2;

		// �����ֱ����С��һ���̶ȣ�����Ϊ�ཻ
		return( coverHeight >= 0 || (-coverHeight)/(float)max( height1, height2 ) < disRatioThresh );
	};

	static inline bool IsCoverObject( s_Rect tempObject1, s_Rect tempObject2, double coverRatioThresh )
	{
		int coverLeft = max( tempObject1.left, tempObject2.left );
		int coverRight = min( tempObject1.right, tempObject2.right );
		int coverTop = max( tempObject1.top, tempObject2.top );
		int coverBottom = min( tempObject1.bottom, tempObject2.bottom );

		int area1;
		int area2;
		int minArea;
		int coverArea;

		if( coverLeft < coverRight && coverTop < coverBottom ) // ����
		{
			area1 = GetRectArea( tempObject1 );
			area2 = GetRectArea( tempObject2 );
			minArea = min( area1, area2 );
			coverArea = (coverRight-coverLeft)*(coverBottom-coverTop);

			if( coverArea >= (int)(minArea*coverRatioThresh+0.5) )
			{
				return( true );
			}
			else
			{
				return( false );
			}
		}
		else
		{
			return( false );
		}
	};

	//�ں���������
	static inline int MergeNeighborRect( s_Rect* pRectArray, int rectNum )
	{
		int i;
		int j;

		s_Rect * rect1;
		s_Rect * rect2;

		int vldOrder;
		int * pValid;

		if( rectNum <= 0 )
		{
			return( 0 );
		}

		pValid = (int *)malloc( sizeof(int)*rectNum );
		for( i = 0; i< rectNum; ++ i )
		{
			pValid[i] = 1;
		}

		// �ϲ�ˮƽ���ߴ�ֱ��������
		for( i = 0; i< rectNum; ++ i )
		{
			if( pValid[i] == 1 )
			{
				rect1 = &(pRectArray[i]);
				//			TRACE( "rect1 = %d_%d_%d_%d\n", rect1->left, rect1->top, rect1->right, rect1->bottom );
				for( j = i+1; j< rectNum; ++ j )
				{
					if( pValid[j] == 1 )
					{
						rect2 = &(pRectArray[j]);
						//					TRACE( "rect2 = %d_%d_%d_%d\n", rect2->left, rect2->top, rect2->right, rect2->bottom );
						if( IsHorNeighborRect( *rect1, *rect2, 0.67f, 0.4f, 0.5f ) || 
							IsVerNeighborRect( *rect1, *rect2, 0.67f, 0.4f, 0.5f ) || 
							IsCoverObject( *rect1, *rect2, 0.36 ) )
						{
							// �ںϲ����¾��ο�
							rect1->left = min( rect1->left, rect2->left );
							rect1->top = min( rect1->top, rect2->top );
							rect1->right = max( rect1->right, rect2->right );
							rect1->bottom = max( rect1->bottom, rect2->bottom );
							// ɾ������һ�����ο�
							pValid[j] = 0;
						}
					}
				}
			}
		}

		// ɾ����Ч����
		vldOrder = 0;
		for( i = 0; i< rectNum; ++ i )
		{
			if( pValid[i] == 1 )
			{
				pRectArray[vldOrder] = pRectArray[i];
				vldOrder ++;
			}
		}

		FREE( pValid );

		return( vldOrder );
	};

	// int maxdataSizeΪ����������Ŀ
	static inline void InitializeRectArray( s_RectArray * pArray, int maxdataSize )
	{
		pArray->maxNum = max( 1, maxdataSize ); // can not be zero
		pArray->actNum = 0;

		pArray->pArray = (s_Rect *)malloc( pArray->maxNum*sizeof(s_Rect) );
	};

	// �ͷŶ����ڴ�
	static inline void RemoveRectArray( s_RectArray * pArray )
	{
		if( pArray->pArray != NULL )
		{
			FREE( pArray->pArray );
		}
		pArray->actNum = 0;
	};

	//���������ۼӺ���������ֵ
	static inline int GetPercentSumIndex( float ratio, float * pHist, int binNum, int vldNum )
	{
		int i;

		int percentsum;
		percentsum = (int)( ratio*vldNum+0.5 );

		if( percentsum <= 0 )
		{
			return( 0 );
		}
		else if( percentsum >= vldNum )
		{
			return( binNum-1 );
		}
		else
		{
			float sum;
			sum = 0;
			for( i = 0; i< binNum; ++ i )
			{
				sum += pHist[i];
				if( sum >= percentsum )
				{
					break;
				}
			}

			return( i );
		}
	};
	
	///////////////// �����ǹ�����ת�ĺ��� /////////////////////////////////
	
	// �õ��������������ˮƽ�ĽǶ�
	static inline void GetRectifyAngle_64f( double * pSinAngle, double * pCosAngle, s_Point point0, s_Point point1 )
	{
		int xDis;
		int yDis;
		
		xDis = point1.x-point0.x;
		yDis = point0.y-point1.y;
		
		double dis;
		dis = sqrt( (double)(xDis*xDis+yDis*yDis) );
		
		(*pSinAngle) = yDis/dis;
		(*pCosAngle) = xDis/dis;
	};
	
	// ���������ǶȺͽǵ�cos��sinֵ
	static inline void AddAngle_64f( double * pDesSinAngle, double * pDesCosAngle, double sinAngle0, double cosAngle0, double sinAngle1, double cosAngle1 )
	{
		(*pDesSinAngle) = sinAngle0*cosAngle1+cosAngle0*sinAngle1;
		(*pDesCosAngle) = cosAngle0*cosAngle1-sinAngle0*sinAngle1;
	};
	
	// ����������֮��ļнǣ������������
	static inline double GetRotAngle_64f( s_Point srcOriginPoint, s_Point srcPoint2, s_Point desOriginPoint, s_Point desPoint2 )
	{
		double rotAngle;
		double cosRotAngle;
		double sinRotAngle;
		
		double sinSrcRotAngle;
		double cosSrcRotAngle;
		double srcx;
		double srcy;
		double srcr;
		double sinDesRotAngle;
		double cosDesRotAngle;
		double desx;
		double desy;
		double desr;
		
		srcx = srcPoint2.x-srcOriginPoint.x;
		srcy = srcPoint2.y-srcOriginPoint.y;
		srcr = sqrt( (double)srcx*srcx+srcy*srcy );
		sinSrcRotAngle = srcy/srcr;
		cosSrcRotAngle = srcx/srcr;
		
		desx = desPoint2.x-desOriginPoint.x;
		desy = desPoint2.y-desOriginPoint.y;
		desr = sqrt( (double)desx*desx+desy*desy );
		sinDesRotAngle = desy/desr;
		cosDesRotAngle = desx/desr;
		
		// cos alfa2-alfa1
		cosRotAngle = cosDesRotAngle*cosSrcRotAngle+sinDesRotAngle*sinSrcRotAngle;
		// sin alfa2-alfa1
		sinRotAngle = sinDesRotAngle*cosSrcRotAngle-cosDesRotAngle*sinSrcRotAngle;
		
		if( sinRotAngle >= 0 )
		{
			rotAngle = acos(cosRotAngle);
		}
		else
		{
			rotAngle = 2*PI-acos(cosRotAngle);
		}
		
		return(rotAngle);
	};
	
	// �õ�ĳ��srcPoint���referPoint����תrotAngle���ȵĽ��
	static inline s_Point_f64 GetReferRotatePoint_f64( s_Point srcPoint, s_Point referPoint, double rotAngle )
	{
		s_Point_f64 referDesPoint;
		double cosRotAngle = cos(rotAngle);
		double sinRotAngle = sin(rotAngle);
		s_Point referSrcPoint = SetPoint( srcPoint.x-referPoint.x, srcPoint.y-referPoint.y );
		referDesPoint.x = (referSrcPoint.x*cosRotAngle-referSrcPoint.y*sinRotAngle);
		referDesPoint.y = (referSrcPoint.y*cosRotAngle+referSrcPoint.x*sinRotAngle);
		return( referDesPoint );
	};
	
	// ����srcPoint��Ե�srcReferPoint��ת��cosRotAngle��sinRotAngle����Ȼ��ƫ��desReferPoint
	static inline s_Point RotatePoint_CosSin( s_Point srcPoint, s_Point srcReferPoint, 
		s_Point desReferPoint, double cosRotAngle, double sinRotAngle )
	{
		s_Point referDesPoint;
		s_Point referSrcPoint = SetPoint( srcPoint.x-srcReferPoint.x, srcPoint.y-srcReferPoint.y );
		referDesPoint.x = (int)( referSrcPoint.x*cosRotAngle-referSrcPoint.y*sinRotAngle );
		referDesPoint.y = (int)( referSrcPoint.y*cosRotAngle+referSrcPoint.x*sinRotAngle );
		
		return( ShiftPoint( referDesPoint, desReferPoint.x, desReferPoint.y ) );
	};

	// coordinates y is from up to down, and angle is positive when rotate clockwise
	// sinAngle, float cosAngle, float sizeRatio�ֱ�ΪԴ�������Ŀ���������ת�Ƕȵ�����ֵ������ֵ�Լ������߶�
	// desOriginPoint and the srcOriginPoint is the corresponding point in source image and des image
	// Rect is the range, left and top is real range, it is enlarged one pixel at right and bottom
	static inline s_Rect RotateRectRange_CosSin(s_Rect srcRect, s_Point srcOriginPoint, s_Point desOriginPoint, 
			double sinAngle, double cosAngle, double sizeRatio)
	{
		s_Rect desRect;
		s_Point desPointArray[4];
		s_Point srcPoint;

		sinAngle *= sizeRatio;
		cosAngle *= sizeRatio;
		
		srcRect.right --;
		srcRect.bottom --;
		
		// first point
		srcPoint.x = srcRect.left;
		srcPoint.y = srcRect.top;
		desPointArray[0] = RotatePoint_CosSin( srcPoint, srcOriginPoint, desOriginPoint, cosAngle, sinAngle );
		desRect.left = desPointArray[0].x;
		desRect.right = desPointArray[0].x;
		desRect.top = desPointArray[0].y;
		desRect.bottom = desPointArray[0].y;
		
		// second point
		srcPoint.x = srcRect.right;
		srcPoint.y = srcRect.top;
		desPointArray[1] = RotatePoint_CosSin( srcPoint, srcOriginPoint, desOriginPoint, cosAngle, sinAngle );
		// get min x to be left
		if( desRect.left > desPointArray[1].x )
		{
			desRect.left = desPointArray[1].x;
		}
		else if( desRect.right < desPointArray[1].x ) // get max x to be right
		{
			desRect.right = desPointArray[1].x;
		}
		
		// get min y to be top
		if( desRect.top > desPointArray[1].y )
		{
			desRect.top = desPointArray[1].y;
		}
		else if( desRect.bottom < desPointArray[1].y ) // get max y to be bottom
		{
			desRect.bottom = desPointArray[1].y;
		}
		
		// third point
		srcPoint.x = srcRect.right;
		srcPoint.y = srcRect.bottom;
		desPointArray[2] = RotatePoint_CosSin( srcPoint, srcOriginPoint, desOriginPoint, cosAngle, sinAngle );
		// get min x to be left
		if( desRect.left > desPointArray[2].x )
		{
			desRect.left = desPointArray[2].x;
		}
		else if( desRect.right < desPointArray[2].x ) // get max x to be right
		{
			desRect.right = desPointArray[2].x;
		}
		
		// get min y to be top
		if( desRect.top > desPointArray[2].y )
		{
			desRect.top = desPointArray[2].y;
		}
		else if( desRect.bottom < desPointArray[2].y ) // get max y to be bottom
		{
			desRect.bottom = desPointArray[2].y;
		}
		
		// fourth point
		srcPoint.x = srcRect.left;
		srcPoint.y = srcRect.bottom;
		desPointArray[3] = RotatePoint_CosSin( srcPoint, srcOriginPoint, desOriginPoint, cosAngle, sinAngle );
		// get min x to be left
		if( desRect.left > desPointArray[3].x )
		{
			desRect.left = desPointArray[3].x;
		}
		else if( desRect.right < desPointArray[3].x ) // get max x to be right
		{
			desRect.right = desPointArray[3].x;
		}
		
		// get min y to be top
		if( desRect.top > desPointArray[3].y )
		{
			desRect.top = desPointArray[3].y;
		}
		else if( desRect.bottom < desPointArray[3].y ) // get max y to be bottom
		{
			desRect.bottom = desPointArray[3].y;
		}
		
		desRect.bottom ++;
		desRect.right ++;
		
		return( desRect );
	};

};

#endif // !defined(AFX_BASICDATATYPE_H__AB497EBE_BDF7_45C4_9B78_C54592D6410E__INCLUDED_)
