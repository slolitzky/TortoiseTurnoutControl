/*
 * Ardunio.h
 *
 *  Created on: Jun 26, 2023
 *      Author: solitzky
 *      This is a dummy header for using in ECLIPSE or other C++/C IDE, don't use this one for the Arduino actual files.
 */

#ifndef ARDUNIO_H_
#define ARDUNIO_H_
#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define MSBFIRST 0x0

void pinMode(unsigned int  pin, unsigned int mode);
void digitalWrite(unsigned int pin, unsigned int val);
int digitalRead(unsigned int pin);
void bitWrite(unsigned char theReg, unsigned int index, bool val);
bool bitRead(unsigned char theReg, unsigned int index);
void shiftOut(unsigned int dataPin, unsigned int clockPin, unsigned int  bitOrder, unsigned int val);


#endif /* ARDUNIO_H_ */
