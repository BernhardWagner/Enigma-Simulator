#pragma once

class EncoderModule {
public:
	static const int NUM_LETTERS = 26;
	EncoderModule();
	EncoderModule(int randSeed);
	virtual ~EncoderModule();
	// initialize the configuration array
	virtual void init() = 0;
	// print the configuration array
	virtual void print() const;
	// get element at index ’idx’
	virtual int getCode(int idx) const;
	// get the index of element ’code’
	virtual int getIndex(int element) const;
protected:
	int m_configuration[NUM_LETTERS];
};