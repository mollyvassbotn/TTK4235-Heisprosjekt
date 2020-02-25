/**
 * @file
 * @brief Finite state machine. Chooses the next state for the elevator.
 */

#ifndef FSM_H
#define FSM_H

#include "order.h"
#include "timer.h"
#include "hardware.h"

typedef enum{
    INIT,
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    DOORS_OPEN,
    STOP
} system_state;

typedef struct{
    int floor;
    int above;
} Position;

int g_between_floors;

system_state g_current_state;

system_state g_prev_state;

/*
void fsm_open_door();

void fsm_close_door();
*/


/**
 * @brief Defines a state for the elevator. Updates current floor.
 */
void init_fsm();


/**
 * @brief Checks if there are any orders, and sets current state.
 */
void fsm_idle();


/**
 * @brief Sets the elevator direction downwards, and stops at the ordered floors in
 * the same direction. The orders will be deleted after they are done.
 */
void fsm_moving_down();


/**
 * @brief Sets the elevator direction upwards, and stops at the ordered floors in
 * the same direction. The orders will be deleted after they are done.
 */
void fsm_moving_up();


/**
 * @brief Opens the door, and keeps it open for 3 seconds. If the obstuction signal
 * is active, the door will open as long as it is active. Then it will close after
 * seconds.
 */
void fsm_doors_open();


/**
 * @brief Stops the elevator immidiately. If the stop button is pushed, all orders
 * will be deleted. If the elevator is at a floor as the stop button is pushed, the
 * doors will open.
 */
void fsm_stop();


/**
 * @brief Queue system for the elevator. Priorities the orders, based on the
 * previous direction.
 */
void fsm_next_order();


/**
 * @brief Updates orders and current floor. Sets the elevator state.
 */
void run_fsm();


#endif

