/*!
 * @file obloq.ino
 * @brief 将子串口1和2都连接1个obloq
 * @n 在运行此demo之前，请到下载obloq的依赖库https://github.com/DFRobot/Obloq
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Arya](xue.peng@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-28
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_IIC_Serial
 */
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Obloq.h"
#include <DFRobot_IIC_Serial.h>

SoftwareSerial softSerial(2,3);
DFRobot_IIC_Serial iicSerial1(Wire, /*subUartChannel =*/SUBUART_CHANNEL_1, /*addr = */0x0E);//构造子串口1
DFRobot_IIC_Serial iicSerial2(Wire, /*subUartChannel =*/SUBUART_CHANNEL_2, /*addr = */0x0E);//构造子串口1
//生成OBLOQ对象，参数：串口指针，wifiSsid,WifiPwd,iotId,iotPwd
//Obloq olq1(&softSerial,"dfrobotYanfa","hidfrobot");

Obloq olq(&iicSerial1,"dfrobotYanfa","hidfrobot");
Obloq olq2(&iicSerial2,"dfrobotYanfa","hidfrobot");
static unsigned long currentTime = 0; 

void httpMsgHandle(const String& code,const String& message)
{
    Serial.println("Code: " + code);
    Serial.println("Message: " + message);
}

void setup()
{
    //softSerial.begin(9600);
    iicSerial1.begin(9600);
    iicSerial2.begin(9600);
    Serial.begin(9600);
    olq.setHttpMsgHandle(httpMsgHandle);
   // olq1.setHttpMsgHandle(httpMsgHandle);
   olq2.setHttpMsgHandle(httpMsgHandle);
}
void loop()
{
    olq.update();
   // olq1.update();
    olq2.update();
    if(millis() - currentTime > 2000)
    {
        currentTime =  millis();
        olq.get("http://download3.dfrobot.com.cn/files/");
        olq2.get("http://download3.dfrobot.com.cn/files/");
       // olq1.get("http://download3.dfrobot.com.cn/files/");
    }
}
