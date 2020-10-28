#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "data.h"

//Read file -> string
std::string read_file(std::string);
//Spliting
std::vector<std::string> split(std::string, char);
std::string replace(std::string, std::string, std::string);
//Divise with [theme] in {themes, contents}
std::vector<std::vector<std::string>> div_text(std::string);
//
int find(std::string, std::string);
template<class T> int in(T elm, std::vector<T> patern);
//
template<class T> std::vector<int> sizes(Var<T>*);
template<class T> std::vector<int> lengths(Var<T>*);
int max_length(std::vector<std::string>);
//ptr funcs
template<class T> void ptr_arr(Array<T>*);
template<class T> void ptr_var(Var<T>*);
template<class T> void ptr_mem(Memory<T>*);
template<class T> void ptr_mdl(Model<T>*);

#include "../cpp/tools.cpp"