#pragma once

#include <vector>
#include <string>

#include "array.h"

template<class T>
struct Var {
	std::vector<Array<T>> time;
};

template<class T>
struct Memory {
	std::vector<Var<T>> data;
	struct {
		std::vector<std::string> code; // Brut code
		std::vector<int> fnlines; // line of each functions
		std::vector<int> argsid; // id of each tmpt args
		int main; // number of main func (to get line : fnlines[main])
	} code;
};

template<class T>
struct Model {
	std::vector<Memory<T>> levels;
	int relativ;
};