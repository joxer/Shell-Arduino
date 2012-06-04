


#include "shell.h"

int incomingByte = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600); 
        // opens serial port, sets data rate to 9600 bps
}

void loop() {

    ArduinoShell *a = new ArduinoShell(9600);
    a->getChoice();
}
 
