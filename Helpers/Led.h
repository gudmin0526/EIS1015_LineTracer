/*
 * Led.h
 *
 *  Created on: 2025. 5. 29.
 *      Author: devkim
 */

#ifndef LED_H_
#define LED_H_

#include "msp.h"

#define LED_RED   (1 << 0)
#define LED_GREEN (1 << 1)
#define LED_BLUE  (1 << 2)

void Led_Init(void);
void TurnOn_Led(int color);
void TurnOff_Led(void);

#endif /* LED_H_ */
