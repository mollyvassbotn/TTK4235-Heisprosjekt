#include "timer.h"

clock_t start_time;

int timer(){
    start_time = clock();
    while((float)(clock()-start_time)/(CLOCKS_PER_SEC)<3){
        add_order();
    }
    return 1;
}

