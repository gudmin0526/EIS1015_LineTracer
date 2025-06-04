#include "msp.h"
#include ".\Helpers\Clock.h"
#include ".\Helpers\Led.h"
#include ".\Helpers\SysTick.h"
#include ".\Helpers\Motor.h"
#include ".\Helpers\Timer.h"
#include ".\Helpers\IR.h"
#include <stdio.h>

/**
 * main.c
 */

int main(void) {
    Clock_Init48MHz();
    Motor_Init();
    Led_Init();
    IR_Init();

    while (1) {
       Move_Forward();
       Move_Backward();
       Rotate_Left(90);
       Rotate_Right(90);
    }
}
