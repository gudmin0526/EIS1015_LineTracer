#include "msp.h"
#include ".\Helpers\Clock.h"
#include ".\Helpers\Led.h"
#include ".\Helpers\SysTick.h"
#include ".\Helpers\Motor.h"
#include ".\Helpers\Timer.h"
#include ".\Helpers\IR.h"
#include ".\Helpers\Switch.h"
#include <stdio.h>

#define MAX_PATH_LENGTH 500

/**
 * main.c
 */


/**
 * @brief Types of nodes encountered during maze navigation.
 *
 * These node types guide the robot in making directional decisions (L/S/R),
 * performing backtracking (B), or continuing straight through non-decision paths.
 *
 * - Node_Branch, Node_LeftCorner, Node_RightCorner:
 *     → Decision points where the robot must choose a direction.
 *       Push 'L', 'S', or 'R' to the stack accordingly.
 *
 * - Node_Straight:
 *     → Straight segment. No direction is pushed to the stack.
 *
 * - Node_None:
 *     → Dead-end (no valid path). Push 'B' (Backtrack) to the stack.
 *
 * - Node_End:
 *     → Final goal. Used to detect maze completion.
 */
typedef enum {
    Node_None = 0,
    Node_End,
    Node_Straight,
    Node_Branch,
    Node_LeftCorner,
    Node_RightCorner,
} NodeType;


typedef enum {
    Dir_L = 0,
    Dir_S,
    Dir_R,
    Dir_B,
} Direction;


Direction path_stack[MAX_PATH_LENGTH];
int16_t stack_top = -1;
uint8_t backtrack_count = 0;


/**
 * @brief Classifies the current node type using 8 IR sensor inputs.
 *
 * This function determines the topological type of the current location
 * (e.g., straight path, corner, branch, dead-end) to guide maze navigation.
 * It is designed to support direction logging (L/S/R/B) for optimal path extraction.
 *
 * Node detection logic:
 * - Node_Branch       : Both left and right sensors detect line → junction
 * - Node_End          : Front line strongly detected, no left/right → dead-end
 * - Node_LeftCorner   : Only left-side sensors detect line → left turn
 * - Node_RightCorner  : Only right-side sensors detect line → right turn
 * - Node_Straight     : Only front-center sensors detect line → straight path
 * - Node_None         : No path detected → backtrack needed
 *
 * @param sensors An array of 8 binary IR sensor values (1 = line, 0 = no line)
 * @return NodeType corresponding to the detected topology
 */
NodeType Detect_NodeType(uint8_t sensors[8]) {
    uint8_t left  = sensors[0] || sensors[1];
    uint8_t right = sensors[6] || sensors[7];
    uint8_t front_left  = sensors[2] && sensors[3] && sensors[4];
    uint8_t front_right = sensors[3] && sensors[4] && sensors[5];
    uint8_t front_center = sensors[3] || sensors[4];
    uint8_t front_strong = front_left || front_right;

    if (left && right)
        return Node_Branch;
    if (front_strong && !left && !right)
        return Node_End;
    if (left)
        return Node_LeftCorner;
    if (right)
        return Node_RightCorner;
    if (front_center)
        return Node_Straight;
    return Node_None;
}


/**
 * @brief Navigates a maze using the left-hand rule based on IR sensor input.
 *
 * If a line is detected on the left side (sensors 0–2), turn left 90 degrees.
 * If a line is detected in the front (sensors 3–4), move forward.
 * If a line is detected on the right side (sensors 5–7), turn right 90 degrees.
 * If no line is detected on any side, turn around (180 degrees).
 *
 * @param sensors an array of 8 IR sensor readings (0 = no line, 1 = line detected)
 */
void Maze_Navigate(NodeType type) {
    if (type == Node_End)
        return;
    if (type == Node_Branch || type == Node_LeftCorner) {
        if (backtrack_co)
        path_stack[stack_top++] = Dir_L;
        Rotate_Left(90);
        Motor_Stop(10);
        Move_Forward(300);
        Motor_Stop(10);
    } else if (type == Node_RightCorner) {
        path_stack[stack_top++] = Dir_S;
        is_right = 1;
        Move_Forward(300);
        Motor_Stop(10);
    } else if (type == Node_Straight) {
        Move_Forward(300);
        Motor_Stop(10);
    } else {
        path_stack[stack_top++] = Dir_B;
        while (path_stack[stack_top] != Dir_S || path_stack[stack_top] != Dir_L) {
            backtrack_count++;
            stack_top--;
        }
        path_stack[stack_top] = Dir_R;

        Move_Backward(300);
        Motor_Stop(10);
        Rotate_Left(90);
        Motor_Stop(10);
        Rotate_Left(90);
        Motor_Stop(10);
    }
}


void task(void) {
    uint8_t sensors[8];
    while (1) {
        Read_IR_Sensor(sensors);
        NodeType type = Detect_NodeType(sensors);
        Maze_Navigate(type);
    }
}


int main(void) {
    Clock_Init48MHz();
    Motor_Init();
    Led_Init();
    IR_Init();
    Switch_Init();

    Move_Forward(500);
    TimerA2_Init(task, 5000);
}
