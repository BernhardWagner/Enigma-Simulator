#include <iostream>
#include "stdafx.h"
#include "Input.h"
#include "Enigma.h"

//headline printing
void printHeadline() {
	//patorjk.com/software/taag/  -> ascii art generator
	std::cout << " _______ .__   __.  __    _______ .___  ___.     ___      " << std::endl <<
		"|   ____||  \\ |  | |  |  /  _____||   \\/   |    /   \\     " << std::endl <<
		"|  |__   |   \\|  | |  | |  |  __  |  \\  /  |   /  ^  \\    " << std::endl <<
		"|   __|  |  . `  | |  | |  | |_ | |  |\\/|  |  /  /_\\  \\   " << std::endl <<
		"|  |____ |  |\\   | |  | |  |__| | |  |  |  | /  _____  \\  " << std::endl <<
		"|_______||__| \\__| |__|  \\______| |__|  |__|/__/     \\__\\ " << std::endl << std::endl <<
		"____________________________________________________________________________________________________________________" << std::endl <<
		"|**Welcome to the Enigma Machine! If you want to close the application enter q, else press any other key         **|" << std::endl <<
		"|**           and follow the instructions. First of all you need to set up your Enigma-Machine!                  **|" << std::endl <<
		"____________________________________________________________________________________________________________________" << std::endl;
	char c = getchar();			//if we want to quit the program (for example we accidentally started it) we can enter q
	if (c == 'q') {
		std::exit(EXIT_SUCCESS);
	}
	if (c != '\n') {															//else we step to the next step
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	

}

//prints the enigma machine with the (current) setting
void printEnigmaMachine(int numRotors, bool* isSetRotor, int* rotorTypes) {
	//nothing special here just some ascii magic
	std::cout << "Machine:" << std::endl;
	std::cout << "##";
	for (int i = 0; i < numRotors; i++)
	{
		std::cout << "#####";
	}

	std::cout << "#######" << std::endl;

	char rotorType = 30;
	char text1[] = { ' ','R','O','T','O','R',' ',' ',' ' };
	char text2[] = { 'R','E','F','L','E','C','T','O','R' };
	char text3[] = { ' ',' ', 'E','M','P','T','Y',' ',' ' };

	for (int j = 0; j < 9; j++)
	{
		std::cout << "#  ";
		for (int k = 0; k < numRotors; k++)
		{
			if (isSetRotor[k]) {
				rotorType = rotorTypes[k];
				text1[7] = (char)(rotorType + 48);				//to get the rotor type
				std::cout << "|" << text1[j] << "|  ";
			}
			else {
				std::cout << "*" << text3[j] << "*  ";;
			}
		}
		std::cout << "|" << text2[j] << "|  #" << std::endl;
	}

	std::cout << "##";
	for (int i = 0; i < numRotors; i++)
	{
		std::cout << "#####";
	}

	std::cout << "#######" << std::endl;
	std::cout << "Number of Rotors: " << numRotors << std::endl << std::endl;
}

//asks for the number of rotors
int getNumberOfRotors() {
	int result;																	//sets up a variable for the input result

	std::cout << "How many rotors do you want in your Enigma-Machine (maximum is 10)?" << std::endl;		//prints the question
	std::cin >> result;																						//gets the input

	while (std::cin.fail() || result < 0 || result > 10) {													//checks if the result was right (and if not asks the user again for input)
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();																					//clears the input stream
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');									//ignores the remaining input stream in the line
		std::cin >> result;
	}

	return result;																					//returns the chekced input
}

int askRotorType(int i) {
	int resultInt;									//sets up a variable for the input result

	std::cout << "Which rotor-type do you want for the rotor on the " << i + 1 << ". place (insert a number)?" << std::endl;  //prints the question
	std::cin >> resultInt;

	while (std::cin.fail() || resultInt > 5 || resultInt < 1) {						//checks if the result was right (and if not asks the user again for input)
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();															//clears the input stream
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			//ignores the remaining input stream in the line
		std::cin >> resultInt;
	}

	std::cout << std::endl;

	return resultInt;																//returns the checked input
}

void printRotorTypes() {
	//i know its hardcoded
	std::cout << "##Rotor Types:################" << std::endl;
	std::cout << "#   1----Type I              #" << std::endl;
	std::cout << "#   2----Type II             #" << std::endl;
	std::cout << "#   3----Type III            #" << std::endl;
	std::cout << "#   4----Type IV             #" << std::endl;
	std::cout << "#   5----Type V              #" << std::endl;
	std::cout << "##############################" << std::endl << std::endl;

}

//exchanges the input of above to the rotor types that will be returned
RotorType getRotorType(int resultInt) {
	RotorType result = ROTOR_TYPE_I;

	switch (resultInt)
	{
	case 1:
		result = ROTOR_TYPE_I;
		break;
	case 2:
		result = ROTOR_TYPE_II;
		break;
	case 3:
		result = ROTOR_TYPE_III;
		break;
	case 4:
		result = ROTOR_TYPE_IV;
		break;
	case 5:
		result = ROTOR_TYPE_V;
		break;
	default:
		return ROTOR_TYPE_I;			//default is rotor type one if a rotor type was not found
		break;
	}

	return result;
}

//procedure is always the same and will not be explained further
//asks if we want to change a rotor
bool askToChangeRotor() {
	char decisionChar;
	std::cout << "Is the machine set up right? (press y or n)?" << std::endl;
	std::cin >> decisionChar;

	while (std::cin.fail() || decisionChar != 'n' && decisionChar != 'y') {
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> decisionChar;
	}

	std::cout << std::endl;

	return (decisionChar == 'n') ? true : false;
}

//what we want to change
int  askWhatToChange(int numRotors) {
	int result;
	std::cout << "On which place do you want to exchange the Rotor? (left to right)" << std::endl;
	std::cin >> result;

	while (std::cin.fail() || result > numRotors || result < 0) {
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> result;
	}
	std::cout << std::endl;

	return result - 1;
}

//asks for daily key (must be as long as numRotors)
char* askDaylyKey(int numRotors) {
	char* result = new char[numRotors];
	std::string tmpResult;
	int i = 0;
	std::cout << "Please enter the daily key (has to be exactly as long as the amount of rotors and only letters are allowed)" << std::endl;
	std::cout << "eg. 5 Rotors -> abcde" << std::endl;

	std::cin >> tmpResult;
	while (std::cin.fail() || tmpResult.length() != numRotors) {
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> tmpResult;
	}

	while (i < numRotors) {																//checks if there are illegal chars in the input array
		char tmp = tmpResult[i];														//illegal chars are every char smaller than 65 or higher than 90
		tmp = ::toupper(tmp);
		if (tmp < 65 || tmp > 90) {														//so only capslock letters are allowed
			do {
				std::cout << "You made a wrong input..try again:" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> tmpResult;
			} while (std::cin.fail() || tmpResult.length() != numRotors);
			i = 0;
		}
		result[i] = tmp;
		i++;
	}
	std::cout << std::endl;

	return result;
}

//asks if we want to decode or encode
bool askIfDecode() {
	char decisionChar;
	std::cout << "Do you want to encode or decode (press d (decode) or e (encode))?" << std::endl;
	std::cin >> decisionChar;

	while (std::cin.fail() || decisionChar != 'd' && decisionChar != 'e') {
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> decisionChar;
	}

	std::cout << std::endl;

	return (decisionChar == 'd') ? true : false;
}

//asks for the message we want to encode or decode (directed by the variable decode) (must not be smaller or same than the number of rotors (so we actually encode or decode something and not only the key)
std::string askForMsg(int numRotors, bool decode) {
	std::string result;

	std::cout << "Type your message you want to " << ((decode) ? "decode" : "encode") << " (incl your msgKey that must be at least as long as the amount of rotors) spaces are not allowed" << std::endl;
	std::cin >> result;
	while (std::cin.fail() || !verfyLetters(changeToUpper(result), numRotors)) {
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> result;
	}

	//change to upper is used to get capsLock letters because only they are allowed
	return changeToUpper(result);
}

bool verfyLetters(std::string & result, int numRotors) {			//checks if the input letters of the message are all alright (no illegal chars) (is used in askForMsg)
	int resultLength = result.length();
	if (resultLength <= numRotors) {
		return false;
	}

	for (int i = 0; i < resultLength; i++)
	{
		if (result[i] < 65 || result[i] > 90) {
			return false;
		}
	}

	return true;
}

std::string changeToUpper(std::string & result) {				//if the char is a lower case letter it will be changed to a upper case letter
	std::string result2 = "";

	for (int i = 0; i < (signed)result.length(); i++) {
		char tmp = ::toupper(result[i]);
		result2 = result2 + tmp;
	}
	return result2;
}

//asks if we want to continue the programm or if we want to quit it with q
void askToContinue() {
	std::cout << std::endl << "Press Enter to continue or enter q to quit the Program" << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char c = getchar();
	if (c == 'q') {
		std::exit(EXIT_SUCCESS);
	}
	if (c != '\n') {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

//asks if we want to change the used daily key
bool askToChangeDaylyKey() {
	char decisionChar;
	std::cout << "Do you want to change the daily key? (y or n)" << std::endl;
	std::cin >> decisionChar;

	while (std::cin.fail() || decisionChar != 'n' && decisionChar != 'y') {
		std::cout << "You made a wrong input..try again:" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> decisionChar;
	}

	std::cout << std::endl;

	return (decisionChar == 'y') ? true : false;
}


//main loop is used when everything is set up right
void mainLoop(Enigma* enigma, int numRotors, bool* isSetRotor, int* rotorTypes, char* daylyKey) {		//gives the setup settings of the enigma machine
	while (true) {																						//infinite loop (we can only exit when we enter q)
		bool change;																					//the variable change is used to check if the user wants to change something
		askToContinue();																				//asks the user if he wants to continue
		system("cls");																					//if so we clear the screen
		printRotorTypes();																				//and print the rotor types
		printEnigmaMachine(numRotors, isSetRotor, rotorTypes);											//and the machine
		change = askToChangeRotor();																	//and ask the user if we want to change something
		while (change) {																				//while the user wants to change something
			int place = askWhatToChange(numRotors);														//we ask him what he wants to change (which rotor on which place)
			rotorTypes[place] = askRotorType(place);													//asks which type the new rotor should have
			system("cls");																				//clears the screen
			enigma->changeRotor(Rotor(getRotorType(rotorTypes[place])), place);							//changes the rotor on the right place with the right rotor type
			printEnigmaMachine(numRotors, isSetRotor, rotorTypes);										//prints the enigma machine with the new settings
			change = askToChangeRotor();																//asks the user again if he wants to change something and if so the loop begins again
		}
		system("cls");																					//clears the screen when the rotors are set up alright
		printEnigmaMachine(numRotors, isSetRotor, rotorTypes);											//prints again the machine with the current settings
		change = askToChangeDaylyKey();																	//ask the user if we want to change the daily key
		system("cls");																					//screen clearing
		if (change) {																					
			printEnigmaMachine(numRotors, isSetRotor, rotorTypes);
			delete[] daylyKey;																			//if so we print the enigma machine again
			daylyKey = askDaylyKey(numRotors);															//and ask the user for the daily key
			system("cls");																				//screen clearing
		}
		enigma->reset();																				//resets the machine (and the rotors to the start position)
		enigma->setDailyKey(daylyKey);																	//sets the old or new daily key

		printEnigmaMachine(numRotors, isSetRotor, rotorTypes);											//prints the enigma machine again
		bool decode = askIfDecode();																	//asks if we want to encode or decode
		std::string msg = askForMsg(numRotors, decode);													//which message (incl message key) we want to en- or decode
		system("cls");																					//screen clearing
		//now we encode or decode the message and print the solution depending on the decode boolean
		std::cout << "Your " << ((decode) ? "decoded" : "encoded") << " message (incl message key):" << std::endl << ((decode) ? enigma->decrypt(msg) : enigma->encrypt(msg)) << std::endl;
		msg = enigma->encrypt(msg);
	}
}
