/*
 * Led.h
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#ifndef LED_H_
#define LED_H_

#include "msp.h"

#define LED_RED   0x01
#define LED_GREEN 0x02
#define LED_BLUE  0x04
#define LED_WHITE 0x07

void Led_Init(void);
void TurnOn_Led(int color);
void TurnOff_Led(void);

#endif /* LED_H_ */
