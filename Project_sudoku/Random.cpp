#include "Random.h"
#include <chrono>

Random::Random(unsigned int t) {

}


Random::~Random() {

}



int Random::RandInt(int a, int b) {

	//srand((unsigned int)seed);

	if (b < a) {
		int temp = b;
		b = a;
		a = temp;
	}

	return (rand() % (b - a + 1)) + a;


}


float Random::RandFloat(int a, int b) {

	//srand((unsigned int)seed);

	if (b < a) {
		float temp = b;
		b = a;
		a = temp;
	}

	float f = (float)((float)rand() / (float)RAND_MAX);


	return f * (float)(b - a) + (float)a;


}


double Random::RandDouble(int a, int b) {

	//srand((unsigned int)seed);

	if (b < a) {
		double temp = b;
		b = a;
		a = temp;
	}

	double f = (double)((double)rand() / (double)RAND_MAX);


	return f * (double)(b - a) + (double)a;


}