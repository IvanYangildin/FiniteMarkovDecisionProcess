#include "PlayIntSet.h"


void GameStep(IntSet& state, OrderedPair action)
{
	float r = float_rand();
	if (r < 0.5)
	{
		state = state.ActMinus(action);
	}
	else
	{
		state = state.ActPlus(action);
	}
}

void IntSetPlay(const FMDP::Actor<IntSet, OrderedPair>& player, const IntSetEnviroment& enviroment, IntSet state)
{
	using namespace FMDP;

	int count = 0;
	cout << "state: " << state.power_to_str() << endl;
	while (!enviroment.IsFinal(state))
	{
		OrderedPair action = player.Policy(state);
		cout << "action: " << action.Big() << " " << action.Small() << endl;

		GameStep(state, action);
		cout << "state: " << state.power_to_str() << endl;
		
		++count;
	}

	cout << "tries: " << count << endl;
}