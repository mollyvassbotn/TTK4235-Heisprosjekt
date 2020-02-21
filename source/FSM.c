#include "FSM.h"

system_state state = INIT;

// åpner dør
void fsm_open_door(){
    hardware_command_door_open(1);
}

//lukker dør
void fsm_close_door(){
    hardware_command_door_open(0);
}

void init_fsm(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    while(state !=IDLE){
        for(int i=0; i<4;i++){
           if(hardware_read_floor_sensor(i)){
               g_current_floor =i;
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                state = IDLE;
            }
        }
    }
}


void fsm_order_handler() {
    if(!check_if_order()){
        state =IDLE;
    }
    else if(order_same_floor(g_current_floor)){
        state=DOORS_OPEN;
    }
    else if(check_if_order()){
        if(get_order_floor() < g_current_floor){
            state = MOVING_DOWN;
        }
        else{
            state=MOVING_UP;
        }
    } 
}

void fsm_moving_down(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    if(hardware_read_floor_sensor(get_order_floor())){
        //g_current_floor = get_order_floor();
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        delete_order_at_floor(get_order_floor());
        state =DOORS_OPEN; 
    }
    else if((g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7] ||g_orders[8] ||g_orders[9] ||g_orders[10] ||g_orders[11])){
        for(int i=4; i<8;i++){
            if((g_orders[i] && hardware_read_floor_sensor(i%4))|| (g_orders[i+4] && hardware_read_floor_sensor((i+4)%4))){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                delete_order_at_floor(g_current_floor);
                state=DOORS_OPEN;
            }
        }
    }
}

void fsm_moving_up(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    if(hardware_read_floor_sensor(get_order_floor())){
        //g_current_floor = get_order_floor();
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        delete_order_at_floor(get_order_floor());
        state= DOORS_OPEN;
    }
    else if((g_orders[0] ||g_orders[1] ||g_orders[2] ||g_orders[3] ||g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7]) ){
        for(int i=0; i<4;i++ ){
            if((g_orders[i]&& hardware_read_floor_sensor(i%4)) || (g_orders[i+4] && hardware_read_floor_sensor((i+4)%4))){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                delete_order_at_floor(g_current_floor);
                state=DOORS_OPEN;
            }
        }
    }
}

void fsm_doors_open(){
    hardware_command_door_open(1);
    if(timer()){
        hardware_command_door_open(0);
        state=IDLE;
    }
}

void run_fsm() {
    while(1){
        add_order();
        get_current_floor();
        if(hardware_read_stop_signal()){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        break;
    }
        switch (state) {
            case INIT:
                init_fsm();
            case IDLE:
                fsm_order_handler();
                break;
            case DOORS_OPEN:
                fsm_doors_open();
                break;
            case MOVING_DOWN:
                fsm_moving_down();
                break;
            case MOVING_UP:
                fsm_moving_up();
                break;

            case STOP:

                break;
        }
    }
}
