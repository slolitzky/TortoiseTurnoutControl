/*
 * Turnout.cpp
 *
 *  Created on: Jun 26, 2023
 *      Author: solitzky
 *  Editied on 6/29/2023
 *  10/14/2023 First Version Checked into git with more comments in file.
 *  11/06/2023 Added code to allow DC motor to rotate or be stopped. This code is currently commented out.
 */

#include "Turnout.h"
#include <Arduino.h>

// constructor takes three arduino pins to control the turnout registers
Turnout::Turnout(unsigned int dataPin, unsigned int latchPin,
		unsigned int clockPin) :
		_dataPin(dataPin), _latchPin(latchPin), _clockPin(clockPin) {
	pinMode(_latchPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);

}

// return the number of turnsout we have
unsigned int Turnout::getMaxTurnouts() {
	return maxTurnouts;
}

// sets the value of the turnout in the turnout table
// this routine first checks the current state of the turnout
// it will only change it if the turnout is different.  Saves a bit of computing.
void Turnout::setTurnout(unsigned int tOut, bool value) {
	int index = tOut / 8;
	bool oldState = getTurnout(tOut);
	if (oldState != value) {
		bitWrite(_turnoutRegs[index], tOut % 8, value);
		changeTurnout(tOut, value);
		activateTurnoutControls();
	}
}

// get the state of the turnout from the turnout table
bool Turnout::getTurnout(unsigned int tOut) {
	int index = tOut / 8;
	return bitRead(_turnoutRegs[index], tOut % 8);
}

// we will change one turnout
void Turnout::changeTurnout(unsigned int tOut, bool state) {
	int index = (tOut * 2) / 8;        // two bytes to change
	unsigned int pos = (tOut * 2) % 8; // first position , both positions are always in the same byte, laws of evenness
	if (state == CLOSED) {
		bitWrite(_outputRegs[index], pos, CLOSED0);
		bitWrite(_outputRegs[index], pos + 1, CLOSED1);

	} else {
		bitWrite(_outputRegs[index], pos, THROWN0);
		bitWrite(_outputRegs[index], pos + 1, THROWN1);
	}
}

// we will change one Light, this uses to values.
// really three states, left, right, off
// odd lights we could turn in one direction, even in another
/*void Turnout::changeLight(unsigned int tOut, bool state) {
    // If x % 2 is '0' that means that x is even.
    bool evenYes = (tOut % 2 == 0);
	int index = (tOut * 2) / 8;        // two bytes to change
	unsigned int pos = (tOut * 2) % 8; // first position , both positions are always in the same byte, laws of evenness
	if (state == TRUE) {
		bitWrite(_outputRegs[index], pos, CLOSED0);
		bitWrite(_outputRegs[index], pos + 1, CLOSED1);

	} else {
		bitWrite(_outputRegs[index], pos, THROWN0);
		bitWrite(_outputRegs[index], pos + 1, THROWN1);
	}
}
*/

// this routine actually writes the data to the registers which will change all of the turnout servos at once.
// there may not be an actual state change though in the servos
void Turnout::activateTurnoutControls() {
	digitalWrite(_latchPin, LOW);

	for (int i = (maxOutput) - 1; i >= 0; i--) {
		shiftOut(_dataPin, _clockPin, MSBFIRST, _outputRegs[i]);
	}
	digitalWrite(_latchPin, HIGH);

}

Turnout::~Turnout() {

}

