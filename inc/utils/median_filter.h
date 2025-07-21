#ifndef __MEDIAN_FILTER_H__
#define __MEDIAN_FILTER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

//  窗口长度最大支持 9, 窗口长度最好为单数
float median_filter( float* buffer, uint8_t window_size, uint8_t* index, float new_data);

#ifdef __cplusplus
}
#endif

#endif
