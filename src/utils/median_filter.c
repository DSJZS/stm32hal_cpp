#include "../../inc/utils/median_filter.h"
#include <string.h>
#include <stdint.h>

void float_bubble_sort(float* arr, uint8_t len) 
{
    int i, j;
    float temp;
    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - 1 - i; j++)
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

float median_filter( float* buffer, uint8_t window_size, uint8_t* index, float new_data)
{
    float tmp_buffer[9] = {0};

    if( window_size == 0 )
        return 0;

    buffer[*index] = new_data;
    *index = ( *index + 1 ) % window_size;
    memcpy( tmp_buffer, buffer, window_size * sizeof(float) );

    // 排序（冒泡排序简单实现）
    float_bubble_sort( tmp_buffer, window_size);

    // 返回中值
    if (window_size % 2 == 1) {
        return tmp_buffer[window_size / 2];
    } else {
        // 偶数：返回中间两个值的平均数
        uint8_t mid = window_size / 2;
        return (tmp_buffer[mid - 1] + tmp_buffer[mid]) / 2.0f;
    }
}