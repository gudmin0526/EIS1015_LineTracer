/*
 * Motor.c
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#include ".\Motor.h"

void Motor_Init(void) {
    P3->SEL0 &= ~0xC0; // 67: nSLPR, nSLPL
    P3->SEL1 &= ~0xC0;
    P3->DIR  |=  0xC0;
    P3->OUT  &= ~0xC0;

    P5->SEL0 &= ~0x30; // 45: DIRR, DIRL
    P5->SEL1 &= ~0x30;
    P5->DIR  |=  0x30;
    P5->OUT  &= ~0x30;

    P2->SEL0 &= ~0xC0; // 67: PWMR, PWML
    P2->SEL1 &= ~0xC0;
    P2->DIR  |=  0xC0;
    P2->OUT  &= ~0xC0;

    // 주기 = 15'000 / 1'500'000 = 0.01s = 10ms
    // 초당 100개의 PWM 사이클 출력, 이후 듀티를 통해 조절
    PWM_Init34(15000, 0, 0);
}

void Move(uint16_t leftDuty, uint16_t rightDuty) {
    P3->OUT |= 0xC0;
    PWM_Duty3(rightDuty);
    PWM_Duty4(leftDuty);
}

void Left_Forward() {
    P5->OUT &= ~0x10;
}

void Left_Backward() {
    P5->OUT |= 0x10;
}

void Right_Forward() {
    P5->OUT &= ~0x20;
}

void Right_Backward() {
    P5->OUT |= 0x20;
}

void Move_Forward(uint16_t time) {
    Left_Forward();
    Right_Forward();
    Move(1500, 1500);
    Clock_Delay1ms(time);
}

void Move_Backward(uint16_t time) {
    Left_Backward();
    Right_Backward();
    Move(1500, 1500);
    Clock_Delay1ms(time);
}

void Rotate_Left(uint16_t degree) {
    Left_Backward();
    Right_Forward();
    Move(1500, 1500);
    Clock_Delay1ms(25 * degree);
}

void Rotate_Right(uint16_t degree) {
    Left_Forward();
    Right_Backward();
    Move(1500, 1500);
    Clock_Delay1ms(25 * degree);
}

void Motor_Stop(uint16_t time) {
    P3->OUT &= ~0xC0;
    Clock_Delay1ms(time);
}

