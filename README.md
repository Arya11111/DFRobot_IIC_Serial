# DFRobot_IIC_Serial
这是一款IIC转双串口的UART模块，IIC最高速率为1Mbps。每个子串口具备收/发独立的256字节FIFO硬件缓存，可以满足用户大量数据传输的场景。<br>
每个子串口的波特率，字长，校验格式可以独特设置，最高可以提供2Mbps的通信速率，支持4个IIC地址，一块主控上最多并联4个模块，一次最多 <br>
扩展8个硬串口。此外子串口还可被配置为IrDA红外收发模式，再次模式下，直接接红外接收或红外发射头即可实现红外通信。<br>

这里需要显示拍照图片，可以一张图片，可以多张图片（不要用SVG图）

![正反面svg效果图](https://github.com/Arya11111/DFRobot_MCP23017/blob/master/resources/images/SEN0245svg1.png)


## 产品链接（链接到英文商城）
    DFR0627 Gravity：IIC to dual UART module
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

1. 子串口模式配置：串口模式或IrDA（红外通信）模式；<br>
2. 波特率设置；<br>
3. 串口数据读；<br>
4. 串口数据写；<br>

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
/**
  * @brief 构造函数
  * @param pWire I2C总线指针对象，构造设备，可传参数也可不传参数，默认Wire
  * @param subUartChannel 子串口通道号，WK2132有2个子串口，可填SUBUART_CHANNEL_1或SUBUART_CHANNEL_2
  * @param addr 8位I2C地址的前5位右移3位，取值(0x02/0x06/0x0A/0x0E)默认0x27
  * @n IIC地址由构成如下图所示
  * 7  6  5  4  3  2  1   0
  * 0  A1 A0 1  0  C1 C0 0/1
  * @n 第7/4/3位为固定值，分别为0/1/0
  * @n 第6/5位的值由拨码开关来确定，范围为（00~11），默认为11
  * @n 第2/1位的值为子串口通道，00表示子串口1，01表示子串口2
  * @n 第0位表示是读写寄存器还是读写FIFO缓存，0表示读寄存器，1表示读FIFO缓存
  * @n 综上所述，此串口扩展模块的IIC地址构成为0 A1 A0 1 0 C1 C0 0/1
  * @n 构造函数中的addr指的是第7~3位右移3位，如下表所示：默认为0x0E
     0  0  0  0  | A1 A0 1  0
     0  0  0  0  | 1  1  1  0    0x0E
     0  0  0  0  | 1  0  1  0    0x0A
     0  0  0  0  | 0  1  1  0    0x06
     0  0  0  0  | 0  0  1  0    0x02
  * @n 模块实际IIC地址与子串口通道编号和是操作寄存器还是FIFO有关
  * @n IIC实际地址:_addr = (addr << 3) | SUBUART_CHANNEL_N | OBJECT_REGISTER/OBJECT_FIFO
  */
DFRobot_IIC_Serial(TwoWire &wire = Wire, uint8_t subUartChannel = SUBUART_CHANNEL_1, uint8_t addr = 0x0E);

/**
 * @brief 初始化函数，设置子串口的波特率
 * @param baud 串口波特率
 */
void begin(long unsigned baud){begin(baud, IIC_SERIAL_8N1, eNormalMode, eNormal);};
/**
 * @brief 初始化函数，设置子串口的波特率，数据格式
 * @param baud 串口波特率
 * @param format 子串口数据格式，可填IIC_SERIAL_8N1、IIC_SERIAL_8N2、IIC_SERIAL_8Z1
 * @n IIC_SERIAL_8Z2、IIC_SERIAL_8O1、IIC_SERIAL_8O2、IIC_SERIAL_8E1、IIC_SERIAL_8E2
 * @n IIC_SERIAL_8F1、IIC_SERIAL_8F2等参数
 */
void begin(long unsigned baud, uint8_t format){begin(baud, format, eNormalMode, eNormal);};
 /**
 * @brief 初始化函数，设置子串口的波特率，数据格式，通信模式
 * @param baud 串口波特率
 * @param format 子串口数据格式，可填IIC_SERIAL_8N1、IIC_SERIAL_8N2、IIC_SERIAL_8Z1
 * @n IIC_SERIAL_8Z2、IIC_SERIAL_8O1、IIC_SERIAL_8O2、IIC_SERIAL_8E1、IIC_SERIAL_8E2
 * @n IIC_SERIAL_8F1、IIC_SERIAL_8F2等参数
 * @param mode 自串口通信模式，可设置为红外模式（1）或普通模式（0），可填eCommunicationMode_t的所有枚举值，或0或1
 */
void begin(long unsigned baud, uint8_t format, eCommunicationMode_t mode){begin(baud, format, mode, eNormal);};
void begin(long unsigned baud, uint8_t format, uint8_t mode){begin(baud, format, mode, eNormal);};
/**
 * @brief 初始化函数，设置子串口的波特率，数据格式，通信模式，和Line-Break输出
 * @param baud 串口波特率
 * @param format 子串口数据格式，可填IIC_SERIAL_8N1、IIC_SERIAL_8N2、IIC_SERIAL_8Z1
 * @n IIC_SERIAL_8Z2、IIC_SERIAL_8O1、IIC_SERIAL_8O2、IIC_SERIAL_8E1、IIC_SERIAL_8E2
 * @n IIC_SERIAL_8F1、IIC_SERIAL_8F2等参数
 * @param mode 自串口通信模式，可设置为红外模式（1）或普通模式（0），可填eCommunicationMode_t的所有枚举值，或0或1
 * @param opt 子串口Line-Break输出控制位，可设置为正常输出（0）和Line-Break输出（1），可填eLineBreakOutput_t的所有枚举值，或0或1
 */
void begin(long unsigned baud, uint8_t format, eCommunicationMode_t mode, eLineBreakOutput_t opt);
void begin(long unsigned baud, uint8_t format, uint8_t mode, uint8_t opt);

/**
 * @brief 结束通信，并复位串口
 */
void end();
/**
 * @brief 读取接收FIFO缓存中数据的字节数
 * @return 返回接收FIFO缓存中字节的个数
 */
virtual int available(void);
/**
 * @brief 从接收FIFO缓存中读取一个字节，该读取不会清除缓存中的数据
 * @return 返回读取的数据
 */
virtual int peek(void);
/**
 * @brief 从接收FIFO缓存中读取一个字节，该读取会清除缓存中的数据
 * @return 返回读取的数据
 */
virtual int read(void);
 /**
 * @brief 读FIFO缓存
 * @param pBuf 要读取数据的存放缓存
 * @param size 要读取数据的长度
 * @return 返回实际读取的长度，返回0表示读取失败
 */
size_t read(void *pBuf, size_t size);
/**
 * @brief 清空接收FIFO缓存的数据
 */
virtual void flush(void){}
/**
 * @brief 向发送FIFO缓存中写入一个字节,以下为不同数据类型字节的重载函数
 * @return 成功返回0，否者返回-1
 */
virtual size_t write(uint8_t);
inline size_t write(unsigned long n) { return write((uint8_t)n); }
inline size_t write(long n) { return write((uint8_t)n); }
inline size_t write(unsigned int n) { return write((uint8_t)n); }
inline size_t write(int n) { return write((uint8_t)n); }
/**
 * @brief 向发送FIFO缓存中写入数据
 * @param pBuf 要读取数据的存放缓存
 * @param size 要读取数据的长度
 * @return 成功返回0，否者返回-1
 */
size_t write(void *pBuf, size_t size);


```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32         |      √       |              |             | 
micro:bit        |      √       |              |             | 

## History

- data 2019-7-18
- version V1.0

## Credits

Written by(xue.peng@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





