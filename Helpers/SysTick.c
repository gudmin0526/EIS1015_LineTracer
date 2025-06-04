/*
 * SysTick.c
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#include ".\SysTick.h"


void SysTick_Init(void) {
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->CTRL = 0x00000005;
}

void SysTick_Wait1us(int delay) {
    SysTick->LOAD = 48 * delay;
    SysTick->VAL = 0;
    while ((SysTick->CTRL & 0x00010000) == 0) {};
}

void SysTick_Wait1ms(int delay) {
    int i;
    for (i = 0; i < delay; i++)
        SysTick_Wait1us(1000);
}

void SysTick_Wait1s() {
        SysTick_Wait1ms(1000);
}
