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

/*  内存池初始化 */
void memory_pool_init( void );
/*  内存池默认指向空间设置 */
void memory_pool_setDefault( MemoryStruct* def_mem );
/*  malloc接口 */
extern void * memory_pool_malloc( size_t xWantedSize );
/*  free接口 */
void memory_pool_free( void *pv );

#ifdef __cplusplus
}
#endif
#endif

