//
// Created by User1 on 12-Oct-25.
//
#pragma once
#ifndef LONGARFINT_H
#define LONGARFINT_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



typedef struct digit {
    short exp;
    short content;
    struct digit *next;
    struct digit *prev;
} digit;

typedef struct {
    digit *head;
    digit *tail;
    short sign;
} long_int;

//Create a new node in long_int
digit *new_digit(short content, short exp);
//Initialise a new long_int
void init_long_int(long_int *number);
//Add a new node at the end of long_int
void* app_end_digit(long_int *number, short content, short exp);
//Add a new node at the beginning of long_int
void* add_strt_digit(long_int *number, short content, short exp);
//Read long_int from consol
long_int read_long_int();
//Creates a new long_int containing the sum of 2 long_int
long_int summ_long_int(long_int *number_1, long_int *number_2);
//Creates a new long_int containing the product of 2 long_int
long_int mult_long_int(long_int *number_1, long_int *number_2);
long_int mult_long_int_test(long_int *number_1, long_int *number_2);

//Creates a new long_int containing the long_int raised to an int power
long_int power_long_int(long_int *base, int exponent);
//Clear data in long_int
void clear_long_int(long_int *number);
//Print long_int in consol
void* print_long_int(long_int *number);
//Copy long_int in other long_int
long_int copy_long_int(long_int *orig);

int check_validness(long_int *number);

#endif //LONGARFINT_H