#include "IntSetMethods.h"
#include <fstream>

bool is_finish(const std::map<int, int>& power, int max_sum)
{
	return power.cbegin()->first >= max_sum;
}

void next_iter(std::map<int, int>& power, int& sum, int max_sum)
{
	if (is_finish(power, max_sum)) return;

	if (power.count(1) == 0) power[1] = 0;
	power[1] += 1;
	sum += 1;

	while (true)
	{
		int small = power.begin()->first;
		if (sum > max_sum)
		{
			sum -= small * power.at(small);
			power.erase(small);
			if (power.count(small + 1) == 0)
			{
				power[small + 1] = 0;
			}
			power[small + 1] += 1;
			sum += small + 1;
		}
		else break;
	}
}

std::vector<IntSet> AllIntSets(int max_sum)
{
	std::map<int, int> power;
	power[1] = 1;
	int sum = 1;

	std::vector<IntSet> isets;
	isets.push_back(IntSet(power));
	while (!is_finish(power, max_sum))
	{ 
		next_iter(power, sum, max_sum);
		isets.push_back(IntSet(power));
	}

	return isets;
}

//////

std::ofstream& operator<<(std::ofstream& out, const std::map<IntSet, float>& data)
{
	for (auto info : data)
	{
		out << info.first.power_to_str() << ":" << info.second << std::endl;
	}
	return out;
}