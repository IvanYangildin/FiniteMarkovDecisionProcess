#include "StringMethods.h"

void split(const std::string line, const char* seps, std::vector<std::string>& vec)
{
	std::string buff = "";
	for (size_t k = 0; k < line.size(); k++)
	{
		if (std::strchr(seps, line[k]))
		{
			vec.push_back(std::string(buff));
			buff.clear();
		}
		else
			buff += line[k];
	}
	if (!buff.empty())
		vec.push_back(std::string(buff));
}

std::string erchrs(const std::string line, const char* outs)
{
	std::string buff = "";
	for (size_t k = 0; k < line.size(); k++)
	{
		if (!std::strchr(outs, line[k]))
			buff += line[k];
	}
	return buff;
}

std::string comclear(const std::string line, const char brack_in, const char brack_out)
{
	std::string buff = "";
	bool is_comment = false;
	for (size_t k = 0; k < line.size(); k++)
	{
		if (line[k] == brack_in)
			is_comment = true;
		
		if (!is_comment)
			buff += line[k];

		if (line[k] == brack_out)
			is_comment = false;
	}
	return buff;
}