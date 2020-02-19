#include "timer.h"


int timer(){
    clock_t start_time = clock();
    while((float)(clock()-start_time)/(CLOCKS_PER_SEC)<3){
    }
    return 1;
}

