/*!
 * @file readSerial.ino
 * @brief 从子串口读取数据(以子串口2为例)
 * @n 检测子串口1中是否有数据被接收，若有数据则读并打印
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Arya](xue.peng@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-28
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_IIC_Serial
 */
#include <DFRobot_IIC_Serial.h>
/*DFRobot_IIC_Serial构造函数
 *参数&wire 可填TwoWire对象Wire
 *参数subUartChannel 子串口通道号，可填SUBUART_CHANNEL_1（子串口1（默认））或SUBUART_CHANNEL_2（子串口2）
 *参数addr  如下I2C地址可用0x0E/0x0A/0x06/0x02，拨码开关A1、A0与I2C地址对应关系如下所示（默认0x0E）：
 *  0  0  0  0  | A1 A0 1  0
    0  0  0  0  | 1  1  1  0    0x0E
    0  0  0  0  | 1  0  1  0    0x0A
    0  0  0  0  | 0  1  1  0    0x06
    0  0  0  0  | 0  0  1  0    0x02
  注：该addr只是IIC地址的前4位
 */
DFRobot_IIC_Serial iicSerial1(Wire, /*subUartChannel =*/SUBUART_CHANNEL_1, /*addr = */0x0E);//构造子串口1
//DFRobot_IIC_Serial iicSerial1;//这样定义会使用默认参数， Wire SUBUART_CHANNEL_1 0x0E(默认I2C地址)

void setup() {
  Serial.begin(115200);
  /*begin 初始化函数,设置波特率,该波特率需要根据选择的晶振频率设置
  begin(long unsigned baud)调用该函数，可设置子串口波特率，默认配置->波特率：baud，数据格式：IIC_SERIAL_8N1，8位数据，无校验模式，1位停止位
  begin(long unsigned baud, uint8_t format)调用该函数可设置波特率和数据格式,
  参数baud支持：115200，
  参数format可填：
  IIC_SERIAL_8N1  IIC_SERIAL_8N2  IIC_SERIAL_8Z1  IIC_SERIAL_8Z2  IIC_SERIAL_8O1
  IIC_SERIAL_8O2  IIC_SERIAL_8E1  IIC_SERIAL_8E2  IIC_SERIAL_8F1  IIC_SERIAL_8F2
  8代表数据位数，N代表无校验，Z代表0校验，O表示奇校验，E表示偶校验， F代表1校验，1或2代表停止位个数，
  默认为IIC_SERIAL_8N1 8为数据，1为停止位，无校验数据格式
  */
  iicSerial1.begin(/*baud = */115200);/*子串口1初始化*/
  //iicSerial1.begin(/*baud = */115200, /*format = */IIC_SERIAL_8N1);
}

void loop() {
  char c;
  if(iicSerial1.available()){/*available返回子串口1接收缓存的字节数，无-返回0*/
    while(iicSerial1.available()){
      c = iicSerial1.read();/*读取子串口1接收缓存的数据*/
      Serial.print(c);
    }
    Serial.println();
  }
  delay(1000);
}
