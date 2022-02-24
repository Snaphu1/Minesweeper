#include "Random.h"
#include <ctime>
//static variables must be redeclared in global space 
std::mt19937 Random::random(time(0));
int Random::Int(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
int Random::Float(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
// for float , its the same thing but replace int with float
// to call it in code do Random::Number(0,window.getSize())