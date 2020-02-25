#include "timer.h"

clock_t start_time;

int timer(){
    start_time = clock();
    while((float)(clock()-start_time)/(CLOCKS_PER_SEC)<3){
        order_add_order();
        if (hardware_read_obstruction_signal()) {
            start_time = clock();
        }
    }
    return 1;
}

