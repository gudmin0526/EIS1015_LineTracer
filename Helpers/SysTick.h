/*
 * SysTick.h
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "msp.h"

void SysTick_Init(void);
void SysTick_Wait1us(int delay);
void SysTick_Wait1ms(int delay);
void SysTick_Wait1s();

#endif /* SYSTICK_H_ */
