#pragma once

#include <cstddef>
// 基础版本
void* operator new(std::size_t size);

// 数组版本
void* operator new[](std::size_t size);