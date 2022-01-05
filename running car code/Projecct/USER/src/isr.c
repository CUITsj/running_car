/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		中断文件
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"

uint8 i;          //计数变量
uint8 Send_Count; //串口需要发送的数据个数

//停车线
uint8 check_time = 0, check_delay = 0;
uint8 nodelay = 0;

void PIT_CH0_IRQHandler(void)
{
    static uint16 count = 0;
  
    if (check_delay == 1)
    {
      count++;
      if (count == 400)         //延时1秒
      {
        count = 0;
        check_delay = 0;
        check_time++;
        if (check_time == lap)
        {
          nodelay = 1;
        }
      }
    }
  
    ad_result[0] = adc_once(AD_CHANNEL1,ADC_12bit);//vin1右
    ad_result[1] = adc_once(AD_CHANNEL2,ADC_12bit);//vin2左
    if (find_max == 1)
    {
      if (ad_result[0] > ad_max0)
      {
        ad_max0 = ad_result[0];
      }
      if (ad_result[1] > ad_max1)
      {
        ad_max1 = ad_result[1];
      }
    }
  
    result[0] = ad_result[0]*800/ad_max0;
    result[1] = ad_result[1]*800/ad_max1;
    
    servo_contral();  
    
    PIT_FLAG_CLR(pit0);
    
}
void PIT_CH1_IRQHandler(void)
{
    ad_result[0] = adc_once(AD_CHANNEL1,ADC_12bit);//vin1
    ad_result[1] = adc_once(AD_CHANNEL2,ADC_12bit);//vin2  
    ad_result[2] = adc_once(AD_CHANNEL3,ADC_12bit);//电流
    ad_result[3] = adc_once(AD_CHANNEL4,ADC_12bit);//电压
    
    DataScope_Get_Channel_Data( ad_result[0], 1 );  //vin1    
    DataScope_Get_Channel_Data( ad_result[1] , 2 );  //vin2
    DataScope_Get_Channel_Data( ad_result[2]/163.8 , 3 );  //电流
    DataScope_Get_Channel_Data( ad_result[3]/261.9 , 4 );  //电压
    
    Send_Count = DataScope_Data_Generate(4); //生成10个通道的 格式化帧数据，返回帧数据长度

    for( i = 0 ; i < Send_Count; i++)  //循环发送,直到发送完毕   
    {
      uart_putchar(uart0, DataScope_OutPut_Buffer[i]);
    }
  
    PIT_FLAG_CLR(pit1);  
}

void IRQ_IRQHandler(void)
{
  static uint8 count = 0;
  
  count++;
  
  if (lap != 3 && count >= 2)
  {
    //uart_putchar(uart0, count);
    count = 0;
    if (nodelay == 1)
    {
      ftm_pwm_duty(ftm2,ftm_ch0,1000); 
    }
    else
    {
      check_delay = 1;
    }
  }
  
  CLEAR_IRQ_FLAG;
    
}

void KBI0_IRQHandler(void)
{
    CLEAN_KBI1_FLAG;        //然后清除标志位
}





/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了周期定时器 通道0得中断
void PIT_CH0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位

FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler    
PIT_CH1_IRQHandler    
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/



