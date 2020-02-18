#include "FSM.h"

system_state state = IDLE;

void fsm_order_handler() {
    if(!check_if_order()){
        state =IDLE;
    }
    else if(check_if_order()){
        //gå til korrekt etasje
        state=IDLE;
    } 
    if(order_same_floor()){
        state=DOORS_OPEN;
    }
}

void run_fsm() {
    while(1){
        if (hardware_read_stop_signal){
            state = STOP;
        }

        switch (state) {
            case IDLE:
                fsm_order_handler();
            case DOORS_OPEN:
            
    
        }
    }
}