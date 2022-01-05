#include "key.h"

uint8 find_max = 0;

void key_init(void)
{
    gpio_init(KEY1,GPI,1);  //初始化IO口
    gpio_init(KEY2,GPI,1);
    gpio_init(KEY3,GPI,1);
    gpio_init(KEY4,GPI,1);
    
    port_pull(KEY1);        //设置IO口内部上拉，或者外部上拉
    port_pull(KEY2);
    port_pull(KEY3);
    port_pull(KEY4);
}

void key_deal(void)
{
  uint16 write1[2];
  static uint8 count = 0;
  
    if(gpio_get(KEY1) == 0)       //choose
    {
        systick_delay_ms(100);//延时10ms
        if (gpio_get(KEY1) == 0)
        {
            if (mode == 1)
            {
              count++;
            }
            if (mode == 1 && count == 1 && find_max == 0)       //按一下开始寻找最大值
            {
              find_max = 1;
              ad_max0 = 0;
              ad_max1 = 0;
              OLED_P6x8Str(0,2,"Update maximum...");
            }
            if (mode == 1 && find_max == 1 && count == 2)       //再按一下存储找到的最大值
            {
              write1[0] = ad_max0;
              write1[1] = ad_max1;
              FLASH_EraseSector(255);                                      //擦除最后一个扇区
              FLASH_WriteSector(255,(const uint8 *)write1,4,4);            //写入四个字节到最后一个扇区 偏移4字节
              find_max = 0;
              count = 0;
              OLED_P6x8Str(0,4,"Update complete.");
            }
            if (mode == 2)
            {
              write1[0] = set_speed;
              write1[1] = set_speed;
              FLASH_EraseSector(254);                                      //擦除倒数第二个扇区
              FLASH_WriteSector(254,(const uint8 *)write1,4,4);            //写入四个字节到最后一个扇区 偏移4字节
              OLED_P6x8Str(0,4,"Complete set.");
              ftm_pwm_duty(motor_ftm,motor_ch,set_speed); //一定要加上不然本次速度不会改变！！！
            }
            if (mode == 3)
            {
              write1[0] = lap;
              write1[1] = lap;
              FLASH_EraseSector(253);                                      //擦除倒数第三个扇区
              FLASH_WriteSector(253,(const uint8 *)write1,4,4);            //写入四个字节到最后一个扇区 偏移4字节
              OLED_P6x8Str(78,7,"complete");
            }
            if (mode == 4)
            {
              write1[0] = charge_energy;
              write1[1] = charge_energy;
              FLASH_EraseSector(252);                                      //擦除倒数第四个扇区
              FLASH_WriteSector(252,(const uint8 *)write1,4,4);            //写入四个字节到最后一个扇区 偏移4字节
              OLED_P6x8Str(0,6,"Complete set.");
            }
        }
    }
    
    if(gpio_get(KEY2) == 0)       //k--
    {
      systick_delay_ms(100);//延时10ms
      if (gpio_get(KEY2) == 0)
      {
        if (mode == 2)
        {
          set_speed = set_speed - 20;
          OLED_P6x8Str(0,2,"Setting speed...");
          if (set_speed <= 20)
          {
            set_speed = 20;
          }
        }
        if (mode == 3)
        {
          lap--;
          OLED_P6x8Str(0,7,"Change lap...");
          if (lap > 3)
          {
            lap = 3;
          }
        }
        if (mode == 4)
        {
          charge_energy = charge_energy - 20;
          OLED_P6x8Str(0,4,"Set charge energy...");
          if (charge_energy > 1000)
          {
            charge_energy = 0;
          }
        }
      }
    }
    
    if(gpio_get(KEY3) == 0)       //k++
    {
      systick_delay_ms(100);//延时10ms
      if (gpio_get(KEY3) == 0)
      {
        if (mode == 2)
        {
          set_speed = set_speed + 20;
          OLED_P6x8Str(0,2,"Setting speed...");
          if (set_speed >= 1000)
          {
            set_speed = 1000;
          }
        }
        if (mode == 3)
        {
          lap++;
          OLED_P6x8Str(0,7,"Change lap...");
          if (lap > 3)
          {
            lap = 0;
          }
        }
        if (mode == 4)
        {
          charge_energy = charge_energy + 20;
          OLED_P6x8Str(0,4,"Set charge energy...");
          if (charge_energy > 1000)
          {
            charge_energy = 0;
          }
        }
      }
    }
    
    if(gpio_get(KEY4) == 0)       //start
    {
        systick_delay_ms(100);//延时10ms
        if (gpio_get(KEY4) == 0)
        {
            mode++;
            OLED_Fill(0x00);
            
           if (mode == 6)
           {
             mode = 0;
           }
        }
    }
}