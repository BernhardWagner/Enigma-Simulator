#include "EncoderModule.h"
#include <iostream>

//constructor
EncoderModule::EncoderModule(int randSeed) {
}

//standard consturctor (is never needed)
EncoderModule::EncoderModule() {
}

//destructor
EncoderModule::~EncoderModule() {
}

//gets the index of the m_configuration for an element (letter in int)
int EncoderModule::getIndex(int element) const {
	for (int i = 0; i < NUM_LETTERS; i++)			//searches in the array for the letter (numValue)
	{
		if (m_configuration[i] == element) {		//if the value was found it returns the index of the value
			return i;
		}
	}

	return -1;										//if the value was not found it returns -1
}

int EncoderModule::getCode(int idx) const {				
	if (idx < NUM_LETTERS) {						//searches with the index for the value to get the code
		return m_configuration[idx];
	}

	return -1;										//return -1 if code does not exist
}

void EncoderModule::print() const {					//prints m_configuration
	std::cout << "Module: " << std::endl;

	for (int i = 0; i < NUM_LETTERS; i++)				//iterates over the m_configuration array
	{
		std::cout << (char)(m_configuration[i] + 65);		//prints out the value as letter (+65 and to char to get the letter)
	}

	std::cout << std::endl;
}