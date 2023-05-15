#include <iostream>
#include "ModelFMDP.h"
#include "PathProblem.h"
#include "IntSetProblem.h"
#include "PlayIntSet.h"
#include "parse.h"


void main_path()
{
	using namespace FMDP;

	size_t width = 12, height = 5;
	PathEnviroment enviroment(width, height);
	Actor< Cell, Arrow> actor(enviroment);

	for (size_t k = 0; k < 15; ++k)
		actor.UpdateV();

	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			cout << actor.VFunction({ int(j), int(i) }) << " ";
		}
		cout << endl;
	}


	for (size_t i = 0; i < height; ++i)
	{
		for (size_t j = 0; j < width; ++j)
		{
			cout << actor.Policy({ int(j), int(i) }) << " ";
		}
		cout << endl;
	}

}

int main()
{
	using namespace FMDP;
	srand(time(0));

	size_t max_sum = 30;
	IntSetEnviroment enviroment(max_sum);
	Actor<IntSet, OrderedPair> actor(enviroment);

	ifstream in("actor_data.txt");
	vector<pair<map<int, int>, float>> vec = parse< vector<pair<map<int, int>, float>>>(in);
	map<IntSet, float> actor_values;
	for (auto p : vec)
	{
		actor_values[IntSet(p.first)] = p.second;
	}
	actor.Load(actor_values);

	//for (int k = 0; k < 50; ++k)
	//	actor.UpdateV();

	IntSetPlay(actor, enviroment, IntSet::SetOfOnes(max_sum));

	//for (auto state : enviroment.AllStates())
	//{
	//	if (state.num_count() == 4)
	//	{
	//		cout << "state: " << state.power_to_str() << endl;
	//		cout << "action: " << actor.Policy(state).Big() << " " << actor.Policy(state).Small() << endl;
	//		cout << endl;
	//	}
	//}

	return 0;
}