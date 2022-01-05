#include "init.h"

void init(void)
{
    get_clk();              //获取时钟频率 必须执行
     
    FLASH_Init();
    OLED_Init();
    
    //初始化AD通道
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
    
    pit_init_ms(pit0,5);	            //初始化pit0 周期设置为50ms			
    set_irq_priority(PIT_CH0_IRQn,0);	//设置pit0优先级
    enable_irq(PIT_CH0_IRQn);			//开启pit0中断
    
//    pit_init_ms(pit1,100);	            //初始化pit0 周期设置为50ms			
//    set_irq_priority(PIT_CH1_IRQn,1);	//设置pit0优先级
//    enable_irq(PIT_CH1_IRQn);			//开启pit0中断
    
    irq_init();                                     //初始化irq，如果需要切换irq的引脚可以在KEA128_port_cfg.h文件修改
    port_pull(I3);                                  //设置上拉
    set_irq_priority(IRQ_IRQn,1);					//设置优先级,根据自己的需求设置 可设置范围为 0 - 3
    enable_irq(IRQ_IRQn);							//打开pit0的中断开关
    				
    EnableInterrupts;	
    
    ad_max0 = flash_read(255,4,uint16);                         //读取数据
    ad_max1 = flash_read(255,6,uint16);
    lap = flash_read(253,4,uint16);
    charge_energy = flash_read(252,4,uint16);
    set_speed = flash_read(254,4,uint16);
    ftm_pwm_duty(motor_ftm,motor_ch,set_speed); 
}