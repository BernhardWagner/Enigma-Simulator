// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Input.h"
#include <cstdlib>
//main program


void enigmaSimulator() {
	printHeadline();							//prints the headline and asks if we want to quit the program or not
	int numRotors = getNumberOfRotors();		//asks for the number of rotors in the machine and saves them in numRotors
	Enigma* enigma = new Enigma(numRotors);		//creates a new enigma machine with numRotors empty rotor spaces

	bool* isSetRotor = new bool[numRotors];		//creates a isSetRotor helping array that saves the data if a rotor is already set on a specific way
	int* rotorTypes = new int[numRotors];		//also an array that saves the rotor types

	for (int i = 0; i < numRotors; i++)			//sets every value in isSetRotor to false (no rotor set)
	{
		isSetRotor[i] = false;
	}
	system("cls");								//clears the screen

	for (int i = 0; i < numRotors; i++)			//for every empty space in the machine we ask for a rotor
	{
		if (!isSetRotor[i]) {					//if there is no rotor already set (is always the case...but to make sure)
			printRotorTypes();					//prints the rotor types that we have (unfortunately hardcoded because i have no f. idea how enums work)
			printEnigmaMachine(numRotors, isSetRotor, rotorTypes);	//prints the enigma machine with the current setting
			rotorTypes[i] = askRotorType(i);						//asks for a rotor type that should be added in the machine
			isSetRotor[i] = true;									//sets the rotor place to true (not empty)
			enigma->addRotor(getRotorType(rotorTypes[i]));			//adds the rotor to the enigma machine
			system("cls");											//clears the screen
		}
	}
	printEnigmaMachine(numRotors, isSetRotor, rotorTypes);			//prints again the enigma machine with the current setting
	bool change = askToChangeRotor();								//asks if everything is alright

	while (change) {												//while not everthing is alright
		int place = askWhatToChange(numRotors);						//we ask the user which rotor (on which place) he wants to change
		rotorTypes[place] = askRotorType(place);					//then we ask the user which rotor type he wants for this place instead
		system("cls");												//screen clearing
		enigma->changeRotor(Rotor(getRotorType(rotorTypes[place])), place);  //now we change the rotor on the specific place with the specific type
		printEnigmaMachine(numRotors, isSetRotor, rotorTypes);				//again we print the machine
		change = askToChangeRotor();										//again we ask the user if the settings is now alright (if not everything begins again)
	}

	system("cls");												//clears the screen (again)
	printEnigmaMachine(numRotors, isSetRotor, rotorTypes);		//prints the enigma machine again with the current setting
	char* daylyKey = askDaylyKey(numRotors);					//now we can ask for the dayly key
	enigma->setDailyKey(daylyKey);								//and we can set the dayly key

	bool decode = askIfDecode();								//now we ask the user if he wants to encode or decode
	std::string msg = askForMsg(numRotors, decode);				//then we ask the user which message (incl msg key) he wants to de or encode
	system("cls");												//clears the screen
	printEnigmaMachine(numRotors, isSetRotor, rotorTypes);		//prints again the rotor machine
	//encodes or decodes the message depending on the chosen settings and prints the result on the screen
	std::cout << "Your " << ((decode) ? "decoded" : "encoded") << " message (incl message key):" << std::endl << "" << ((decode) ? enigma->decrypt(msg) : enigma->encrypt(msg)) << "" << std::endl;

	//Test if encrypt and decrypt are working properly
	//  msg = enigma->encrypt(msg);
	//	std::cout << "encrpted = " << msg << std::endl;
	//	enigma->reset();
	//	msg = enigma->encrypt(msg);
	//	std::cout << "encrpted = " << msg << std::endl;
	//	enigma->setDailyKey(daylyKey);
	//	std::cout << "decryptd = " << enigma->decrypt(msg) << std::endl;

	//now we have everything intialized and made the first encode or decode...we can start the main loop (where we only can escape when we enter q)
	mainLoop(enigma, numRotors, isSetRotor, rotorTypes, daylyKey);
}


int main()
{	//starts the enigma simulator
	enigmaSimulator();
	//should never reach getchar
	getchar();
	getchar();
    return 0;
}

