/*
 * Motor.h
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define LEFT_MOTOR_CALIBRATION 0.025f

#include "msp.h"
#include ".\Timer.h"
#include ".\Clock.h"

void Motor_Init(void);
void Move(uint16_t leftDuty, uint16_t rightDuty);
void Left_Forward(void);
void Left_Backward(void);
void Right_Forward(void);
void Right_Backward(void);

void Move_Forward(uint16_t time);
void Move_Backward(uint16_t time);
void Rotate_Left(uint16_t degree);
void Rotate_Right(uint16_t degree);
void Motor_Stop(uint16_t time);

#endif /* MOTOR_H_ */
