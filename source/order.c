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

// void add_order(HardwareOrder type, int floor){
//     int button=3;
//     orders[type*button + floor] =1;
// }

// void place_order(){
//     for(int button=0; button<3; button++){ 
//         for(int floor=0; floor<4; floor++){
//             if(!((floor==0 && button==1) || (floor==3 && button==0))){
//                 if(hardware_read_order(floor, button)){
//                     add_order(button,floor);
//                     printf("Added order");
//                 }
//             }
//         }
//     }
//     printf("Test");
// }

void place_order(){
    for(int order=0; order<12; order++){
        orders[order] = hardware_read_order(order%4, order/4);
    }
    for(int i =0; i<10; i++){
        printf("%d", orders[i]);
        //printf("AAAAA");
    }
}

void try_elevator(){
    while(1){
        place_order();
        if(check_if_order()){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
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

void delete_order(HardwareMovement type, int floor) {
    int button=3;
    orders[button*floor + type] =0;
}

void delete_all_orders(){
    for(int i=0; i<12; i++){
        orders[i] =0;
    }
} 
