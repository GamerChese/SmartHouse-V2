#ifndef LDR_H
#define LDR_H

#include <Arduino.h>

int getLDR1();
int getLDR2();
float averageLDRs();
int percentLDR();
void handleLDR(int ldr);

#endif // LDR_H

