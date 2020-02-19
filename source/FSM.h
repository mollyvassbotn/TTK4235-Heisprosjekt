#ifndef FSM_H
#define FSM_H

#include "order.h"
#include "timer.h"
#include "hardware.h"

typedef enum{
    IDLE,
    MOVING,
    DOORS_OPEN,
    STOP
} system_state;

void fsm_open_door();
void fsm_close_door();






#endif

