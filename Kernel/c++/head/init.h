#pragma once

#include <vector>
#include <string>

#include "data.h"
#include "tools.h"

//Del comments
std::string del_com(std::string);
//from file
template<class T> Memory<T> load_mem(std::string);
//convert 3.0,4.1,51.31,-4.0 to array<T>{3.0, 4.1...}
template<class T> std::vector<T> str_to_list(std::string);
//open init file
template<class T> void init_mem(Memory<T>*, std::string, bool);
//Load Model from file [not json]
template<class T> Model<T> load_model(std::string, std::string);
//Add 1-scale number
template<class T> void add_number(Memory<T>*, T);
//
template<class T> void add_arr(Memory<T>*, std::vector<T>);

#include "../cpp/init.cpp"