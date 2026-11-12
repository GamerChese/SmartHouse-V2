#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include "counter.h"

void initLED();
void turnON(int ledPin);
void turnOFF(int ledPin);
void blikLED(int ledPin, unsigned long ms);

#endif // LDR_H

