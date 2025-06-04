/*
 * Motor.h
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "msp.h"
#include ".\Timer.h"

void Motor_Init(void);
void Move(uint16_t leftDuty, uint16_t rightDuty);
void Left_Forward();
void Left_Backward();
void Right_Forward();
void Right_Backward();

void Move_Forward();
void Move_Backward();
void Rotate_Left();
void Rotate_Right();

#endif /* MOTOR_H_ */
