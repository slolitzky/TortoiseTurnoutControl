//pin 13 on chip is output enabled bring low to allow output active
// pin 14 is the serial data in
// pin 11 is the serial clock to move serial data in
// pin 12 is the register clock to move serial register to the output register
// pin 10 is the serial register clear bit bring it LOW to clear it, leave it high +5
// pin 8 is ground


const int dataPin = 4;   // serial data in which is pin 14
const int latchPin = 5;  // register clock to move data in pin 12
const int clockPin = 6;  // clock in the serial data pin 11
#define THROWN 1
#define CLOSED 0


