#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "order.h"
#include "FSM.h"


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    order_delete_all_orders();
    order_init();
    fsm_init();
    order_reset_lights();

    order_add_order();
    order_get_current_floor();
    g_current_state = INIT;
    fsm_run();

    return 0;
}
