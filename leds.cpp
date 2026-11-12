#include "leds.h"
    #define RED_LED 11
    #define WHITE_LED 10

bool ledState = false;


void initLED(){

    pinMode(RED_LED, OUTPUT);
    pinMode(WHITE_LED, OUTPUT);
    startCounter();
}

void turnON(int ledPin){
    digitalWrite(ledPin,1);
}
void turnOFF(int ledPin){
    digitalWrite(ledPin,0);
}
void blikLED(int ledPin, unsigned long ms){
    if (isCounterDone(ms)){
        ledState = !ledState;
        digitalWrite(ledPin,ledState);
        startCounter();
    }
}