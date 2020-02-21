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

void fsm_open_door();

void fsm_close_door();

void fsm_order_handler();

void init_fsm();

void fsm_moving_down();

void fsm_moving_up();

void fsm_doors_open();

void run_fsm();


#endif

