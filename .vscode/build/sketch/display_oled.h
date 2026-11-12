#line 1 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\display_oled.h"
#ifndef DISPLAY_OLED_H
#define DISPLAY_OLED_H

#include <Arduino.h>

bool initDisplay();
void mostrarTemperaturas(const char* nombre, int c, int f);

#endif // DISPLAY_OLED_H

