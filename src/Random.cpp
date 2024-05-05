#include "Random.h"

// Gets a random number between min (inclusive) and max (exclusive).
int random_range(int min, int max)
{
	// check for invalid cases
	if (min >= max)
	{
		return max;
	}

	return min + rand() % (max - min);
}

int random_range(int max)
{
	return rand() % max;
}

// returns -1 or 1
int random_sign()
{
	return (rand() % 2) * 2 - 1;
}

// initializes srand based on the current time
void random_init_time()
{
	time_t t;
	srand((unsigned)time(&t));
}

void random_init(const unsigned int seed)
{
	srand(seed);
}