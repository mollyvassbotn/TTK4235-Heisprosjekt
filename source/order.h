#ifndef ORDER_H
#define ORDER_H
#include "FSM.h"
#include "hardware.h"
#include <stdio.h>


int check_if_order();

void add_order();

int order_same_floor();

void delete_order(HardwareMovement type, int floor);

void delete_all_orders();

void try_elevator();

void queue_system();


void reset_lights();

#endif

