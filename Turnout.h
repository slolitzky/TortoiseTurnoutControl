/*
 * Turnout.h
 *
 *  Created on: Jun 26, 2023
 *      Author: solitzky
 *  10/14/2023 First Version Checked into git with more comments in file.
 *  11/06/2023 Added comment.
 */

#ifndef TURNOUT_H_
#define TURNOUT_H_
#include <Arduino.h>

// pin 13 on chip is output enabled bring low to allow output active
// pin 14 is the serial data in
// pin 11 is the serial clock to move serial data in
// pin 12 is the register clock to move serial register to the output register
// pin 10 is the serial register clear bit bring it LOW to clear it, leave it high +5
// pin 8 is ground

//const int DATAPIN = 4;   // serial data in which is pin 14
//const int LATCHPIN = 5;  // register clock to move data in pin 12
//const int CLOCKPIN = 6;  // clock in the serial data pin 11

class Turnout {
public:
	Turnout(unsigned int dataPin = 4,
			unsigned int latchPin = 5,
			unsigned int clockPin = 6);

	virtual ~Turnout();
	unsigned int getMaxTurnouts();
	// sets the value of the turnout in the turnout table
	void setTurnout(unsigned int tOut, bool value);

	bool getTurnout(unsigned int tOut);

private:

	// if used with CMRI then the maximum number of turnouts is 48 but inputs is 24 so if you want to use one node for both
	// turnouts and sensors limit this to 24
#define maxRegs 3  // 3*8 = 24
#define maxTurnouts 24  // for now only five bytes  each byte takes two output registers
#define maxOutput 6

#define CLOSED 0
#define THROWN 1
#define CLOSED0 0
#define CLOSED1 1
#define THROWN0 1
#define THROWN1 0
// to stop a motor set both imputs to same value

	unsigned int _dataPin;
	unsigned int _latchPin;
	unsigned int _clockPin;
	unsigned char _turnoutRegs[maxRegs];     // Registers current state since it is returned
	unsigned char _outputRegs[maxOutput]; // each turnout takes two bits to control
	//const unsigned int _delayTime = 1000; // one second to allow turnout to work
	void changeTurnout(unsigned int tOut, bool state);
	void activateTurnoutControls();
};

#endif /* TURNOUT_H_ */
