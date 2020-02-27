/**
 * @file
 * @brief Finite state machine. Chooses the next state for the elevator.
 */


#ifndef FSM_H
#define FSM_H

#include "order.h"
#include "timer.h"
#include "hardware.h"

/**
 * @brief The different states the elevator can be in
 */
typedef enum{
    INIT,
    IDLE,
    MOVING_UP,
    MOVING_DOWN,
    DOORS_OPEN,
    STOP
} system_state;


int g_between_floors;

system_state g_current_state;

system_state g_prev_state;


/**
 * @brief Defines a state for the elevator. Updates current floor.
 */
void fsm_init();


/**
 * @brief Checks if there are any orders, sets the next state. 
 */
void fsm_idle();


/**
 * @brief Sets the elevator direction downwards. If it is an order in the same direction as the 
 * current order it will stop there, otherwise it will stop at the floor of the current order. 
 */
void fsm_moving_down();


/**
 * @brief Sets the elevator direction upwards. If it is an order in the same direction as the 
 * current order it will stop there, otherwise it will stop at the floor of the current order. 
 */
void fsm_moving_up();


/**
 * @brief Deletes the orders at the current floor. Opens the door, and keeps it open for 3 seconds. If the obstuction signal
 * is active, the door will open as long as it is active. Then it will close after
 * 3 seconds. As long as the stop button is pushed the stop light will be on, and if the elevator is at a floor the 
 * doors will open as long as stop is active and will close 3 seconds after the button is released. 
 */
void fsm_doors_open();


/**
 * @brief Stops the elevator immidiately. If the stop button is pushed, all orders
 * will be deleted, and the stop light will be on. If the elevator is at a floor as the stop button is pushed, the
 * doors will open.
 */
void fsm_stop();


/**
 * @brief Queue system for the elevator. Priorities the orders, based on the
 * previous direction.
 */
void fsm_next_order();


/**
 * @brief Updates the position, defines whether the elevator is above, below or at
 *  a floor, and sets the floor indicators. 
 */
void fsm_update_position();


/**
 * @brief Updates orders and current floor. Let the elevator switch between different states. 
 */
void fsm_run();


#endif

