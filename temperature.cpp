#include "temperature.h"

#define TEMP_PIN A0

static float temperaturaC = 0.0;

int getCelsius() {
  int tempValue = analogRead(TEMP_PIN);
  float voltaje = (tempValue * 5.0) / 1023.0;
  temperaturaC = voltaje * 100.0;

  return round(temperaturaC);
}

int getFahrenheit() {
  float fahrenheit = (temperaturaC * 9.0 / 5.0) + 32.0;
  return round(fahrenheit);
}

