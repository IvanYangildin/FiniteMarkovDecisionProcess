#pragma once
#include <functional>
#include <vector>
#include <map>
#include <fstream>
#include "MathStuff.h"



namespace FMDP
{
	using namespace std;


	template<typename TState, typename TAction>
	class IEnviroment {
	public:
		virtual float Probability(const TState& state_new, float reward, const TState& state_old, const TAction& action) const = 0;

		virtual vector<TState> AllStates() const = 0;
		virtual vector<TAction> PossibleActions(const TState& state) const = 0;
		virtual vector<pair<TState, float>> PossibleOuts(const TState& state, const TAction& action) const = 0;

		virtual bool IsFinal(const TState& state) const = 0;
		virtual TAction ZeroAction() const = 0;

		pair<TState, float> Response(const TState& state_old, const TAction& action) const;
	};

	template<typename TState, typename TAction>
	class Actor {
	private:
		map<TState, float> v;
		const IEnviroment<TState, TAction>& enviroment;
		float gamma;
	public:
		Actor(const IEnviroment<TState, TAction>& enviroment, float gamma=1): enviroment(enviroment), gamma(gamma) {
			for (const auto& state : enviroment.AllStates())
			{
				v[state] = 0;
			}
		}

		float VFunction(const TState& state) const;
		float QFunction(const TState& state, const TAction& action) const;
		TAction Policy(const TState& state) const;

		void UpdateV();
		void Load(map<TState, float>);

		map<TState, float> GetData() const;
	};
};

// REALIZATION

template<typename TState, typename TAction>
std::pair<TState, float> FMDP::IEnviroment<TState, TAction>::Response(const TState& state_old, const TAction& action) const
{
	vector<pair<TState, float>> outs = PossibleOuts(state_old, action);

	if (outs.size() == 0) return pair<TState, float>(state_old, 0);

	float r = float_rand();
	float board = 0;
	for (size_t i = 0; i < outs.size() - 1; ++i)
	{
		board += Probability(outs[i].first, outs[i].second, state_old, action);
		if (r < board)
		{
			return outs[i];
		}
	}
	return outs[outs.size() - 1];
}


template<typename TState, typename TAction>
float FMDP::Actor<TState, TAction>::VFunction(const TState& state) const
{
	return v.at(state);
}

template<typename TState, typename TAction>
float FMDP::Actor<TState, TAction>::QFunction(const TState& state, const TAction& action) const
{
	float q = 0;
	for (auto p : enviroment.PossibleOuts(state, action))
	{
		q += (p.second + gamma * VFunction(p.first)) * enviroment.Probability(p.first, p.second, state, action);
	}
	return q;
}

template<typename TState, typename TAction>
TAction FMDP::Actor<TState, TAction>::Policy(const TState& state) const
{
	TAction policy_action = enviroment.ZeroAction();
	float max_q;
	bool is_first = true;
	for (auto a : enviroment.PossibleActions(state))
	{
		float q = QFunction(state, a);
		if (is_first)
		{
			max_q = q;
			policy_action = a;
			is_first = false;
		}
		else if (q > max_q)
		{
			max_q = q;
			policy_action = a;
		}
	}
	return policy_action;
}

template<typename TState, typename TAction>
void FMDP::Actor<TState, TAction>::UpdateV()
{
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		const TState& state = it->first;
		if (!enviroment.IsFinal(state))
			v.at(state) = QFunction(state, Policy(state));
	}
}

template<typename TState, typename TAction>
void FMDP::Actor<TState, TAction>::Load(map<TState, float> data)
{
	v = data;
}

template<typename TState, typename TAction>
std::map<TState, float> FMDP::Actor<TState, TAction>::GetData() const
{
	return v;
}