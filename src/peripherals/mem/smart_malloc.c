#include "../../../inc/peripherals/mem/smart_malloc.h"
#include "../../../inc/peripherals/mem/mem_manager.h"

void* malloc(size_t size)
{
    return memory_pool_malloc( size );
}