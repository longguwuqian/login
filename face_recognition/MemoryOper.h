// MemoryOper.h: 用于进行内存分配和释放.
// 邓亚峰 创建于2010年1月11日
// 修改记录：
// 记录一 ： 2010\01\12 王媛琼，将内存分配部分改为内联函数；加入static修饰符；以纯c方式编译；对于输入加入const修饰符 
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_MEMORYOPER_H__BDBB2707_1C5A_459C_B9A8_A9232D8D1D09__INCLUDED_)
#define AFX_MEMORYOPER_H__BDBB2707_1C5A_459C_B9A8_A9232D8D1D09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BasicDataType.h"

#include "memory.h"

extern "C" 
{

//--------------------------------对byte型2维数据操作-------------------------------------//
	//创建并返回2维byte型
	static inline byte **CreateMemory_2D_8u(IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		byte **ppMem = (byte **)malloc( sizeof(byte *) * rowNum );
		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
		{
			ppMem[rowOrder] = (byte *)malloc( sizeof(byte) * colNum );
		}
		return( ppMem );
	};

	//释放二维指针byte型的
	static inline void ReleaseMemory_2D_8u( OUT byte** ppMem, IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		if( ppMem != NULL )
		{
			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
			{
				FREE( ppMem[rowOrder] );
			}
			FREE( ppMem );
		}
	};

	
	//创建s_Data_2D_8u
	static inline void Create2DMem_2D_8u( OUT s_Data_2D_8u* pMem, IN const int width, IN const int height )
	{
		pMem->width = width;
		pMem->height = height;
		pMem->ppData = CreateMemory_2D_8u( pMem->height, pMem->width );
	};

	static inline void Set2DMemNull_2D_8u(IN OUT s_Data_2D_8u* pMem )
	{
		pMem->ppData = NULL;
		pMem->width = 0;
		pMem->height = 0;
	};

	//释放s_Data_2D_8u
	static inline void Release2DMem_2D_8u( IN OUT s_Data_2D_8u* pMem )
	{
		ReleaseMemory_2D_8u( pMem->ppData, pMem->height, pMem->width );
		pMem->ppData = NULL;
 		pMem->height = 0;
 		pMem->width  = 0;
	};

	
//--------------------------------对int型2维数据操作-------------------------------------//
	static inline int** CreateMemory_2D_32i( IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		int ** ppMem = (int **)malloc( sizeof(int *) * rowNum );
		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
		{
			ppMem[rowOrder] = (int *)malloc( sizeof(int) * colNum );
		}
		return( ppMem );

	};

	static inline void ReleaseMemory_2D_32i( IN OUT int** ppMem, IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		if( ppMem != NULL )
		{
			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
			{
				FREE( ppMem[rowOrder] );
			}
			FREE( ppMem );
		}
	};

	//创建s_Data_2D_32i
	static inline void Create2DMem_2D_32i( OUT s_Data_2D_32i* pMem, IN const int width, IN const int height )
	{
		pMem->width = width;
		pMem->height = height;
		pMem->ppData = CreateMemory_2D_32i( pMem->height, pMem->width );
	};

	static inline void Set2DMemNull_2D_32i(IN OUT s_Data_2D_32i* pMem )
	{
		pMem->ppData = NULL;
		pMem->width = 0;
		pMem->height = 0;
	};

	//释放s_Data_2D_32i
	static inline void Release2DMem_2D_32i(IN OUT s_Data_2D_32i* pMem )
	{
		ReleaseMemory_2D_32i( pMem->ppData, pMem->height, pMem->width );
		pMem->ppData = NULL;
		pMem->height = 0;
		pMem->width = 0;
	};


//--------------------------------对double型2维数据操作-------------------------------------//
	static inline double** CreateMemory_2D_64f( IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		double ** ppMem = (double **)malloc( sizeof(double *) * rowNum );
		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
		{
			ppMem[rowOrder] = (double *)malloc( sizeof(double) * colNum );
		}
		return( ppMem );
	};

	static inline void ReleaseMemory_2D_64f( IN OUT double** ppMem, IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		if( ppMem != NULL )
		{
			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
			{
				FREE( ppMem[rowOrder] );
			}
			FREE( ppMem );
		}
	};

	static inline void Create2DMem_2D_64f( OUT s_Data_2D_64f *pMem, IN const int width, IN const int height )
	{
		pMem->width = width;
		pMem->height = height;
		pMem->ppData = CreateMemory_2D_64f( pMem->height, pMem->width );
	};

	static inline void Set2DMemNull_2D_64f(IN OUT s_Data_2D_64f * pMem )
	{
		pMem->ppData = NULL;
		pMem->width = 0;
		pMem->height = 0;
	};

	static inline void Release2DMem_2D_64f( IN OUT s_Data_2D_64f *pMem )
	{
		ReleaseMemory_2D_64f( pMem->ppData, pMem->height, pMem->width );
		pMem->ppData = NULL;
		pMem->height = 0;
		pMem->width  = 0;
	};


//--------------------------------对byte型1维数据操作-------------------------------------//
	static inline void Create1DMem_1D_8u( IN OUT s_Data_1D_8u * pMem, IN const int width, IN const int height )
	{
		pMem->width = width;
		pMem->height = height;
		pMem->pData = (byte *)malloc( sizeof(byte) * pMem->height * pMem->width );
	};

	static inline void Release1DMem_1D_8u(IN OUT s_Data_1D_8u* pMem )
	{
		FREE( pMem->pData );
		pMem->width = 0;
		pMem->height = 0;
	};


//--------------------------------对int型1维数据操作-------------------------------------//
	static inline void Create1DMem_1D_32i( OUT s_Data_1D_32i* pMem, IN const int width, IN const int height )
	{
		pMem->width  = width;
		pMem->height = height;
		pMem->pData  = (int *)malloc( sizeof(int) * pMem->height * pMem->width );
	};

	static inline void Release1DMem_1D_32i( IN OUT s_Data_1D_32i* pMem )
	{
		FREE( pMem->pData );
		pMem->width  = 0;
		pMem->height = 0;
	};


//--------------------------------对double型1维数据操作-------------------------------------//
	static inline void Create1DMem_1D_64f( IN OUT s_Data_1D_64f* pMem, IN const int width, IN const int height )
	{
		pMem->width  = width;
		pMem->height = height;
		pMem->pData  = (double *)malloc( sizeof(double)*pMem->height*pMem->width );
	};
	static inline void Release1DMem_1D_64f( s_Data_1D_64f* pMem )
	{
		FREE( pMem->pData );
		pMem->width  = 0;
		pMem->height = 0;
	};
	
	
//--------------------------------对bool型2维数据操作-------------------------------------//
	static inline bool** CreateMemory_2D_1b( IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		bool ** ppMem = (bool **)malloc( sizeof(bool *) * rowNum );
		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
		{
			ppMem[rowOrder] = (bool *)malloc( sizeof(bool) * colNum );
		}
		return( ppMem );
	};

	static inline void ReleaseMemory_2D_1b(OUT bool** ppMem, IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		if( ppMem != NULL )
		{
			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
			{
				FREE( ppMem[rowOrder] );
			}
			FREE( ppMem );
		}
	};
//
////--------------------------------对short int型2维数据操作-------------------------------------//
//	static inline int16** CreateMemory_16s_2D( IN const int rowNum, IN const int colNum )
//	{
//		int rowOrder;
//		int16 ** ppMem = (int16 **)malloc( sizeof(int16 *)*rowNum );
//		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
//		{
//			ppMem[rowOrder] = (int16 *)malloc( sizeof(int16)*colNum );
//		}
//		return( ppMem );
//	};
//	static inline void ReleaseMemory_16s_2D( OUT int16** ppMem, IN const int rowNum, IN const int colNum )
//	{
//		int rowOrder;
//		if( ppMem != NULL )
//		{
//			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
//			{
//				FREE( ppMem[rowOrder] );
//			}
//			FREE( ppMem );
//		}
//	};

	
//--------------------------------对float型2维数据操作-------------------------------------//
	static inline float** CreateMemory_2D_32f( IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		float ** ppMem = (float **)malloc( sizeof(float *) * rowNum );

		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
		{
			ppMem[rowOrder] = (float *)malloc( sizeof(float)*colNum );
		}
		return( ppMem );
	};

	static inline void ReleaseMemory_2D_32f( OUT float** ppMem, IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		if( ppMem != NULL )
		{
			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
			{
				FREE( ppMem[rowOrder] );
			}
			FREE( ppMem );
		}
	};


//--------------------------------对char型2维数据操作-------------------------------------//
	static inline char** CreateMemory_2D_char( IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		char ** ppMem = (char **)malloc( sizeof(char *)*rowNum );
		for( rowOrder = 0; rowOrder< rowNum; rowOrder ++ )
		{
			ppMem[rowOrder] = (char *)malloc( sizeof(char)*colNum );
		}
		return( ppMem );
	};

	static inline void ReleaseMemory_2D_char( OUT char** ppMem, IN const int rowNum, IN const int colNum )
	{
		int rowOrder;
		if( ppMem != NULL )
		{
			for( rowOrder = 0; rowOrder < rowNum; rowOrder ++ )
			{
				FREE( ppMem[rowOrder] );
			}
			FREE( ppMem );
		}
	};



//--------------------------------图像数据操作部分-------------------------------------//
	static inline int GetImgBufferSize( IN const int width, IN const int height,IN const ImageType imgType )
	{
		switch( imgType )
		{
		case it_gray:
		case it_flipgray:

			return( width * height );

			break;

		case it_RGB24:
		case it_flipRGB24:
		case it_BGR24:
		case it_flipBGR24:
		case it_YUV444:

			return( width * height * 3 );

			break;

		case it_YUV422:

			return( width * height * 2 );

			break;

		default:

			return( -1 );
		}
	};

//--------------------------------byte型图像数据操作-------------------------------------//
	static inline byte* CreateImgBuffer( IN const int width, IN const int height, IN const ImageType imgType )
	{
		int bufferSize = GetImgBufferSize( width, height, imgType );

		return( bufferSize>0?( (byte *)malloc(sizeof(byte) * bufferSize) ):NULL );
	};


	static inline void SetNullImg_8u( IN OUT s_Img_8u* pImg )
	{
		pImg->pImgData = NULL;
		pImg->ppImgIndex = NULL;
		pImg->width = 0;
		pImg->height = 0;
	};

//	static inline void CrtImg_8u( s_Img_8u* pCurImg, int grad )
	static inline void CrtImg_8u( IN OUT s_Img_8u* pCurImg, IN const int width, IN const int height )
	{
// 		int width;
// 		int height;
		int h;
		int rowBytes;

		pCurImg->width = width;
		pCurImg->height = height;

//		pCurImg->grad = grad;
		rowBytes = width; // * pCurImg->grad;

		pCurImg->pImgData = (byte *)malloc( sizeof(byte) * height * rowBytes );
		pCurImg->ppImgIndex = (byte **)malloc( sizeof(byte *) * height );
		pCurImg->ppImgIndex[0] = pCurImg->pImgData;
		for( h = 1; h< height; h++ )
		{
			pCurImg->ppImgIndex[h] = pCurImg->ppImgIndex[h-1]+rowBytes;
		}
	};

	static inline void ReleaseImg_8u( IN OUT s_Img_8u* pImg )
	{
		FREE( pImg->pImgData );
		FREE( pImg->ppImgIndex );
		pImg->width = 0;
		pImg->height = 0;
	};


//--------------------------------short int型图像数据操作-------------------------------------//
	//static inline void SetNullImg_16s( s_Img_16s* pImg )
	//{
	//	pImg->pImgData = NULL;
	//	pImg->ppImgIndex = NULL;
	//};

	//static inline void CrtImg_16s( s_Img_16s* pCurImg, int width, int height )
	//{
	//	int width = pCurImg->width;
	//	int height = pCurImg->height;
	//	int h = 0;
	//	pCurImg->pImgData = (int16 *)malloc( width * height * sizeof(int16) );
	//	pCurImg->ppImgIndex = (int16 **)malloc( sizeof(int16 *) * height );
	//	pCurImg->ppImgIndex[0] = pCurImg->pImgData;
	//	for( h = 1; h< height; h++ )
	//	{
	//		pCurImg->ppImgIndex[h] = pCurImg->ppImgIndex[h - 1]+width;
	//	}
	//};

	//static inline void ReleaseImg_16s( s_Img_16s* pImg )
	//{
	//	FREE( pImg->pImgData );
	//	FREE( pImg->ppImgIndex );
	//};


//--------------------------------int型图像数据操作-------------------------------------//
	static inline void SetNullImg_32i( IN OUT s_Img_32i* pImg )
	{
		pImg->pImgData = NULL;
		pImg->ppImgIndex = NULL;
		pImg->width = 0;
		pImg->height = 0;
	};

	static inline void CrtImg_32i( OUT s_Img_32i* pCurImg, IN const int width, IN const int height )
	{
		int h;
		int rowBytes;

		pCurImg->width = width;
		pCurImg->height = height;

		rowBytes = width;

		pCurImg->pImgData = (int *)malloc( sizeof(int)*height*rowBytes );
		pCurImg->ppImgIndex = (int **)malloc( sizeof(int *)*height );
		pCurImg->ppImgIndex[0] = pCurImg->pImgData;
		for( h = 1; h< height; h++ )
		{
			pCurImg->ppImgIndex[h] = pCurImg->ppImgIndex[h-1]+rowBytes;
		}
	};

	static inline void ReleaseImg_32i( IN OUT s_Img_32i* pImg )
	{
		FREE( pImg->pImgData );
		FREE( pImg->ppImgIndex );
		pImg->width = 0;
		pImg->height = 0;
	};


//--------------------------------s_PointArray数据操作-------------------------------------//
	//maxdataSize为队列人脸数
	static inline void InitializePointArray( IN OUT s_PointArray* pArray, IN const int maxdataSize )
	{
		pArray->maxNum = max( 1, maxdataSize ); // can not be zero
		pArray->actNum = 0;

		pArray->pArray = (s_Point *)malloc( pArray->maxNum*sizeof(s_Point) );
	};

	static inline void RemovePointArray( IN OUT s_PointArray* pArray )
	{
		FREE( pArray->pArray );
		pArray->actNum = 0;
		pArray->maxNum = 0;
	};
};

#endif // !defined(AFX_MEMORYOPER_H__BDBB2707_1C5A_459C_B9A8_A9232D8D1D09__INCLUDED_)

