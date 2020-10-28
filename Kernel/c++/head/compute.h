#pragma once

#include "data.h"

#include <vector>
#include <string>

template<class T> int _exec(Memory<T>*, int, int, int, bool);
template<class T> void compute(Memory<T>*, int, bool);

#include "../cpp/compute.cpp"