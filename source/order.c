#include "order.h"


int orders[12] = {0};

int check_if_order() {
    for (int i=0; i<12; i++) {
        if (orders[i]) {
            return 1;
        } 
    }
    return 0;
}


void add_order(){
    for(int order=0; order<12; order++){
        orders[order] = hardware_read_order(order%4, order/4);
    }
}

void try_elevator(){
    while(1){
        add_order();
        if(check_if_order()){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

    }
}

int order_same_floor(){
    for(int floor=0; floor<3; floor++){
        if(hardware_read_floor_sensor(floor) && hardware_read_order(floor,3)) {
            return 1;
        }
    }
    return 0;
}

void delete_order_at_floor(int current_floor) {
    if(hardware_read_floor_sensor(current_floor)){
        for(int i=0; i<3; i++){
        orders[current_floor +4*i]=0;
        }
    }
}

void delete_all_orders(){
    for(int i=0; i<12; i++){
        orders[i] =0;
    }
} 

void reset_lights(){
    for(int order =0; order<12; order ++){
        hardware_command_order_light(order%4, order/4,0);
    }
}

 void queue_system(){
     reset_lights();
     while(1){
        add_order();
        for(int order =0; order<12; order ++){
            if(orders[order]){
                hardware_command_order_light(order%4, order/4,1);
            }
        }
        for(int floor=0; floor<4; floor++){
            if(hardware_read_floor_sensor(floor)){
                hardware_command_door_open(1);
                if(timer()){
                    hardware_command_door_open(0);
                }
            }
        }
        // if(hardware_read_floor_sensor(2)){
        //     hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        // }
        // if(hardware_read_floor_sensor(1)){
        //     hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        // }
        if(orders[0] || orders[1] || orders[2]){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        if(orders[9] || orders[10] || orders[11]){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }
        if(orders[4] || orders[5] || orders[6] || orders[7]){
            hardware_command_door_open(1);
        }
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
     }
 }