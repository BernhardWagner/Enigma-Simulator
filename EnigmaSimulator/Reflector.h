#pragma once

#include <iostream>
#include "Rotor.h"
class Reflector: public EncoderModule {
public:
	Reflector();
	Reflector(int randSeed);
	~Reflector();
	void init();

private:
	int seed;
};