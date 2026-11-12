#include "ldr.h"
#include "servo.h"

#define LDR_1 A1
#define LDR_2 A2 


int getLDR1() {
  return analogRead(LDR_1);
}

int getLDR2() {
  return analogRead(LDR_2);
}

float averageLDRs() {
  int a = getLDR1();
  int b = getLDR2();

  return (a + b) / 2;
}

int percentLDR() {
  float average = averageLDRs();
  float value = (average * 100) / 1023;

  return value;
}


void handleLDR(int value) {
  if (value < 25) {
    moverServo(0);
  } 
  else if (value < 50) {
    moverServo(45);
  } 
  else if (value < 75) {
    moverServo(90);
  } 
  else {
    moverServo(180);
  }
}

