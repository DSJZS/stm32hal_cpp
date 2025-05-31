#include "../../../inc/peripherals/mem/smart_delete.hpp"
#include "../../../inc/peripherals/mem/mem_manager.h"

// 基础版本
void operator delete(void* ptr) noexcept
{
    memory_pool_free(ptr);
}

// 数组版本
void operator delete[](void* ptr) noexcept
{
    memory_pool_free(ptr);
}