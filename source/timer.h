/**
 * @file
 * @brief Timer for the lights, obstruction and stop. 
 */


#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <stdio.h>
#include "order.h"

/**
 * @brief Checks if it has been more than three seconds. If obstruction is active the timer will restart. If stop is active the timer
 * will reset, the stop light will be turned on and all orders will be deleted. 
 * @return 1 if the timers has passed three seconds, 0 otherwise.  
 */
int timer();

#endif
