#pragma once
#include <iostream>
#include <time.h>
#include <random>

using namespace std;


class Random {

public:

	Random(unsigned int t);
	~Random();
	
	int RandInt(int a, int b);
	double RandDouble(int a, int b);
	float RandFloat(int a, int b);


};
