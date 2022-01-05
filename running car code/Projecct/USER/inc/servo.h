#ifndef __servo_h
#define __servo_h

#include "headfile.h"

#define servo_ftm ftm0
#define servo_ch ftm_ch0
#define servo_hz 100
#define servo_mid 1470  //�����ֵ
#define servo_min 1310  //��ת����
#define servo_max 1630  //��ת����

extern uint16 servo_duty;

void servo_contral();

#endif