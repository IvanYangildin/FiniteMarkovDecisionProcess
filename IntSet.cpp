#include "IntSet.h"


IntSet::IntSet(const std::vector<int>& numbers)
{
	for (int num : numbers)
	{
		if (power.count(num) == 0) power[num] = 0;
		power[num] += 1;
	}
}

IntSet::IntSet(const std::map<int, int>& power) : power(power)
{
}

IntSet IntSet::SetOfOnes(size_t N)
{
	IntSet is;
	is.power[1] = N;
	return is;
}

int IntSet::biggest() const
{
	return power.crbegin()->first;
}

int IntSet::sum() const
{
	int s = 0;
	for (auto it = power.cbegin(); it != power.cend(); ++it)
	{
		s += it->first * it->second;
	}
	return s;
}

int IntSet::diff() const
{
	return 2 * biggest() - sum();
}

IntSet IntSet::ActMinus(const OrderedPair& act) const
{
	IntSet int_set(*this);
	int a = act.Big();
	int b = act.Small();
	
	int c = a - b;
	if (c > 0) int_set.power[c] += 1;
	
	int_set.power[a] -= 1;
	int_set.power[b] -= 1;
	if (int_set.power[a] <= 0) int_set.power.erase(a);
	if (int_set.power[b] <= 0) int_set.power.erase(b);

	return int_set;
}

IntSet IntSet::ActPlus(const OrderedPair& act) const
{
	IntSet int_set(*this);
	int a = act.Big();
	int b = act.Small();

	int c = a + b;
	int_set.power[c] += 1;

	int_set.power[a] -= 1;
	int_set.power[b] -= 1;
	if (int_set.power[a] <= 0) int_set.power.erase(a);
	if (int_set.power[b] <= 0) int_set.power.erase(b);

	return int_set;
}

std::vector<OrderedPair> IntSet::PossibleActions() const
{
	std::vector<OrderedPair> actions;

	for (auto it = power.cbegin(); it != power.cend(); ++it)
	{
		int a = it->first;
		if (it->second >= 2) actions.push_back(OrderedPair(a, a));
		for (auto jt = std::next(it, 1); jt != power.cend(); ++jt)
		{
			int b = jt->first;
			actions.push_back(OrderedPair(a, b));
		}
	}

	return actions;
}

bool IntSet::operator==(const IntSet& other) const
{
	for (auto it = power.cbegin(); it != power.cend(); ++it)
	{
		if (other.power.count(it->first) <= 0) return false;
		if (other.power.at(it->first) != it->second) return false;
	}
	return true;
}

bool IntSet::operator<(const IntSet& other) const
{
	auto it = power.cbegin();
	auto jt = other.power.cbegin();

	while ((it != power.cend()) && (jt != other.power.cend()))
	{
		if (it->first == jt->first)
		{
			if (it->second == jt->second)
			{
				++it;
				++jt;
			}
			else
			{
				return it->second < jt->second;
			}
		}
		else
		{
			return it->first < jt->first;
		}
	}
	
	return (it == power.cend()) && (jt != other.power.cend());
}

int IntSet::num_count() const
{
	int count = 0;
	for (auto p : power)
	{
		count += p.second;
	}
	return count;
}

std::string IntSet::power_to_str() const
{
	std::string s = "";
	std::string sep = "";
	for (auto it = power.cbegin(); it != power.cend(); ++it)
	{
		s += sep + std::to_string(it->first) + "*" + std::to_string(it->second);
		sep = ",";
	}
	return s;
}