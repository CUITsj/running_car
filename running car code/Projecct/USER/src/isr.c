/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�ж��ļ�
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.23
 * @Target core		S9KEA128AMLK
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-11-6
 ********************************************************************************************************************/



#include "isr.h"

uint8 i;          //��������
uint8 Send_Count; //������Ҫ���͵����ݸ���

//ͣ����
uint8 check_time = 0, check_delay = 0;
uint8 nodelay = 0;

void PIT_CH0_IRQHandler(void)
{
    static uint16 count = 0;
  
    if (check_delay == 1)
    {
      count++;
      if (count == 400)         //��ʱ1��
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
  
    ad_result[0] = adc_once(AD_CHANNEL1,ADC_12bit);//vin1��
    ad_result[1] = adc_once(AD_CHANNEL2,ADC_12bit);//vin2��
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
    ad_result[2] = adc_once(AD_CHANNEL3,ADC_12bit);//����
    ad_result[3] = adc_once(AD_CHANNEL4,ADC_12bit);//��ѹ
    
    DataScope_Get_Channel_Data( ad_result[0], 1 );  //vin1    
    DataScope_Get_Channel_Data( ad_result[1] , 2 );  //vin2
    DataScope_Get_Channel_Data( ad_result[2]/163.8 , 3 );  //����
    DataScope_Get_Channel_Data( ad_result[3]/261.9 , 4 );  //��ѹ
    
    Send_Count = DataScope_Data_Generate(4); //����10��ͨ���� ��ʽ��֡���ݣ�����֡���ݳ���

    for( i = 0 ; i < Send_Count; i++)  //ѭ������,ֱ���������   
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
    CLEAN_KBI1_FLAG;        //Ȼ�������־λ
}





/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ���������ڶ�ʱ�� ͨ��0���ж�
void PIT_CH0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ

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



