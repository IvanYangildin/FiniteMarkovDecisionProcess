#pragma once
#include <vector>
#include <map>
#include <string>


class OrderedPair
{
private:
	// small <= big
	int small, big;
public:
	OrderedPair(int a, int b)
	{
		if (a <= b) {
			small = a;
			big = b;
		}
		else
		{
			small = b;
			big = a;
		}
	}

	int Small() const { return small; }
	int Big() const { return big; }
};

class IntSet
{
private:
	// power[i] shows how much integers i in set
	std::map<int, int> power;

	IntSet() = default;
public:
	// create IntSet from set of numbers;
	// "power" and "numbers" have different nature
	IntSet(const std::vector<int>& numbers);

	// create IntSet from map,
	// where key - is number in set,
	// value - count of this number
	IntSet(const std::map<int, int>& pover);

	// return set of N ones
	static IntSet SetOfOnes(size_t N);

	// return biggest number i nset
	int biggest() const;

	// return sum of elements
	int sum() const;

	// return difference between biggest number and sum of otehr elements
	int diff() const;

	// remove a and b from set and add |a-b| instead 
	IntSet ActMinus(const OrderedPair& act) const;

	// remove a and b from set and add a+b instead 
	IntSet ActPlus(const OrderedPair& act) const;

	std::vector<OrderedPair> PossibleActions() const;

	bool operator==(const IntSet&) const;

	bool operator<(const IntSet&) const;

	// return count of numbers in IntSet
	int num_count() const;

	std::string power_to_str() const;
};