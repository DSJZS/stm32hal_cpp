#include "../../../inc/peripherals/mem/mem_manager.h"
#include "../../../inc/peripherals/mem/memory_manager.hpp"

namespace cya::stm32::peripheral{

static class Mem_Manager{
public:
    Mem_Manager();
    ~Mem_Manager();
}mm;    //  定义全局类对象, 其构造函数在main函数调用前自动执行(__libc_init_array)，无需外部执行初始化操作

Mem_Manager::Mem_Manager()
{
    //  用于执行静态内存池初始化, 默认不支持 DMA
#if defined(MEM_MANAGER_DMP_CAPABLE) && MEM_MANAGER_DMP_CAPABLE == 0
    memory_pool_init(0);
#endif

#if defined(MEM_MANAGER_DMP_CAPABLE) && MEM_MANAGER_DMP_CAPABLE != 0
    memory_pool_init(1);
#endif

}

Mem_Manager::~Mem_Manager()
{

}

}