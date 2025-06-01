#ifndef _MEMORY_H
#define _MEMORY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* 定义链表结构。这是用来连接自由块的他们的记忆地址 */
typedef struct A_BLOCK_LINK
{
	struct A_BLOCK_LINK *pxNextFreeBlock;	/* 列表中的下一个自由块 */
	size_t xBlockSize;						/* 自由块的大小 */
} BlockLink_t;

typedef struct {
	uint8_t 		*pMemory;				/* 创建内存地址 */
	size_t			size;					/* 创建内存大小 */
	BlockLink_t		pStart;					/* 创建内存开始 链表标记 */
	BlockLink_t		*pEnd;					/* 创建内存结束 链表标记 */
	size_t			Free;					/* 内存当前最小剩余 */
	size_t			MinFree;				/* 内存历史最小剩余 */
}MemoryStruct;

//									DMA支持		深度睡眠保持
extern MemoryStruct SRAM_IN;	//	支持		丢失
extern MemoryStruct CCM_RAM;	//	不支持		丢失
/*
extern MemoryStruct SDRAM_EX;	//	支持		自刷新保持
*/

/**********************************************************************************************/
/*			下述函数用于灵活的开辟动态空间,适合用于开辟空间给ADC用于DMA传输等等	*/
/*			使用某一内存前务必使用 pMemoryInit() 将其初始化	*/
/*			建议C语言项目使用下述函数, C++项目尽可能的不使用 */

/*内存初始化*/
extern void pMemoryInit( MemoryStruct *mem );
/*内存申请*/
extern void *pMemoryMalloc( MemoryStruct * mem , size_t xWantedSize );
/*内存重申请*/
extern void *pMemoryReMalloc( MemoryStruct * mem1 , MemoryStruct * mem2 , void *ptr , size_t size );
/*内存释放*/
extern void pMemoryFree( MemoryStruct * mem , void *pv );
/*内存当前剩余*/
extern size_t pMemoryGetFreeMemorySize( MemoryStruct * mem );
/*内存历史最小剩余*/
extern size_t pMemoryGetMinimumEverFreeMemorySize( MemoryStruct * mem );

/**********************************************************************************************/


/**********************************************************************************************/
/*			下述函数为提供给原始malloc/free与new/delete的接口	*/
/*	如果想要使用指针指针等操作,务必执行 memory_pool_init(),并用这些接口覆写malloc/free与new/delete	*/
/*			建议C++项目使用下述函数, C语言项目禁止使用 */

/*  内存池初始化 */
/*  必须开头初始化，且只能初始化一次 */
/*  建议不开启DMA支持,需要使用DMA的场合用上面更为原始的操作来完成  */
extern void memory_pool_init( uint8_t is_dma_capable );
/*  malloc接口 */
extern void * memory_pool_malloc( size_t xWantedSize );
/*  free接口 */
extern void memory_pool_free( void *pv );

/**********************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif

