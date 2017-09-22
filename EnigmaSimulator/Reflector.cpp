#include "Reflector.h"
#include <algorithm>

Reflector::Reflector(int randSeed) : EncoderModule(randSeed) {
	seed = randSeed;
	init();
}

Reflector::Reflector() : EncoderModule (){
	Reflector(0);
}

Reflector::~Reflector() {
	
}

void Reflector::init() {
	
	srand(seed);
	for (int i = 0; i < NUM_LETTERS; i++)
	{
		m_configuration[i] = -1;				//placeholder (says that array is empty)
	}

	for (int i = 0; i < NUM_LETTERS; i++) {
		int random = rand() % (NUM_LETTERS);

		while (m_configuration[i] != -1) {
			i++;
		}

		while ((m_configuration[random] != -1 || random == i) && i < NUM_LETTERS) {
			random = rand() % (NUM_LETTERS);
		}

		if (i < NUM_LETTERS) {					//only set the values if we are in range
			m_configuration[random] = i;
			m_configuration[i] = random;
		}

	}
	//debugging something
	/*for (int i = 0; i < NUM_LETTERS; i++)
	{
		if (m_configuration[m_configuration[i]] != i) {
			std::cout << "false";
		}
		std::cout << i << "=>" << m_configuration[i] << std::endl;
		
	}

	getchar();
	getchar();*/
}