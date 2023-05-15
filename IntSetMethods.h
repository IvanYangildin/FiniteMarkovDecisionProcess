#pragma once
#include "IntSet.h"

std::vector<IntSet> AllIntSets(int max_sum);

std::ofstream& operator<<(std::ofstream& out, const std::map<IntSet, float>&);