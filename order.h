#ifndef ORDER_H
#define ORDER_H
#include "FSM.h"

int check_if_order();

void add_order(HardwareOrder type, int floor);

void place_order();

int order_same_floor();

void delete_order(HardwareMovement type, int floor);

void delete_all_orders();
#endif