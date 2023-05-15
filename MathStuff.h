#pragma once
#include <random>


inline float float_rand()
{
	return rand() / float(RAND_MAX);
}