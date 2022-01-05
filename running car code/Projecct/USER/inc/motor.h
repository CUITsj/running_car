#ifndef __motor_h
#define __motor_h

#include "headfile.h"

#define motor_ftm ftm2
#define motor_ch ftm_ch0 
#define motor_hz 1000

extern uint16 set_speed;

extern int motor_duty;

void motor_measure();
void motor_pid(int16 gsp);
void stop_pid();

#endif