#ifndef __DATA__PACKET_PROCESS_INTERFACE_HPP__
#define __DATA__PACKET_PROCESS_INTERFACE_HPP__

#include "main.h"

namespace cya::legacy{

/* 打包与解包的接口
 * pack_data    用于给数据进行打包操作，需要提供以下参数：
 *      packet      : 打包后的包数据存放地址
 *      data        : 待打包数据的存放地址
 *      data_size   : 要打包的数据一共占多少字节
 *      packet_id   : 数据包ID，用于区分不同用途的数据包, 默认为 0xAA
 *      hParam / lParam
 *                  : 高低位参数，可以位指针等数据，用户自定义，用于加强接口灵活性
 *
 * unpack_data  用于给数据包进行解包操作，需要提供以下参数：
 *      packet      : 待解包数据存放地址
 *      data        : 解包后数据的存放地址
 *      data_size    : 要解包的数据一共占多少字节
 *      packet_id   : 数据包ID，用于区分不同用途的数据包, 默认为 0xAA
 *      hParam / lParam
 *                  : 高低位参数，可以位指针等数据，用户自定义，用于加强接口灵活性
 */
class Data_Packet_Process{
public:
    virtual bool pack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
            uint8_t packet_id = 0xAA,
            uint32_t hParam = 0,uint32_t lParam = 0) = 0;
    virtual uint16_t unpack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
            uint8_t packet_id = 0xAA,
            uint32_t hParam = 0,uint32_t lParam = 0) = 0;
};


/* 校验和
 * 数据包格式：HEAD + SIZE + DATA + VERIF
 * HEAD : 包头，单字节
 * SIZE : 包长度，单字节，记录整个数据包的长度，包最大长度为 256(注意提供的包存储空间要足够)
 * DATA : 包数据，不定字节，存放着数据包传输的实际数据
 * VERIF: 包校验，单字节，存放校验和数据
 */
class Data_Packet_Checksum : public Data_Packet_Process{
public:
    virtual bool pack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
            uint8_t packet_id = 0xAA,
            uint32_t hParam = 0,uint32_t lParam = 0) override;
    virtual uint16_t unpack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
            uint8_t packet_id = 0xAA,
            uint32_t hParam = 0,uint32_t lParam = 0) override;
};

/* firewater协议
 *
 * 注意：该协议并未实现，因为串口的printf相关函数可以轻易的替代它的作用
 *      由于其尴尬的地位，暂时不会实现其功能，如果你有时间可以尝试在现有基础上进行实现
 *      并提交请求到功能库
 *
 * 数据包格式：data_1,data_2,data_3, ... ,data_n\n
 * 可以一次性传输n个数据，每个数据用英文逗号隔开，最后以换行符号结束
 * 如果想要更加灵活的传输方式，建议使用串口的printf相关函数打包数据后直接发送
 * ( 便于向VOFA+传输数据，注意提供的包存储空间要足够 )
 */
class Data_Packet_Firewater : public Data_Packet_Process{
public:
    enum data_type { INT_8,UINT_8,INT_16,UINT_16,INT_32,UINT_32,FLOAT_32};
    virtual bool pack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
            uint8_t packet_id = 0xAA,
            uint32_t hParam = 0,uint32_t lParam = 0) override;
    virtual uint16_t unpack_data(uint8_t* packet, uint8_t* data, uint16_t data_size,
            uint8_t packet_id = 0xAA,
            uint32_t hParam = 0,uint32_t lParam = 0) override;
};

//  固定包头包尾数据包接收器
class Data_Packet_Receiver{
private:
    uint8_t head_;
    uint8_t rear_;
    uint8_t ptr_;
    uint8_t buffer_[256];    //  固定大小缓存，后续添加动态内存后修改

    void receive_byte(uint8_t byte);
public:
    Data_Packet_Receiver(uint8_t head,uint8_t rear);
    bool receive_data(uint8_t* data, uint16_t size);
    uint8_t* get_buffer(uint8_t* ptr_size = NULL);
    void clear_buffer(void);
};

}

#endif
