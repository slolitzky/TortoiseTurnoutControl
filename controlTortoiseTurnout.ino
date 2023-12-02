
/**
 * This example uses C/MRI and JMRI to control Tortoise Turnouts.
 *
 * A C/MRI -> JMRI interface
 * =================================
 * Sets up pin 13 (LED) as an output, and attaches it to the first output bit
 * of the emulated SMINI interface.
 * 
 * To set up in JMRI:
 * 1: Create a new connection, 
 *    - type = C/MRI, 
 *    - connection = Serial, 
 *    - port = <arduino's port>, 
 *    - speed = 9600
 * 2: Click 'Configure C/MRI nodes' and create a new SMINI node
 * 3: Click 'Add Node' and then 'Done'
 * 4: Restart J/MRI and it should say "Serial: using Serial on COM<x>" - congratulations!
 * 5: Open Tools > Tables > Lights and click 'Add'
 * 6: Add a new light at hardware address 1, then click 'Create' and close the window. Ignore the save message.
 * 7: Click the 'Off' state button to turn the LED on. Congratulations!
 * 
 * Debugging:
 * Open the CMRI > CMRI Monitor window to check what is getting sent.
 * With 'Show raw data' turned on the output looks like:
 *    [41 54 01 00 00 00 00 00]  Transmit ua=0 OB=1 0 0 0 0 0 
 * 
 * 0x41 = 65 = A = address 0
 * 0x54 = 84 = T = transmit, i.e. PC -> C/MRI
 * 0x01 = 0b00000001 = turn on the 1st bit
 * 0x00 = 0b00000000 = all other bits off
 */
#include <CMRI.h>
#include <Turnout.h>
#include "turnoutData.h"
// this can support up to 24 turnouts using 3 bytes.  Each turnout will be controlled by a serial/parellel
// shift register.   By increase the number of bytes we can increase the number of turnouts to be infinite.
// unfortunately a default CMRI object only supports 24 inputs but can handle 48 outputs .  It can be changed thou.


CMRI cmri0(0);         // first SMINI, 24 inputs, 24 outputs  use for both turnouts and turnout sensors
Turnout turnOut(dataPin, latchPin, clockPin);
int numTurnouts;
void setup() {
  Serial.begin(9600, SERIAL_8N2);  // make sure this matches your speed set in JMRI
  delay(3000);                     // wait for console to open
  numTurnouts = turnOut.getMaxTurnouts();  // set in the library
}

void loop() {

  // put your main code here, to run repeatedly:
  // when the data is zero we close the turnout
  // when the data is one we throw the turnout

  bool found0 = false;  // turnouts
 
  char c;


  while (Serial.available() > 0) {
    c = Serial.read();
    found0 = cmri0.process_char(c);
  }

  // now process any change bits,  change the arrays one at a time so that we switch them all at different times.

  if (found0) {
    for (int i = 0; i < numTurnouts; i++) {
      turnOut.setTurnout(i, cmri0.get_bit(i));  // lower level handles differences
      cmri0.set_bit(i, turnOut.getTurnout(i));
    }
  }
  
}

