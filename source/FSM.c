#include "FSM.h"


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
    while(g_current_state !=IDLE){
        for(int i=0; i<4;i++){
           if(hardware_read_floor_sensor(i)){
               g_current_floor =i;
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                g_current_state = IDLE;
            }
        }
    }
}


void fsm_idle() {
    if(!check_if_order()){
        g_current_state =IDLE;
    }
    else if(order_same_floor(g_current_floor)){
        g_current_state=DOORS_OPEN;
    }
    else if(check_if_order()){
        if(get_order_floor() < g_current_floor){
            g_current_state = MOVING_DOWN;
        }
        else{
            g_current_state=MOVING_UP;
        }
    } 
}

void fsm_moving_down(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    g_prev_state = MOVING_DOWN;
    if(hardware_read_floor_sensor(get_order_floor())){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        delete_order_at_floor(get_order_floor());
        g_current_state =DOORS_OPEN; 
    }
    else if((g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7] ||g_orders[8] ||g_orders[9] ||g_orders[10] ||g_orders[11])){
        for(int i=4; i<8;i++){
            if((g_orders[i] && hardware_read_floor_sensor(i%4))|| (g_orders[i+4] && hardware_read_floor_sensor((i+4)%4))){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                delete_order_at_floor(g_current_floor);
                g_current_state=DOORS_OPEN;
            }
        }
    }
}

void fsm_moving_up(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    g_prev_state = MOVING_UP;
    if(hardware_read_floor_sensor(get_order_floor())){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        delete_order_at_floor(get_order_floor());
        g_current_state= DOORS_OPEN;
    }
    else if((g_orders[0] ||g_orders[1] ||g_orders[2] ||g_orders[3] ||g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7]) ){
        for(int i=0; i<4;i++ ){
            if((g_orders[i]&& hardware_read_floor_sensor(i%4)) || (g_orders[i+4] && hardware_read_floor_sensor((i+4)%4))){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                delete_order_at_floor(g_current_floor);
                g_current_state=DOORS_OPEN;
            }
        }
    }
}

void fsm_doors_open(){
    hardware_command_door_open(1);
    if(timer()){
        hardware_command_door_open(0);
        next_order();
    }
}

void next_order(){
    if(hardware_read_floor_sensor(3)){
        g_prev_state = MOVING_DOWN;
    }

    if(hardware_read_floor_sensor(0)){
        g_prev_state = MOVING_UP;
    }

    if(!check_if_order()){
        g_current_state = IDLE;
    }

    if((g_prev_state == MOVING_UP) && (g_orders[0] ||g_orders[1] ||g_orders[2] ||g_orders[3] ||g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7])){
        for(int i =3; i >= 0; i--){
            if(g_orders[i]){
                g_current_order = i;
            }
            else if(g_orders[4+i]){
                g_current_order = (4+i);
            }
        }
        if(get_current_floor() > get_order_floor()){
            g_current_state = MOVING_DOWN;
        }
        else{
            g_current_state = MOVING_UP;
        }
    }

    if((g_prev_state == MOVING_DOWN) && ( g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7] ||g_orders[8] ||g_orders[9] ||g_orders[10] ||g_orders[11])){
        for(int i =7; i>= 4; i--){
            if(g_orders[i]){
                g_current_order =i;
            }
            else if(g_orders[4+i]){
                g_current_order = (4+i);
            }
        }
        if(get_current_floor() < get_order_floor()){
            g_current_state = MOVING_UP;
        }
        else{
            g_current_state = MOVING_DOWN;
        }
    }

    if((g_prev_state ==MOVING_DOWN) &&(!(g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7] ||g_orders[8] ||g_orders[9] ||g_orders[10] ||g_orders[11]))){
        for(int i =3; i >= 0; i--){
            if(g_orders[i]){
                g_current_order = i;
            }
            else if(g_orders[4+i]){
                g_current_order = (4+i);
            }
        }
        if(get_current_floor() > get_order_floor()){
            g_current_state = MOVING_DOWN;
        }
        else{
            g_current_state = MOVING_UP;
        }
    }

    if((g_prev_state == MOVING_UP) && (!(g_orders[0] ||g_orders[1] ||g_orders[2] ||g_orders[3] ||g_orders[4] ||g_orders[5] ||g_orders[6] ||g_orders[7]))){
        for(int i =7; i>= 4; i--){
            if(g_orders[i]){
                g_current_order =i;
            }
            else if(g_orders[4+i]){
                g_current_order = (4+i);
            }
        }
        if(get_current_floor() < get_order_floor()){
            g_current_state = MOVING_UP;
        }
        else{
            g_current_state = MOVING_DOWN;
        }
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
        switch (g_current_state) {
            case INIT:
                init_fsm();
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

                break;
        }
    }
}
