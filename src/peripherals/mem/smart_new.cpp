#include "../../../inc/peripherals/mem/smart_new.hpp"
#include "../../../inc/peripherals/mem/mem_manager.h"

// 基础版本
void* operator new(std::size_t size)
{
    return memory_pool_malloc( size );
}

// 数组版本
void* operator new[](std::size_t size)
{
    return memory_pool_malloc( size );
}