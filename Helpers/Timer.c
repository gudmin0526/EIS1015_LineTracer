/*
 * Timer.c
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#include ".\Timer.h"
#include <stdint.h>

void (*TimerA2Task)(void) = 0;

 void TimerA2_Init(void(*task)(void), uint16_t period) {
    TimerA2Task = task;
    TIMER_A2->CTL = 0x0280; // Main divider: 4, SMLCK=12MHz
    TIMER_A2->CCTL[0] = 0x0010; // compare mode, IRQ enable
    TIMER_A2->CCR[0] = (period - 1); // compare match value
    TIMER_A2->EX0 = 0x0005; // Extended divider 6
    NVIC->IP[3] = (NVIC->IP[3]&0xFFFFFF00)|0x00000040; // IRQ 12 우선순위 설정
    NVIC->ISER[0] = 0x00001000; // IRQ 12 enable
    TIMER_A2->CTL |= 0x0014; // UP mode, clear TA2R register
}

 void TA2_0_IRQHandler(void){
     TIMER_A2->CCTL[0] &= ~0x0001;
     (*TimerA2Task)();
 }

 void PWM_Duty3(uint16_t duty3) {
     TIMER_A0->CCR[3] = duty3;
 }

 void PWM_Duty4(uint16_t duty4) {
     TIMER_A0->CCR[4] = duty4;
 }

 void PWM_Init34(uint16_t period, uint16_t duty3, uint16_t duty4){
     P2->DIR |= 0xC0; // set P2.6 P2.7 as output
     P2->SEL0 |= 0xC0; // set as Timer instead GPIO
     P2->SEL1 &= ~0xC0;

     TIMER_A0->CCTL[0] = 0x0080; // CCR0 OUT bit 설정
     TIMER_A0->CCR[0] = period; // PWM 주기 설정

     TIMER_A0->EX0 = 0x0000; // No Extended divider

     TIMER_A0->CCTL[3] = 0x0040; // Toggle/Reset Mode
     TIMER_A0->CCR[3] = duty3;
     TIMER_A0->CCTL[4] = 0x0040; // Toggle/Reset Mode
     TIMER_A0->CCR[4] = duty4;

     TIMER_A0->CTL = 0x02F0; // Main divider: 8, SMLCK=12MHz, UP mode
 }
