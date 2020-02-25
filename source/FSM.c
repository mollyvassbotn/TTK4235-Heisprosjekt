#include "FSM.h"

void fsm_init(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    while(g_current_state !=IDLE){
        for(int i=0; i<4;i++){
           if(hardware_read_floor_sensor(i)){
                g_current_floor =i;
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                g_current_state = IDLE;
                g_prev_state =MOVING_DOWN;
                g_between_floors= 0;
            }
        }
    }
}


void fsm_idle() {
    if(!order_check_if_order()){
        g_current_state =IDLE;
    }
    else if(order_same_floor(g_current_floor)){
        g_current_state=DOORS_OPEN;
    }
    else if(order_check_if_order()){
        if((order_get_order_floor() < g_current_floor) || ((order_get_order_floor() <= g_current_floor) &&(g_between_floors == 1))){
            g_current_state = MOVING_DOWN;
        }
        else{ //if((get_order_floor()> g_current_floor) || (hardware_read_floor_sensor(g_current_floor) && (g_between_floors ==-1))){
            g_current_state=MOVING_UP;
        }
    } 
}


void fsm_moving_down(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    g_prev_state = MOVING_DOWN;
    if(hardware_read_floor_sensor(order_get_order_floor())){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        order_delete_order_at_floor(order_get_order_floor());
        g_current_state =DOORS_OPEN; 
    }
    else if((g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7] ||g_orders[8] ||g_orders[9] ||g_orders[10] ||g_orders[11])){
        for(int i=4; i<8;i++){
            if((g_orders[i] && hardware_read_floor_sensor(i%4))|| (g_orders[i+4] && hardware_read_floor_sensor((i+4)%4))){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                order_delete_order_at_floor(g_current_floor);
                g_current_state=DOORS_OPEN;
            }
        }
    }
}


void fsm_moving_up(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    g_prev_state = MOVING_UP;
    if(hardware_read_floor_sensor(order_get_order_floor())){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        order_delete_order_at_floor(order_get_order_floor());
        g_current_state= DOORS_OPEN;
    }
    else if((g_orders[0] ||g_orders[1] ||g_orders[2] ||g_orders[3] ||g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7]) ){
        for(int i=0; i<4;i++ ){
            if((g_orders[i]&& hardware_read_floor_sensor(i%4)) || (g_orders[i+4] && hardware_read_floor_sensor((i+4)%4))){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                order_delete_order_at_floor(g_current_floor);
                g_current_state=DOORS_OPEN;
            }
        }
    }
}


void fsm_doors_open(){
    g_between_floors =0;
    hardware_command_door_open(1);
    if(timer()){
        hardware_command_door_open(0);
        fsm_next_order();
    }
}


void fsm_stop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    while(hardware_read_stop_signal()){
        hardware_command_stop_light(1);
        order_delete_all_orders();
        if (hardware_read_floor_sensor(g_current_floor)) {
            hardware_command_door_open(1);
        }
    }
    if (hardware_read_floor_sensor(g_current_floor)) {
        hardware_command_stop_light(0);
        g_current_state = DOORS_OPEN;
    }
    else if (!(hardware_read_floor_sensor(g_current_floor))) {
        hardware_command_stop_light(0);
        g_current_state = IDLE;
    }
    
}


void fsm_next_order(){
    if(!order_check_if_order()){
        g_current_state = IDLE;
    }

    else if(g_prev_state == MOVING_UP){
        for(int i =3; i> order_get_current_floor(); i--){
            for(int j=0; j<3; j++){
                if(g_orders[4*j+i]){
                    g_current_order =4*j+i;
                    g_current_state =MOVING_UP;
                    return;
                }
            }
        }
        for(int i=0; i< order_get_current_floor(); i++){
            for(int j=0; j<3; j++){
                if(g_orders[4*j+i]){
                    g_current_order =4*j+i;
                    g_current_state =MOVING_DOWN;
                    return;
                }
            }
        }

    }
    else if(g_prev_state ==MOVING_DOWN){
        for(int i=0; i< order_get_current_floor(); i++){
            for(int j=0; j<3; j++){
                if(g_orders[4*j+i]){
                    g_current_order =4*j+i;
                    g_current_state =MOVING_DOWN;
                    return;
                }
            }
        }
        for(int i=3; i> order_get_current_floor(); i--){
            for(int j=0; j<3; j++){
                if(g_orders[4*j+i]){
                    g_current_order =4*j+i;
                    g_current_state =MOVING_UP;
                    return;
                }
            }
        }
    }
}


void fsm_update_position(){
    for(int i=0; i<4; i++){
        if(hardware_read_floor_sensor(i)){
            g_current_floor =i;
            hardware_command_floor_indicator_on(i);
            if(g_current_state == MOVING_UP){
                g_between_floors =1;
            }
            else if(g_current_state ==MOVING_DOWN){
                g_between_floors = -1;
            }
        }
    }
}


void fsm_run() {
    while(1){
        fsm_update_position();
        order_add_order();
        //get_current_floor();
        if(hardware_read_stop_signal()){
            g_current_state=STOP;
        }
        if(hardware_read_obstruction_signal() && hardware_read_floor_sensor(g_current_order)){
            g_current_state =DOORS_OPEN;
        }
        // if(hardware_read_obstruction_signal()){
        //     break;
        // }
        switch (g_current_state) {
            case INIT:
            fsm_init();
                break;
            case IDLE:
                fsm_idle();
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
                fsm_stop();
                break;
        }
    }
}
