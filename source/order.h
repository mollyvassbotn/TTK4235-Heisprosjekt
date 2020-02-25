/**
 * @file
 * @brief Deals with the orders.
 */


#ifndef ORDER_H
#define ORDER_H
#include "FSM.h"
#include "hardware.h"
#include <stdio.h>


int g_orders[12];
int g_current_floor;
int g_current_order;


/**
 * @brief Initializes the order array.
 */
void order_init();


/**
 * @brief Checks if there are any orders, and sets the current order.
 *
 * @return 0 on success, 1 if there are any orders.-> RETURNERER 0, VOID?
 */
int order_check_if_order();


/**
 * @brief Adds orders, and sets the order light.
 */
void order_add_order();


/**
 * @brief Checks if there are any more orders at the current floor.
 *
 * @param[in]  floor The current floor.
 *
 * @return 0 on success, 1 if there are any other orders at the floor.
 */
int order_same_floor(int floor);


/**
 * @brief Deletes all orders at the current floor, and turns the order lights off
 *
 * @param[in]  current_floor The current floor.
 */
void order_delete_order_at_floor(int current_floor);


/**
 * @brief Sets the destination floor based on current order
 *
 * @return destination floor ELLER 0,1,2,3??
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
 * @return g_current_floor The current floor.
 */
int order_get_current_floor();



#endif

