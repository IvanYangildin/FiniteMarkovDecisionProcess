#include "parse.h"
#include <map>
#include <vector>
#include "StringMethods.h"


template<>
std::map<int, int> parse(std::string line)
{
	using namespace std;
	vector<string> sub_lines;
	line = erchrs(line, " ");
	split(line, ",", sub_lines);

	map<int, int> res;
	for (auto sub_line : sub_lines)
	{
		vector<string> p;
		split(sub_line, "*", p);
		if (p.size() != 2)
		{
			throw std::exception("exception: wrong line format to parse to map<int, int>!");
		}
		int key = stoi(p[0]);
		int value = stoi(p[1]);
		res[key] = value;
	}

	return res;
}

template<>
std::pair<std::map<int, int>, float> parse(std::string line)
{
	using namespace std;

	vector<string> sub_lines;
	line = erchrs(line, " ");
	split(line, ":", sub_lines);

	if (sub_lines.size() != 2)
	{
		throw std::exception("exception: wrong line format to parse to pair<map<int, int>, float>!");
	}
	pair<map<int, int>, float> res;
	res.first = parse<map<int, int>>(sub_lines[0]);
	res.second = stof(sub_lines[1]);

	return res;
}

template<>
std::vector<std::pair<std::map<int, int>, float>> parse(std::ifstream& input)
{
	using namespace std;
	vector<pair<map<int, int>, float>> vec;

	string line;
	while (getline(input, line))
	{ 
		vec.push_back(parse< pair<map<int, int>, float>>(line));
	}

	return vec;
}
