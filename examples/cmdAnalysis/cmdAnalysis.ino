/*!
 * @file cmdAnalysis.ino
 * @brief 解析串口命令，存放（以子串口2为例，将子串口2的RX与TX引脚连接到一起）
 * @n 通过串口随机发送一个字符串："ABCDEFASFGHJUAAAEEB"
 * @n 接收该字符串，去掉字符串中的字符'A'，并将消除字符'A'后的字符串打印出来
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
DFRobot_IIC_Serial iicSerial2(Wire, /*subUartChannel =*/SUBUART_CHANNEL_2, /*addr = */0x0E);//构造子串口2

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
  iicSerial2.begin(/*baud = */115200);/*子串口2初始化*/
  //iicSerial2.begin(/*baud = */115200, /*format = */IIC_SERIAL_8N1);
  Serial.print("Original string: ");//打印原始字符串
  Serial.println("ABCDEFASFGHJUAAAEEB");
  Serial.print("Eliminate char: ");//打印需要清除的字符
  Serial.println('A');
  iicSerial2.println("ABCDEFASFGHJUAAAEEB");//子串口2发送字符串"ABCDEFASFGHJUAAAEEB"
}

void loop() {
  int n = iicSerial2.available();//读取子串口2中的字节数
  char c[256];
  int i = 0;
  if(n){
      while(iicSerial2.available()){
          if((char)iicSerial2.peek() != 'A'){//使用peek函数读取字符，不会清除缓存中的数据
              c[i++] = iicSerial2.read();//使用read函数读取字符，会清除缓存中的数据
              if((i > (sizeof(c) - 1)))
                  break;
          }else{
              iicSerial2.read();//read函数放在这里，用于清除缓存里的一个字节数据，这里是清除字符'A'
          }
      }
      Serial.print("Analysis string: ");
      for(int j = 0; j < i; j++){
          Serial.print(c[j]);
      }
      Serial.println();
  }
  delay(1000);
}
