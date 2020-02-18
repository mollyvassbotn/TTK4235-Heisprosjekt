#include "timer.h"

time_t start_time;
time_t close_time = 3; 

void start_timer(){
    start_time = time(NULL);
}


int timer() {
    time_t close_time=3;

    start_time = time(NULL);

    while(time(NULL) > close_time+ start_time) {
        return 1;
    }
    
    return 0;
}