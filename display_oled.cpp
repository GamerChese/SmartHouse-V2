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


void handleIntruder() {

}



void showStatus(const char* name, int c, int f, bool presence) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (!presence) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Buenos dias, ");
    display.println(name);

    display.setTextSize(2);
    display.setCursor(0, 22);
    display.print(c);
    display.print((char)247);
    display.print("C");

    display.setCursor(68, 22);
    display.print(f);
    display.print("%");
  } else {
    display.fillScreen(SSD1306_WHITE);

    display.drawTriangle(64, 4, 38, 40, 90, 40, SSD1306_BLACK);
    display.drawTriangle(64, 5, 39, 39, 89, 39, SSD1306_BLACK);

    display.drawLine(64, 16, 64, 28, SSD1306_BLACK);
    display.drawPixel(64, 33, SSD1306_BLACK);
    display.drawPixel(64, 34, SSD1306_BLACK);

    display.setTextColor(SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(41, 48);
    display.println("Intruso!");
  }
  display.display();
}

