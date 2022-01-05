#include "show.h"

uint8 mode = 0;
uint16 charge_energy = 0, remain_energy = 0;

void oled_show()
{
    if (mode == 0)            //黑屏
    {
      OLED_Fill(0x00);
    }
    else if (mode == 1)       //显示电感最大值
    {
      OLED_P6x8Str(0,0,"Lm:");
      OLED_P6x8Str(64,0,"Rm:");
      OLED_Print_Num1(80, 0, ad_max0);      //右
      OLED_Print_Num1(16, 0, ad_max1);      //左
    }
    else if (mode == 2)       //显示速度设定值
    {
      OLED_P6x8Str(0,0,"Current speed:");
      OLED_Print_Num1(84, 0, set_speed);     
    }
    else if (mode == 3)       //车跑的圈数
    {
      OLED_P6x8Str(0,0,"The lap to run:");
      OLED_P6x8Str(0,2,"0:stop;");
      OLED_P6x8Str(0,3,"1:a lap;");
      OLED_P6x8Str(0,4,"2:two laps;");
      OLED_P6x8Str(0,5,"3:until battery dies.");
      OLED_Print_Num1(90, 0, lap);      
    }
    else if (mode == 4)       //充电能量
    {
      OLED_P6x8Str(0,0,"Charge energy:");
      OLED_P6x8Str(121,0,"J");
      OLED_Print_Num1(84, 0, charge_energy);     
      OLED_P6x8Str(0,2,"Remain energy:");
      OLED_P6x8Str(121,2,"J");
      OLED_Print_Num1(84, 2, remain_energy);     
      
    }
    else if (mode == 5)       //当前电感值
    {
      OLED_P6x8Str(0,0,"Lc:");
      OLED_P6x8Str(64,0,"Rc:");
      OLED_P6x8Str(0,2,"SUB/ADD:");
      OLED_Print_Num1(80, 0, result[0]);      
      OLED_Print_Num1(16, 0, result[1]);    
      OLED_Print_Num1(48, 2, (result[0] - result[1])*100/(result[0] + result[1]));      
    }
}