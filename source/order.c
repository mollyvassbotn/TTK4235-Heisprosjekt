#include "order.h"

orders[12] = {0};

int check_if_order() {
    for (int i=0; i<12; i++) {
        if (orders[i]) {
            return 1;
        } 
    }
    return 0;
}

void add_order(HardwareOrder type, int floor){
    int button=3;
    orders[button*floor + type] =1;
}

void place_order(){
    for(int i=0; i<4; i++){ //kall variablene floor!!
        for(int j=0; j<3; i++){
            if(!((i==0 && j==1) || (i==3 && j==0))){
                if(hardware_read_order(i, j));
                 add_order(i,j);
            }
        }
    }
}

int order_same_floor(){
    for(int i=0; i<3; i++){
        if(hardware_read_floor_sensor(i) && hardware_read_order(i,3)) {
            return 1;
        }
    return 0;
    }
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