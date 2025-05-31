#pragma once

#include "peripherals/peripherals.hpp"
#include "interfaces/interfaces.hpp"
#include "modules/modules.hpp"
#include "protocols/protocols.hpp"
#include "services/services.hpp"
#include "utils/utils.hpp"

/* legacy */
/* 理应尽快替换的代码 */
#include "legacy/data_packet_process_interface.hpp"

/* 文件的依赖关系
 * 目录					可依赖的目录									禁止依赖的目录
 * interfaces			无（仅定义接口，不依赖其他目录）						所有目录
 * legacy				utils（允许使用基础工具）							尽量避免被其他目录依赖（尤其是新代码）
 * modules				interfaces, peripherals, protocols, utils	services, legacy
 * peripherals			interfaces（实现接口）, utils					modules, protocols, services
 * protocols			interfaces, peripherals（若依赖硬件）, utils		modules, services
 * services				modules, protocols, utils					peripherals, legacy
 * utils				无（完全独立）									所有目录
 */

/* 一些后缀与命名空间的解释
 * 接口应该用 Interface 后缀，并且放在 interfaces/，命名空间应该为 interface::
 * 通用基类应该用 Base 后缀( 考虑换成 Abstract 后缀 )，并且与实现放在统一文件下，命名空间应该与实现相同
 */

/* 目标与日志
 * 1.完成ADC
 * 2.完成OLED封装
 * 3.测试通讯协议
 */
