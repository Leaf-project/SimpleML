#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "globals.h"

template<class T> T add(T, T);
template<class T> T sub(T, T);
template<class T> T mul(T, T);
template<class T> T div(T, T);
template<class T> T _pow(T, T);

template<class T> T add_lst(std::vector<T>);
template<class T> T sub_lst(std::vector<T>);
template<class T> T mul_lst(std::vector<T>);
template<class T> T div_lst(std::vector<T>);
template<class T> T pow_lst(std::vector<T>);

// Header view of Array
template <class T>
class Array {
private:
	std::vector<T> data;
	std::vector<int> real_sizes; //Size of each 'deep'
	void compute_real_sizes();
	int get_real_pos(std::vector<int>);
	//Operator function
	Array<T> lin_ope(Array<T>*, T(*)(T,T));
	//Set b to this
	void set_eq(Array<T>);
	//
	void update_str();
public:
	//Semi-const datas
	int deep;
	std::vector<int> shape;
	int length;
	//Debbug function
	std::vector<std::string> list_str; //static ptr
	//Controle functions
	void set(int, T);
	void insert(int, T);
	void push_back(T);
	void set_data(std::vector<T>);
	T& operator[](std::vector<int>);
	T& get(std::vector<int>);
	T& get_data(int); // return data[i]
	//Magic functions
	Array<T> operator+(const Array<T>&);
	Array<T> operator-(const Array<T>&);
	Array<T> operator*(const Array<T>&);
	Array<T> operator/(const Array<T>&);
	Array<T> operator^(const Array<T>&);
	void operator=(const Array<T>&);
	void operator+=(const Array<T>&);
	void operator-=(const Array<T>&);
	void operator*=(const Array<T>&);
	void operator/=(const Array<T>&);
	void operator^=(const Array<T>&);
	//Special operations
	Array<T> dot(Array<T>*);
	//Char operation
	void operation_char(Array<T>*, char);
	//Init
	Array<T> (std::vector<T>, std::vector<int>);
};

#include "../cpp/array.cpp"