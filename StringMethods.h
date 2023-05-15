#pragma once
#include <string>
#include <vector>

void split(const std::string line, const char* seps, std::vector<std::string>& vec);

//erase chars from string
std::string erchrs(const std::string line, const char* outs);

std::string comclear(const std::string line, const char brack_in, const char brack_out);

