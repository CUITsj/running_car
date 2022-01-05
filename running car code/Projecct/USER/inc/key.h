#ifndef _key_h
#define _key_h

#include "headfile.h"

#define KEY1 A1 //choose	
#define KEY2 D2 //k--
#define KEY3 D3 //k++
#define KEY4 D4 //start

extern void key_init(void);
extern void key_deal(void);

extern uint8 find_max;

#endif