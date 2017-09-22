#include "Enigma.h"

Enigma::Enigma(int numRotors) {
	m_rotors = new Rotor*[numRotors]();				//creates an machine with a preset amount of rotors
	m_numRotors = numRotors;						//m_numRotors is needed to get the size of m_rotors
	m_reflector = Reflector(ReflectorSeed);			//creates the reflecor
}

Enigma::~Enigma() {
	for (int i = 0; i < m_numRotors; i++)		//deletes the rotor pointers in m_rotors
	{
		delete m_rotors[i];
	}
	delete[] m_rotors;							//delets the rotor array
	delete m_msgKey;							//deletes the m_msgKey array
}

void Enigma::addRotor(RotorType type) {
	for (int i = 0; i < m_numRotors; i++)		//finds the next empty space of the m_rotors array
	{											//adds the rotor if there was a empty space found
		if (m_rotors[i] == nullptr) {
			/*std::cout << type << "----" << i << std::endl;			//for debugging purpose
			getchar();
			getchar();*/
			m_rotors[i] = new Rotor(type);		//adds the new rotor with the specific type
			return;								//returns if there was an empty space and the new rotor was set
		}
	}
}

void  Enigma::changeRotor(Rotor &rotor, int posIdx) {
	delete m_rotors[posIdx];
	m_rotors[posIdx] = &rotor; //sets the new rotor
}

void  Enigma::setDailyKey(char key[]) {
	//first key is the first rotor rotation (B -> is one rotation, c are two rotations...) 
	//second key is the second rotor rotation

	for (int i = 0; i < m_numRotors; i++)			//iterates over the daily-key-array
	{
		int rotationValue = this->toInt(key[i]);	//gets the rotationValue out of the character

		for (int i = 0; i <= rotationValue; i++)	 //sets the rotator right (no need to check if you also need to rotate the next rotor
		{											//because the rotors are at the beginning at pos 0 and only can rotate 25 times
			if (m_rotors[0] != nullptr) {			//ensures that there is a rotor to rotate
				m_rotors[0]->turnRotor();
			}
		}
	}

	//str.c-str(); const char* umwandeln
	
}

void  Enigma::setMessageKey(char key[]) {			//setter for msgKey
	this->m_msgKey = key;
}

void  Enigma::reset() {								//resets the enigma machine to the beginning state
	for (int i = 0; i < m_numRotors; i++)
	{
		if (m_rotors != nullptr) {				 //if the rotor exists
			m_rotors[i]->reset();				//resets every rotor in the machine
		}				
	}
}

std::string  Enigma::encrypt(const std::string & msg) {
	//INFO: daily key is already set
	//creates the result string that will be reuturned
	std::string result = "";

	//get an char array of the msg
	int msgLength = msg.length();				//verify the length of the string

	char* msgKeyTmp = new char[m_numRotors];		//creates an empty char array for the temporary msgKey (that is as long as the number of used rotors)
	
	for (int i = 0; i < m_numRotors; i++)		//encodes every character in the char Array
	{
		msgKeyTmp[i] = msg[i];                        //saves the first n letters of the msg to the msgKey-array that will be later applied
		result = result + processChar(msgKeyTmp[i]);  //encodes the message key with the daily-key-settings and saves them in the result string (encoded string includes msgKey)
	}
	this->setMessageKey(msgKeyTmp);					//now the msgKey will be set
	this->applyMsgKey();							//and applied

	for (int i = m_numRotors; i < msgLength; i++)	//now with the right setting the actual encoding begins
	{
		result = result + processChar(msg[i]);		//encodes every char of the msgString
	}

	delete[] msgKeyTmp;								//deletes the msgKeyTmp array
	return result;									//returns the result (encoded msg key and encoded message)
}

std::string  Enigma::decrypt(const std::string & msg) {
	//INFO: daily key is already set
	//creates the result string that will be reuturned
	std::string result = "";

	char* msgKeyTmp = new char[m_numRotors];		//creates an temporary array for the mesage key

	int msgLength = msg.length();			 //determines the length of the msg string

	for (int i = 0; i < m_numRotors; i++)		//iterates over the first chars of the message until the number of the amount of the rotors is reached (gets the msgKey)
	{
		msgKeyTmp[i] = processChar(msg[i]);  //encrypt msgKey with the daily key settings and saves the result in msgKey
		result = result + msgKeyTmp[i];		//also saves the key in the result string
	}
	this->setMessageKey(msgKeyTmp);			//sets the msgKey
	this->applyMsgKey();					//applies the encrypted msgKey

	//actual encoding with the right settings
	for (int i = m_numRotors; i < msgLength; i++)		//iterates over the rest of the message (without the message key)
	{
		result = result + this->processChar(msg[i]);		//encodes the characters of the message and saves them in the result string
	}

	delete[] msgKeyTmp;									//deletes the msgKeyTmp array
	return result;										//returns the result
}

void  Enigma::applyMsgKey() {
	for (int i = 0; i < m_numRotors; i++) //iterates over the msgKey array that is as big as the number of rotors used in the machine
	{
		int rotationValue = this->toInt(m_msgKey[i]); //transforms the character to the rotation value to know how often we have to rotate
														
		for (int j = 0; j < rotationValue; j++)			//now rotates the rotor as long as the rotationValue is
		{
			if (m_rotors[i] != nullptr) {
				//m_rotors[i]->print();
				int d = m_rotors[i]->turnRotor();

				//do we have to rotate the next rotor
				int counter = 1;															//now we also have to ensure, if the rotor made one full rotation
				while (d == 1 && m_rotors[counter] != nullptr && counter < m_numRotors) {	//that the next rotor will be rotated once
					d = m_rotors[counter]->turnRotor();
					counter++;
				}
			}
		}
	}
}

int  Enigma::toInt(char c) {		//converts the character to an int (-65 to get the right number)
	return (int)(c - 65);
}

char  Enigma::toChar(int i) {		//converts an integer to an character (+ 65 to get the right char)
	return (char)(i + 65);
}

char Enigma::processChar(char letter) {
	if (letter > 90 || letter < 65) {			//security check (is not really needed because we catch the mistakes with the input file (but to make sure we do it anyways)
		return -1;
	}
		int numValChar = this->toInt(letter);			//gets the num value of the given letter (character)

		for (int i = 0; i < m_numRotors; i++)			//goes throught every rotor in the machine
		{
			Rotor* currentRotor = m_rotors[i];
			numValChar = currentRotor->getCode(numValChar);			//saves the new letter in numValChar (so the old letter will get the new letter)
		}

		numValChar = m_reflector.getIndex(numValChar);			//reflect (old letter gets a new letter again)


		for (int i = m_numRotors - 1; i >= 0; i--)				//iterates backwards through the rotors
		{
			Rotor* currentRotor = m_rotors[i];
			numValChar = currentRotor->getIndex(numValChar);	//because we go backwards throught the rotors we need to get the index of the characters and not the value
		}
		char result = this->toChar(numValChar);					//translates the numValue again to a char and saves them as result

		//rotate rotor
		int d = m_rotors[0]->turnRotor();						//now we can rotate the rotor and save the return value to d that expresses if we have to rotate the next rotor (d = 1) or not (d = 0)

		int counter = 1;										//sets up a counter
		while (d == 1 && m_rotors[counter] != nullptr && counter < m_numRotors) {	//while we made a full rotation  with the current rotor and there is a next rotor
			d = m_rotors[counter]->turnRotor();										//we also rotate that rotor and save again the decision value (0 or 1)
			counter++;																//now we jump to the next rotor and we repeat the loop if there is a next rotor and if the decision value d is 1
		}

	return result;												//now we can return the result
}