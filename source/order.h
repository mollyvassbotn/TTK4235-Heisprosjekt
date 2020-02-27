/**
 * @file
 * @brief Deals with the orders.
 */


#ifndef ORDER_H
#define ORDER_H
#include "hardware.h"
#include <stdio.h>

#define N_ORDERS 12

/**
 * @brief An array where all the orders from the elevator is stored. 
 */
int g_orders[N_ORDERS];

/**
 * @brief Cointains which floor the elevator is currently at.
 */
int g_current_floor;

/**
 * @brief Contains the order the elevator will execute. 
 */
int g_current_order;


/**
 * @brief Initializes the order array.
 */
void order_init();


/**
 * @brief Checks if there are any orders, and sets the current order.
 *
 * @return 1 if there are any orders, 0 otherwise. 
 */
int order_check_if_order();


/**
 * @brief Adds new orders, and sets the order lights.
 */
void order_add_order();


/**
 * @brief Checks if there are any more orders at the current floor.
 *
 * @param[in]  floor The floor the elevator is currently at.
 *
 * @return 1 if it is any more orders at the current floor, otherwise 0. 
 */
int order_same_floor(int current_floor);


/**
 * @brief Deletes all orders at the current floor, and turns the order lights off
 *
 * @param[in]  current_floor The floor the elevator is currently at.
 */
void order_delete_order_at_floor(int current_floor);


/**
 * @brief Calculates the destination floor for the current order.  
 *
 * @return The floor the current order is at. 
 */
int order_get_order_floor();


/**
 * @brief Deletes all orders, and resets the order lights.
 */
void order_delete_all_orders();

/**
 * @brief Resets the order lights.
 */
void order_reset_lights();


/**
 * @brief Sets the current floor based on the hardware sensors.
 *
 * @return g_current_floor The floor the elevator is currently at. 
 */
int order_get_current_floor();



#endif