#pragma once
#include "ModelFMDP.h"


enum Arrow { arr_left, arr_up, arr_right, arr_down, arr_noone };

struct Cell
{
	int x, y;
	Cell Next(const Arrow& arrow) const
	{
		switch (arrow)
		{
		case arr_left:
			return { x - 1, y };
		case arr_right:
			return { x + 1, y };
		case arr_up:
			return { x, y + 1 };
		case arr_down:
			return { x, y - 1 };
		default:
			break;
		}
		return *this;
	}
};

inline bool operator<(const Cell& a, const Cell& b)
{
	if (a.y < b.y) return true;
	if (a.y == b.y) return a.x < b.x;
	return false;
}

inline bool operator==(const Cell& a, const Cell& b)
{
	return (a.x == b.x) && (a.y == b.y);
}


class PathEnviroment : public FMDP::IEnviroment<Cell, Arrow>
{
private:
	size_t width, height;
public:
	PathEnviroment(size_t width, size_t height): width(width), height(height)
	{ }

	float Probability(const Cell& state_new, float reward, const Cell& state_old, const Arrow& action) const
	{
		if (IsFinal(state_old) && (reward < 0)) return 0.0f;

		if (state_new == state_old.Next(action))
		{
			return 1.0f;
		}

		return 0.f;
	}

	std::vector<Cell> AllStates() const
	{
		std::vector<Cell> cells;
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				cells.push_back({ j,i });
			}
		}
		return cells;
	}

	bool IsFinal(const Cell& cell) const
	{
		return (cell.x == width - 1) && (cell.y == height - 1);
	}


	Arrow ZeroAction() const
	{
		return arr_noone;
	}

	std::vector<Arrow> PossibleActions(const Cell& state) const
	{
		std::vector<Arrow> actions;

		if (IsFinal(state)) return actions;

		if (state.x > 0) actions.push_back(arr_left);
		if (state.x < width - 1) actions.push_back(arr_right);
		if (state.y > 0) actions.push_back(arr_down);
		if (state.y < height - 1) actions.push_back(arr_up);

		return actions;
	}

	std::vector<std::pair<Cell, float>> PossibleOuts(const Cell& state, const Arrow& action) const
	{
		std::vector<std::pair<Cell, float>> outs;
		if (IsFinal(state))
			return outs;

		Cell cell = state.Next(action);
		outs.push_back(std::pair<Cell, float>(cell, -1));

		return outs;
	}
};