#line 1 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\display_oled.cpp"
#include "display_oled.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool initDisplay() {
  return display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

void mostrarTemperaturas(const char* nombre, int c, int f) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Encabezado
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Buenos dias, ");
  display.println(nombre);

  // Valores de temperatura
  display.setTextSize(2);
  display.setCursor(0, 22);
  display.print(c);
  display.print((char)247);
  display.print("C");

  display.setCursor(68, 22);
  display.print(f);
  display.print((char)247);
  display.print("F");

  display.display();
}

