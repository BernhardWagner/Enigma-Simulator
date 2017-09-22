#pragma once

#ifndef __Enigma__Rotor__
#define __Enigma__Rotor__

#include <iostream>
#include <string>
#include <vector>
#include "EncoderModule.h"

class Rotor : public EncoderModule {

public:
	static const int NUM_LETTERS = 26;
	Rotor(int randSeed);
	~Rotor();
	int turnRotor();
	int getSetting();
	void setRotor(int newSetting);
	void init();
	void reset();
private:
	//position of rotation of wheel
	int setting;
	int seed;
};

#endif /* defined(__Enigma__Rotor__) */