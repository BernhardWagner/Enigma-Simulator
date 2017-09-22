#pragma once
#include <string>
#include "EncoderModule.h"
#include "Rotor.h"
#include "Reflector.h"
#include "Seeds.h"

class Enigma {
public:
	Enigma(int numRotors);
	~Enigma();
	// add a rotor of a specific type
	void addRotor(RotorType type);
	// exchange the rotor at position ’posIdx’
	void changeRotor(Rotor & rotor, int posIdx);
	// set the daily key settings
	void setDailyKey(char key[]);
	// set the message key settings
	void setMessageKey(char key[]);
	// clear daily and message key settings
	void reset();
	// encrypt the message key with the daily key settings
	// encrypt ’msg’ with the current daily and message key settings
	std::string encrypt(const std::string & msg);
	// decrypt the message with current daily and message key settings
	// (the message key is read at the beginning of the message)
	std::string decrypt(const std::string & msg);
	// apply the message key setting (set offset for each rotor)
	void applyMsgKey();
	// get the index of the char ’c’ (range: [A..Z,a..z])
	int toInt(char c);
	// get the corresponding char for the int ’i’ (range: [0..NUM_LETTERS[)
	char toChar(int i);
	char processChar(char letter);
private:
	int m_numRotors; // the number of rotors
	Rotor **m_rotors;// array of pointers to rotors
	Reflector m_reflector; // the reflector module
	char *m_msgKey;// the current msgKey
};