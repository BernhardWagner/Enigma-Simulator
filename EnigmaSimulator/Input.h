#pragma once
#include "stdafx.h"
#include "Seeds.h"
#include <iostream>
#include "Enigma.h"

void printHeadline();
void printEnigmaMachine(int numRotors, bool* isSetRotor, int* rotorType);
int getNumberOfRotors();
void printRotorTypes();
int askRotorType(int i);
RotorType getRotorType(int resultInt);
bool askToChangeRotor();
int askWhatToChange(int numRotors);
char* askDaylyKey(int numRotors);
bool askIfDecode();
std::string askForMsg(int numRotors, bool decode);
bool verfyLetters(std::string & result, int numRotors);
std::string changeToUpper(std::string & result);
void askToContinue();
bool askToChangeDaylyKey();
void mainLoop(Enigma* enigma, int numRotors, bool* isSetRotor, int* rotorTypes, char* daylyKey);

