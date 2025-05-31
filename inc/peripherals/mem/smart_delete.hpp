#pragma once

// 基础版本
void operator delete(void* ptr) noexcept;

// 数组版本
void operator delete[](void* ptr) noexcept;