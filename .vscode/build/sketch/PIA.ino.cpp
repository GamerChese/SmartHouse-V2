#include <Arduino.h>
#line 1 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\PIA.ino"
#include "temperature.h"
#include "display_oled.h"

const char nombre[] = "The Warning";

#line 6 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\PIA.ino"
void setup();
#line 15 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\PIA.ino"
void loop();
#line 6 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\PIA.ino"
void setup() {
  Serial.begin(9600);

  if (!initDisplay()) {
    Serial.println(F("Fallo al inicializar SSD1306"));
    for (;;);
  }
}

void loop() {
  int c = getCelsius();
  int f = getFahrenheit();

  Serial.print("Temperatura: ");
  Serial.print(c);
  Serial.print(" °C | ");
  Serial.print(f);
  Serial.println(" °F");

  mostrarTemperaturas(nombre, c, f);

  delay(1000);
}

