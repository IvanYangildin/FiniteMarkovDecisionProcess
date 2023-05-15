#pragma once
#include <iostream>
#include <fstream>
#include <string>

template<typename T>
T parse(std::string);

template<typename T>
T parse(std::ifstream& input);
