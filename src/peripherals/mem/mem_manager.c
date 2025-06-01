#include "../../../inc/peripherals/mem/mem_manager.h"

/*  参考文章
 *  https://www.armbbs.cn/forum.php?mod=viewthread&tid=89560
 *  http://mp.weixin.qq.com/s?__biz=MzU0MzQzMzc5Nw%3D%3D&chksm=fb0a3a89cc7db39f6eac3aba4551808f94257d8b8d3905b7b50ae5c03e028223294063e87848&idx=1&mid=2247487395&scene=21&sn=3ba04d465c860a9f04fed7ca8e97a3f5#wechat_redirect
 *  https://blog.csdn.net/DP29syM41zyGndVF/article/details/119121537
 */

/* CubeIDE生成项目不支持直接写 __align, 需要改为__ALIGNED , cmsis_gcc.h 可根据实际编译情况更改为其它文件 */
#include "cmsis_gcc.h"

/* 引入临界保护函数 */
#include "../../../inc/peripherals/core_interrupt.h"

/* 内存块大小不能 小于  MemoryMINIMUM_BLOCK_SIZE */
#define MemoryMINIMUM_BLOCK_SIZE	( ( size_t ) ( pMemoryStructSize << 1 ) )

/* 8字节 */
#define MemoryBITS_PER_BYTE			( ( size_t ) 8 )

#define BYTE_ALIGNMENT				(8)
#define BYTE_ALIGNMENT_MASK 		( 0x0007 )

// 大小定义
#define CCMRAMSIZE         64*1024     // 64KB CCM RAM			
// #define SDRAMSIZE          8*1024*1024 // 8MB SDRAM (典型配置)
#define SRAM_SIZE          64*1024     // 128KB大小,实际使用64KB					
// #define SRAM1SIZE          112*1024    // 112KB	
// #define SRAM2SIZE          16*1024     // 16KB

/* CubeIDE生成项目不支持直接写 __align, 需要改为__ALIGNED */
/* stm32cubeide里面的C语言编译器的文档，没有at这个属性，所以在keil中的at指向地址不能用，要改成section，否则报错 */
__ALIGNED(BYTE_ALIGNMENT) static uint8_t CCMRAM[CCMRAMSIZE] __attribute__((section(".ccmram")));
// __ALIGNED(BYTE_ALIGNMENT) static uint8_t SDRAMEX[SDRAMSIZE] __attribute__((section(".sram"));
__ALIGNED(BYTE_ALIGNMENT) static uint8_t SRAMIN[SRAM_SIZE];
// __ALIGNED(BYTE_ALIGNMENT) static uint8_t SRAMIN1[SRAM1SIZE] __attribute__((at(0x20000000)));
// __ALIGNED(BYTE_ALIGNMENT) static uint8_t SRAMIN2[SRAM2SIZE] __attribute__((at(0x2001C000)));


MemoryStruct SRAM_IN = {
	.pMemory = SRAMIN,
	.size = SRAM_SIZE,
	.pStart = {0},
	.pEnd = 0,
	.Free = 0,
	.MinFree = 0,
};

MemoryStruct CCM_RAM = {
	.pMemory = CCMRAM,
	.size = CCMRAMSIZE,
	.pStart = {0},
	.pEnd = 0,
	.Free = 0,
	.MinFree = 0,
};
/*
MemoryStruct SDRAM_EX = {
	.pMemory = SDRAMEX,
	.size = SDRAMSIZE,
	.pStart = {0},
	.pEnd = 0,
	.Free = 0,
	.MinFree = 0,
};
*/

/* 务必将要使用的内存添加到此处，不添加到此处的内存无法被使用 */
/* 支持 DMA 的内存 */
static MemoryStruct* mm_dma_capable_list[] = { &SRAM_IN };
/* 不支持 DMA 的内存 */
static MemoryStruct* mm_no_dma_capable_list[] = { &CCM_RAM };

static uint8_t mm_is_dma_capable;
/*-----------------------------------------------------------*/

/*合并内存*/
static void pInsertBlockIntoFreeList( MemoryStruct * mem , BlockLink_t *pxBlockToInsert );
/*-----------------------------------------------------------*/

/* 在每个分配的内存的开始处放置的结构的大小块必须通过正确的字节对齐 */
static const size_t pMemoryStructSize	= ( sizeof( BlockLink_t ) + ( ( size_t ) ( BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) BYTE_ALIGNMENT_MASK );

/* 内存使用标志 BLOCK 的最高位 | pBlockAllocatedBit 表示已使用 */
static size_t pBlockAllocatedBit = 0;

/*-----------------------------------------------------------*/

void *pMemoryMalloc( MemoryStruct * mem , size_t xWantedSize )
{
	BlockLink_t *pxBlock, *pxPreviousBlock, *pxNewBlockLink;
	void *pvReturn = NULL;

	uint32_t primask = enter_critical();
	
	/* 申请内存大小不能大于 pBlockAllocatedBit */
	/* 不然可能会覆盖 已使用标志置位 */
	if( ( xWantedSize & pBlockAllocatedBit ) == 0 )
	{
		if( xWantedSize > 0 )
		{
			/* xWantedSize 实际大小 需要加 pMemoryStructSize */
			xWantedSize += pMemoryStructSize;

			/* 判断 xWantedSize 是否 字节对齐 */
			if( ( xWantedSize & BYTE_ALIGNMENT_MASK ) != 0x00 )
			{
				/* 字节对齐处理 */
				xWantedSize += ( BYTE_ALIGNMENT - ( xWantedSize & BYTE_ALIGNMENT_MASK ) );
			}
		}

		/* 申请大小大于零 并且 小于当前剩余量 */
		if( ( xWantedSize > 0 ) && ( xWantedSize <= mem->Free ) )
		{
			/* 寻找足够大小的内存块 */
			pxPreviousBlock = &mem->pStart;			 	
			pxBlock = mem->pStart.pxNextFreeBlock;
			while( ( pxBlock->xBlockSize < xWantedSize ) && ( pxBlock->pxNextFreeBlock != NULL ) )
			{
				pxPreviousBlock = pxBlock;					//保存当前 BLOCK
				pxBlock = pxBlock->pxNextFreeBlock;			//指向下一个 BLOCK
			}

			/* 是否有满足条件的内存块 */
			if( pxBlock != mem->pEnd )		// 如果 pxBlock == pEnd[mem]  则找到了最后没找到   
			{
				/* 内存地址为  pxNextFreeBlock + pMemoryStructSize 为起始 */
				pvReturn = ( void * ) ( ( ( uint8_t * ) pxPreviousBlock->pxNextFreeBlock ) + pMemoryStructSize );

				/* 改变当前 BLOCK 的 pxNextFreeBlock 的指向地址 指向下一个 BLOCK 的地址 */
				pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

				/* 如果 pxBlock 剩余内存 大于 最小的 BLOCK 大小 */
				if( ( pxBlock->xBlockSize - xWantedSize ) > MemoryMINIMUM_BLOCK_SIZE )
				{
					/* 创建新的 BLOCKLink 地址为 pxBlock + xWantedSize */
					pxNewBlockLink = ( void * ) ( ( ( uint8_t * ) pxBlock ) + xWantedSize );

					/* 创建新的 BLOCKLink 内存大小为 xBlockSize - 申请值 */
					pxNewBlockLink->xBlockSize = pxBlock->xBlockSize - xWantedSize;
					
					/* 当前 BLOCK 的大小 */
					pxBlock->xBlockSize = xWantedSize;

					/* 插入新的LIST 到剩余 内存中 */
					pInsertBlockIntoFreeList( mem , pxNewBlockLink );
				}

				/* 记录当前内存剩余 */
				mem->Free -= pxBlock->xBlockSize;

				if( mem->Free < mem->MinFree )
				{
					/* 记录历史内存最小剩余 */
					mem->MinFree = mem->Free;
				}

				/* 当前BLock 已使用标志置位 */
				pxBlock->xBlockSize |= pBlockAllocatedBit;
				pxBlock->pxNextFreeBlock = NULL;
			}
		}
	}
	
	( void ) exit_critical(primask);

	return pvReturn;
}

/*-----------------------------------------------------------*/

void *pMemoryReMalloc( MemoryStruct * mem1 , MemoryStruct * mem2 , void *ptr , size_t size )
{
	size_t *offset = NULL;
	
	offset = pMemoryMalloc( mem1 , size );   	
	
    if(offset == NULL)
	{
		return NULL; 
	}
	else
	{
		memcpy( offset , ptr , size );
		
		pMemoryFree( mem2 , ptr );
	}
	
	return offset;
}
/*-----------------------------------------------------------*/

void pMemoryFree( MemoryStruct * mem , void *pv )
{
	uint8_t *puc = ( uint8_t * ) pv;
	BlockLink_t *pxLink;

	if( pv == NULL )
		return;
	
	/* 内存BLOCK list 地址为内存地址 - pMemoryStructSize 在申请的时候会 + pMemoryStructSize */
	puc -= pMemoryStructSize;

	/* 使用  puc 避免编译器报警告 */
	pxLink = ( void * ) puc;

	/* 使用  xBlockSize 是否使用 */
	if( ( pxLink->xBlockSize & pBlockAllocatedBit ) != 0 )
	{
		if( pxLink->pxNextFreeBlock == NULL )
		{
			/* 去掉使用标志 */
			pxLink->xBlockSize &= ~pBlockAllocatedBit;

			uint32_t primask = enter_critical();
			
			/* 把这个BLOCK 添加到剩余内存中 */
			mem->Free += pxLink->xBlockSize;
			pInsertBlockIntoFreeList( mem , ( ( BlockLink_t * ) pxLink ) );

			( void ) exit_critical(primask);
		}
	}
}
/*-----------------------------------------------------------*/

size_t pMemoryGetFreeMemorySize( MemoryStruct * mem )
{
	return mem->Free;
}
/*-----------------------------------------------------------*/

size_t pMemoryGetMinimumEverFreeMemorySize( MemoryStruct * mem )
{
	return mem->MinFree;
}
/*-----------------------------------------------------------*/

void pMemoryInit( MemoryStruct *mem)
{
	BlockLink_t *pxFirstFreeBlock;
	uint8_t *pucAlignedHeap;
	size_t uxAddress;
	size_t xTotalHeapSize = mem->size;

	/* 内存地址赋值 */
	uxAddress = ( size_t ) mem->pMemory;

	/* 判断是否内存对齐 */
	if( ( uxAddress & BYTE_ALIGNMENT_MASK ) != 0 )
	{
		uxAddress += ( BYTE_ALIGNMENT - 1 );
		uxAddress &= ~( ( size_t ) BYTE_ALIGNMENT_MASK );
		xTotalHeapSize -= uxAddress - ( size_t ) mem->pMemory;
	}

	pucAlignedHeap = ( uint8_t * ) uxAddress;

	/* 第一个 BLOCK 初始化 */
	mem->pStart.pxNextFreeBlock = ( void * ) pucAlignedHeap;
	mem->pStart.xBlockSize = ( size_t ) 0;

	/* 内存结尾赋值 */
	uxAddress = ( ( size_t ) pucAlignedHeap ) + xTotalHeapSize;
	uxAddress -= pMemoryStructSize;
	uxAddress &= ~( ( size_t ) BYTE_ALIGNMENT_MASK );
	mem->pEnd = ( void * ) uxAddress;
	mem->pEnd->xBlockSize = 0;
	mem->pEnd->pxNextFreeBlock = NULL;

	/* 首先，有一个单独的自由块，它的大小可以用来处理整个堆空间，减去pxEnd所占用的空间 */
	pxFirstFreeBlock = ( void * ) pucAlignedHeap;
	pxFirstFreeBlock->xBlockSize = uxAddress - ( size_t ) pxFirstFreeBlock;
	pxFirstFreeBlock->pxNextFreeBlock = mem->pEnd;

	/* 内存使用剩余量 */
	mem->Free = pxFirstFreeBlock->xBlockSize;
	mem->MinFree = pxFirstFreeBlock->xBlockSize;

	/* 最高位标志 当最高位置位时表示已使用 */
	pBlockAllocatedBit = ( ( size_t ) 1 ) << ( ( sizeof( size_t ) * MemoryBITS_PER_BYTE ) - 1 );
}
/*-----------------------------------------------------------*/

static void pInsertBlockIntoFreeList( MemoryStruct * mem , BlockLink_t *pxBlockToInsert )
{
	BlockLink_t *pxIterator;
	uint8_t *puc;

	/* 寻找插入内存地址 找到当前 插入的 BLOCK 位置 pxIterator 下一个内存地址 >= pxBlockToInsert */
	for( pxIterator = &mem->pStart; pxIterator->pxNextFreeBlock < pxBlockToInsert; pxIterator = pxIterator->pxNextFreeBlock )
	{
	}

	/* 判断前一个 BLOCK（pxIterator）  是否 指向的是当前 BLOCK（pxBlockToInsert） 内存块*/
	puc = ( uint8_t * ) pxIterator;
	if( ( puc + pxIterator->xBlockSize ) == ( uint8_t * ) pxBlockToInsert )
	{
		pxIterator->xBlockSize += pxBlockToInsert->xBlockSize;	//合并两个 BLOCK
		pxBlockToInsert = pxIterator;
	}

	/* 插入的块，以及它之前插入的块创建一个连续的内存块？*/
	puc = ( uint8_t * ) pxBlockToInsert;
	if( ( puc + pxBlockToInsert->xBlockSize ) == ( uint8_t * ) pxIterator->pxNextFreeBlock )
	{
		if( pxIterator->pxNextFreeBlock != mem->pEnd )
		{
			/* 合并两个内存块 */
			pxBlockToInsert->xBlockSize += pxIterator->pxNextFreeBlock->xBlockSize;
			pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock->pxNextFreeBlock;
		}
		else
		{
			pxBlockToInsert->pxNextFreeBlock = mem->pEnd;
		}
	}
	else
	{
		pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
	}

	/* 如果插入的块插入一个gab，那么就与block合并在此之前和之后，它的pxNextFreeBlock指针将会有已经设置好了，
	不应该在这里设置因为这将使它指向本身。 */
	if( pxIterator != pxBlockToInsert )
	{
		pxIterator->pxNextFreeBlock = pxBlockToInsert;
	}
}
/*-----------------------------------------------------------*/

/*	从内存中查找是否有某个自由块 */
static uint8_t pMemoryFindBlock( MemoryStruct* mem, void *pv)
{
	if( ( pv >= ( void* )( mem->pMemory ) ) && ( pv < (void*)( mem->pMemory + mem->size ) ))
		return 1;
	return 0;
}
/*-----------------------------------------------------------*/

/*  设置内存分配是否支持DMA */
void memory_pool_set_dma_capable( uint8_t is_capable )
{
	if( is_capable != 0 )
	{
		mm_is_dma_capable = 1;
	} else {
		mm_is_dma_capable = 0;
	}
}
/*-----------------------------------------------------------*/

/*  内存池初始化 */
void memory_pool_init( uint8_t is_dma_capable )
{
	uint8_t i = 0;
	if( is_dma_capable != 0 )
	{
		mm_is_dma_capable = 1;
	} else {
		mm_is_dma_capable = 0;
	}

	for( i = 0 ; i < sizeof(mm_no_dma_capable_list) / sizeof(mm_no_dma_capable_list[0]) ; ++i)
	{
		pMemoryInit( mm_no_dma_capable_list[i] );
	}

	for( i = 0 ; i < sizeof(mm_dma_capable_list) / sizeof(mm_dma_capable_list[0]) ; ++i)
	{
		pMemoryInit( mm_dma_capable_list[i] );
	}
}
/*-----------------------------------------------------------*/

/*  malloc接口 */
void * memory_pool_malloc( size_t xWantedSize )
{
	uint8_t i = 0;
	void * pv = NULL;

	if( mm_is_dma_capable == 0 )
	{
		for( i = 0 ; i < sizeof(mm_no_dma_capable_list) / sizeof(mm_no_dma_capable_list[0]) ; ++i)
		{
			pv = pMemoryMalloc( mm_no_dma_capable_list[i] , xWantedSize );
			if( pv != NULL )
				return pv;
		}
	}

	for( i = 0 ; i < sizeof(mm_dma_capable_list) / sizeof(mm_dma_capable_list[0]) ; ++i)
	{
		pv = pMemoryMalloc( mm_dma_capable_list[i] , xWantedSize );
		if( pv != NULL )
			break;
	}

	return pv;
}
/*-----------------------------------------------------------*/

/*  free接口 */
void memory_pool_free( void *pv )
{
	uint8_t i = 0;

	if( mm_is_dma_capable == 0 )
	{
		for( i = 0 ; i < sizeof(mm_no_dma_capable_list) / sizeof(mm_no_dma_capable_list[0]) ; ++i)
		{
			if( pMemoryFindBlock( mm_no_dma_capable_list[i], pv) )
			{
				pMemoryFree(mm_no_dma_capable_list[i],pv);
				return;
			}
		}
	}

	for( i = 0 ; i < sizeof(mm_dma_capable_list) / sizeof(mm_dma_capable_list[0]) ; ++i)
	{
		if( pMemoryFindBlock( mm_dma_capable_list[i], pv) )
		{
			pMemoryFree(mm_dma_capable_list[i],pv);
			return;
		}
	}

	/* 错误 free 警告 */
	/* ... */
}
/*-----------------------------------------------------------*/

