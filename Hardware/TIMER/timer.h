#ifndef __TIMER_H
#define __TIMER_H
#include "systick.h"
#include "gd32e23x.h"
#include <stdint.h>

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

/* -------------------------------------------------------------------------- */
//采用定时器5，编写宏定义
/* -------------------------------------------------------------------------- */
#define BSP_TIMER TIMER5
void TIM6_Int_Init(u16 arr,u16 psc);
#endif























