#include "../../../inc/peripherals/mem/smart_free.h"
#include "../../../inc/peripherals/mem/mem_manager.h"

void free(void* ptr)
{
    memory_pool_free( ptr );
}