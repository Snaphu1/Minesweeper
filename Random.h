//Random number generator 
#pragma once
#include <random>
class Random {
	//one instance of the x variable 
	//static int x; 
	static std::mt19937 random;
public:
	//One and only one of this function
	static int Int(int min, int max);
	static int Float(int min, int max);
};
// int value = Random::x; <- this is how we access the x value. We can't change it