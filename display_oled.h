#ifndef DISPLAY_OLED_H
#define DISPLAY_OLED_H

#include <Arduino.h>

bool initDisplay();
void showStatus(const char* nombre, int c, int f, bool pre);
void showIntruso();
void clearDisplay();

#endif // DISPLAY_OLED_H

