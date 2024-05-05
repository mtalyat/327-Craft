#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// gets a random number between min (inclusive) and max (exclusive).
int random_range(int min, int max);

// gets a random number between 0 (inclusive) and max (exclusive).
int random_range(int max);

// returns -1 or 1
int random_sign();

// initializes srand based on the current time
void random_init_time();

// initializes srand based on the given seed
void random_init(const unsigned int seed);

#endif