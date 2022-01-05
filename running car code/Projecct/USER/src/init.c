#include "init.h"

void init(void)
{
    get_clk();              //��ȡʱ��Ƶ�� ����ִ��
     
    FLASH_Init();
    OLED_Init();
    
    //��ʼ��ADͨ��
    adc_init(AD_CHANNEL1);
    adc_init(AD_CHANNEL2);
    adc_init(AD_CHANNEL3);
    adc_init(AD_CHANNEL4);
//    adc_init(AD_CHANNEL5);
//    adc_init(AD_CHANNEL6);
//    adc_init(AD_CHANNEL7);
//    adc_init(AD_CHANNEL8);
    
    ftm_pwm_init(servo_ftm,servo_ch,servo_hz,servo_mid);
    ftm_pwm_init(charge_ftm,charge_ch,charge_hz,0);
    ftm_pwm_init(motor_ftm,motor_ch,motor_hz,1000);
    
    key_init();
    
    uart_init(uart0,9600);
    
    pit_init_ms(pit0,5);	            //��ʼ��pit0 ��������Ϊ50ms			
    set_irq_priority(PIT_CH0_IRQn,0);	//����pit0���ȼ�
    enable_irq(PIT_CH0_IRQn);			//����pit0�ж�
    
//    pit_init_ms(pit1,100);	            //��ʼ��pit0 ��������Ϊ50ms			
//    set_irq_priority(PIT_CH1_IRQn,1);	//����pit0���ȼ�
//    enable_irq(PIT_CH1_IRQn);			//����pit0�ж�
    
    irq_init();                                     //��ʼ��irq�������Ҫ�л�irq�����ſ�����KEA128_port_cfg.h�ļ��޸�
    port_pull(I3);                                  //��������
    set_irq_priority(IRQ_IRQn,1);					//�������ȼ�,�����Լ����������� �����÷�ΧΪ 0 - 3
    enable_irq(IRQ_IRQn);							//��pit0���жϿ���
    				
    EnableInterrupts;	
    
    ad_max0 = flash_read(255,4,uint16);                         //��ȡ����
    ad_max1 = flash_read(255,6,uint16);
    lap = flash_read(253,4,uint16);
    charge_energy = flash_read(252,4,uint16);
    set_speed = flash_read(254,4,uint16);
    ftm_pwm_duty(motor_ftm,motor_ch,set_speed); 
}