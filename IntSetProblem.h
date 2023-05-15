#pragma once
#include "ModelFMDP.h"
#include "IntSet.h"
#include "IntSetMethods.h"


class IntSetEnviroment : public FMDP::IEnviroment<IntSet, OrderedPair>
{
private:
	int max_num;
public:
	IntSetEnviroment(int max_num): max_num(max_num) {}

	float Probability(const IntSet& state_new, float reward, const IntSet& state_old, const OrderedPair& action) const
	{
		IntSet positive = state_old.ActPlus(action);
		IntSet negative = state_old.ActMinus(action);
		if ((negative == state_new) || (positive == state_new))
		{
			if (IsFinal(state_new)? (reward == 0.) : (reward == -1.))
			return 0.5;
		}

		return 0.0;
	}

	std::vector<IntSet> AllStates() const
	{
		return AllIntSets(max_num);
	}

	std::vector<OrderedPair> PossibleActions(const IntSet& state) const
	{
		return state.PossibleActions();
	}

	std::vector<std::pair<IntSet, float>> PossibleOuts(const IntSet& state, const OrderedPair& action) const
	{
		IntSet positive = state.ActPlus(action);
		IntSet negative = state.ActMinus(action);
		std::vector<std::pair<IntSet, float>> outs;
		outs.push_back(std::pair<IntSet, float>(positive, IsFinal(positive) ? 0. : -1.));
		outs.push_back(std::pair<IntSet, float>(negative, IsFinal(negative) ? 0. : -1.));
		return outs;
	}


	bool IsFinal(const IntSet& state) const
	{
		return state.diff() >= 0;
	}

	OrderedPair ZeroAction() const
	{
		return OrderedPair(0, 0);
	}

};