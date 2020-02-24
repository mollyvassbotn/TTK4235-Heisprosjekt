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
    delete_all_orders();
    orders_init();
    init_fsm();
    reset_lights();

    add_order();
    get_current_floor();
    g_current_state = INIT;
    run_fsm();

    return 0;
}