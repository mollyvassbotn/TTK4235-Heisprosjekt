#include "FSM.h"

system_state state = IDLE;

// åpner dør
void fsm_open_door(){
    hardware_command_door_open(1);
}

//lukker dør
void fsm_close_door(){
    hardware_command_door_open(0);
}



// void fsm_order_handler() {
//     if(!check_if_order()){
//         state =IDLE;
//     }
//     else if(check_if_order()){
//         //gå til korrekt etasje
//         state=IDLE;
//     } 
//     if(order_same_floor()){
//         state=DOORS_OPEN;
//     }
// }

// void run_fsm() {
//     while(1){
//         if (hardware_read_stop_signal){
//             state = STOP;
//         }

//         switch (state) {
//             case IDLE:
//                 fsm_order_handler();
//             case DOORS_OPEN:

            
    
//         }
//     }
// }
