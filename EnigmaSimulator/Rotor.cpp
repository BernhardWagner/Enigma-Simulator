#include "Rotor.h"
#include <algorithm>

Rotor::Rotor(int seed) : EncoderModule(seed){
	this->seed = seed;		//saves the seed
	init();					//initializes the Rotor (genereates a random m_config array)
}

//destructor
Rotor::~Rotor() {
}

void Rotor::init() {
	srand(seed);								 //sets the seed for the random function
	for (int i = 0; i < NUM_LETTERS; i++)
	{
		m_configuration[i] = i;					//generates a normal array (from 0 to 25)
	}
	
	//shuffles the array (i was too lazy to write a shuffle algorithm myself)
	std::random_shuffle(&m_configuration[0], &m_configuration[NUM_LETTERS - 1]);

	setting = 0;							//initialize setting to null, the setting determines the rotation position of the rotor
}

int Rotor::turnRotor() {
	if (m_configuration != nullptr) {						//checka if m_configuration isset
		int last = m_configuration[NUM_LETTERS - 1];		//saves the last data of the array
		for (int i = NUM_LETTERS - 1; i > 0; i--)			//counts down from the last data in the array to the second first
		{
			m_configuration[i] = m_configuration[i - 1];	//now the data should be the previous data	
		}

		m_configuration[0] = last;							//set the first data to the last (last jumps one step forward)
	}
	
	setting += 1;	
										//for every rotation the setting will count up

	if (setting == 26) {				//if the setting reaches 26 (end of the array) then we have one full rotation and we can reset the setting to null
		setting = 0;
		return 1;						//returns one if we made a full rotation (important to calibrate the next rotors)
	}

	return 0;							//returns 0 if we didnt make a full rotation
}

int Rotor::getSetting() {				//returns the setting we currently have for the rotation (for debugging purpose)
	return setting;
}

void Rotor::setRotor(int newSetting) {	//sets the new rotor to a new setting
	while (setting != newSetting) {		//rotates the rotor as long as we reach the right setting
		turnRotor();
	}
}

void Rotor::reset() {			//resets the rotor to the start position
	setRotor(0);				//calls setRotor with the setting 0 (start position)
}