#include "order.h"

void order_init() {
    for(int order=0; order<N_ORDERS; order++){
        g_orders[order] = 0;
    }
}

int order_check_if_order() {
    for (int i=0; i<N_ORDERS; i++) {
        if (g_orders[i]) {
            g_current_order =i; 
            return 1;
        } 
    }
    return 0;
}


void order_add_order(){
    for(int order=0; order<N_ORDERS; order++){
        if(hardware_read_order(order%4, order/4)){
            g_orders[order] = 1;
            hardware_command_order_light(order%4, order/4,1);
        }
    }
}


int order_same_floor(int current_floor){
    for(int i=0; i<3; i++){
        if(hardware_read_floor_sensor(current_floor) && g_orders[current_floor + 4*i]) {
            return 1;
        }
    }
    return 0;
}


void order_delete_order_at_floor(int current_floor) {
    if(hardware_read_floor_sensor(current_floor)){
        for(int i=0; i<3; i++){
            g_orders[current_floor +4*i]=0;
            hardware_command_order_light(current_floor, i,0);
        }
    }
}

int order_get_order_floor(){
    return g_current_order %4;
}

void order_delete_all_orders(){
    for(int i=0; i<N_ORDERS; i++){
        g_orders[i] =0;
        order_reset_lights(); 
    }
} 

void order_reset_lights(){
    for(int order =0; order<N_ORDERS; order ++){
        hardware_command_order_light(order%4, order/4,0);
    }
}

int order_get_current_floor(){
     for(int i=0; i<HARDWARE_NUMBER_OF_FLOORS; i++){
         if(hardware_read_floor_sensor(i)){
             g_current_floor=i;
         }
     }
     return g_current_floor;
 }