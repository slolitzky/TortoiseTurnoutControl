# TortoiseTurnoutControl

Following is a simple explanation of what the software does.

I control 24 Tortoise turnouts using one Arduino Uno.  I use L298 Dual Motor Controller Modules which I purchased off of Amazon.  They are really economical.
You get four of them for $11.50  you can control 8 tortoises.  You supply 12 volts to them and with an Ardunio and some software you can make the switch thrown or closed.  Since the Tortoises are stall motors this is really easy to do as you just have the motor controllers change polarity just like using a toggle switch.
I use  74595 shift registers and by wiring them together I can control as many Tortoise switches from one Arduino uno using only 3 Arduino output pins to control all of the switches via the shift registers.  Each L298 Motor Controller takes 2 outputs from each shift register for each Tortoise.  On one  74595 I can control 4 tortoises.  I have 6 shift registers wired.  

The two files turnout.cpp and turnout.h are C++ files that can be used in an Arduino library to be called by a Arduino sketch.  The third file is a mock arduino.h file that is needed
when you are using a C++ IDE such as Eclipse. (Use the arduino.h distributed with the arduino IDE when compiling your sketch.)


The library files use the standard C++ conventions for an Arduino library.  They are stored in "ardunio/libraries/Turnouts" where the ardunio part of the path is wherever 
you have your Adrunio development.

A sample sketch that interfaces using C/MRI and JMRI is included with its header file.  These are controlTortoiseTurnout.ino and turnoutData.h.


Files:

controlTortoiseTurnout.ino	// arduino sketch using C/MRI and JMRI

turnoutData.h		 	// header file

turnout.cpp					// c++ source file that you use in Arduino library.  I use Eclipse to compile and edit C++

turnout.h                  // c++ header file

arduino.h                    // mock header file needed for C++ IDE, (don't use with Arduino sketch)
