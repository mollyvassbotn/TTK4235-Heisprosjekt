#include "timer.h"

clock_t start_time;

int timer(){
    start_time = clock();
    while((float)(clock()-start_time)/(CLOCKS_PER_SEC)<3){
        order_add_order();
        order_delete_order_at_floor(g_current_floor);
        if (hardware_read_obstruction_signal()) {
            start_time = clock();
        }
        while(hardware_read_stop_signal()){
            hardware_command_stop_light(1);
            order_delete_all_orders();
            start_time=clock();
        }
        hardware_command_stop_light(0);
    }
    return 1;
}