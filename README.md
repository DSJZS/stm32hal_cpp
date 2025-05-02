# STM32 HAL C++ 功能库 

**⚠️ 注意**：本库为私有库，未经许可不得外传或用于其他用途。

---

## 作者
- 2023级校友程雨安

---

## 使用方法
- 参考文件：`stm32_hal_cpp_user_utility_class.hpp` 中的详细说明

---


## 文件内容描述

### 核心功能模块
- **debug_function**  
  调试工具集：
  - 函数耗时计数器

- **useful_function**  
  通用实用功能：
  - 数据打包/解包接口
  - PID

### 硬件抽象层封装
- **stm32_hal_cpp_base_bsp**  
  STM32 HAL 基础外设 C++ 封装：
  - GPIO 
  - TIM 
  - UART 
  - I2C 

- **stm32_hal_cpp_ex_bsp**  
  STM32 HAL 扩展外设 C++ 封装：
  - 直流电机电机驱动
  - HC-05蓝牙模块

---

> **声明**：本库所有权归大连民族大学创三工作室所有，禁止未授权分发。