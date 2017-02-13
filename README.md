# TestThingspeakMCP9700
A test with Thingspeak with gizDuino IOT. ADC reading with MCP9700 at A0.

Some notes:

1. Tested with Arduino 1.16.12 installed with thingspeak library. Sketch > Manage Library, search for thingspeak and install.
2. Used the library and patch provided by e-Gizmo
.
3. Overwrite Wstring.cpp and Wstring.h with the newer version from \\arduino-1.6.12\hardware\arduino\avr\cores\arduino.
	Copy the two files and overwrite the files under \\arduino-1.6.12\hardware\gizduino-\avr\cores\gizduino+
.
4. 
Open an account in Thingspeak.com and create a channel. You will be needing the channel number and the WriteAPIkey when sending the data.
5. The sketch is solely based on the sample program provided by e-gizmo with some modification from here: https://github.com/mathworks/thingspeak-arduino/tree/master/examples/WriteVoltage
