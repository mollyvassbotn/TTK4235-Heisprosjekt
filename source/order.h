#ifndef ORDER_H
#define ORDER_H
#include "FSM.h"
#include "hardware.h"
#include <stdio.h>


//int g_orders[12] = {0};
int g_orders[12];
int g_current_floor;
int g_current_order;

void orders_init();

int check_if_order();

int order_same_floor(int floor);

void add_order();

int order_same_floor();

void delete_order(HardwareMovement type, int floor);

void delete_all_orders();

void try_elevator();

int get_order_floor();

void reset_lights();

void get_current_floor();

void delete_order_at_floor(int current_floor);

#endif

