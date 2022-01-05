#include "servo.h"

uint16 servo_duty = servo_mid;  

void servo_contral(void)
{
  int16 ierror = 0;
  static int16 last_error = 0;
  
  ierror = (result[0] - result[1])*100/(result[0] + result[1]);
  servo_duty = servo_mid + ierror*1.66 + (ierror - last_error)*2.55;
  
  //70%占空比  P:1.6  D:2.1
  //80%占空比  P:1.66 D:2.55
  last_error = ierror;
  
  if(servo_duty > servo_max)
  {
    servo_duty = servo_max;
  }
  if(servo_duty < servo_min)
  {
    servo_duty = servo_min;
  }
  
  ftm_pwm_duty(servo_ftm,servo_ch,servo_duty); 
}