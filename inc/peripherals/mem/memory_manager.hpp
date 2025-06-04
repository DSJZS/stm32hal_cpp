#pragma once

#include "../../../inc/peripherals/mem/mem_manager.h"

#define __ENABLE_MEM_MANGER__

#ifdef __ENABLE_MEM_MANGER__

#ifndef MEM_MANAGER_DMP_CAPABLE
    #define MEM_MANAGER_DMP_CAPABLE     (0)
#endif

#endif
