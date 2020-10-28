#pragma once

#include <string>

std::string debbug = "\033[0m[\033[2mDebbug\033[0m] ";
std::string computing = "\033[0m[\033[2mComputing\033[0m] ";

std::vector<char> operators = {'#', ':', ')', '|', '+', '-', '/', '*', '^', '='};

template<class T> T max(std::vector<T> l) {
	T max = l[0];
	for (T elm : l) if (elm > max) max = elm;
	return max;
};