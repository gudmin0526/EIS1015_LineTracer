/*
 * Timer.h
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "msp.h"
#include <stdint.h>

void (*TimerA2Task)(void);
void TimerA2_Init(void(*task)(void), uint16_t period);
void PWM_Init34(uint16_t period, uint16_t duty3, uint16_t duty4);
void PWM_Duty3(uint16_t duty3);
void PWM_Duty4(uint16_t duty4);

#endif /* TIMER_H_ */
