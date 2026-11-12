#include "temperature.h"
#include "display_oled.h"
#include "ldr.h"
#include "servo.h"
#include "pir.h"
#include "bt.h"
#include "leds.h"
    #define RED_LED 11
    #define WHITE_LED 10

const char name[] = "Jonatan";

void setup() {
  Serial.begin(9600);

  if (!initDisplay()) {
    Serial.println(F("Fallo al inicializar SSD1306"));
    for (;;)
      ;
  }
  initServo();
  initBT();
  initLED();
  startCounter();
}

void loop() {
  int c = 22;
  int ldr = percentLDR();
  bool presence = presencePIR();

 
 if (presence){
  blikLED(RED_LED, 200);
  turnON(12);
 }
 else{
  turnOFF(RED_LED);
  turnOFF(12);
 }

  digitalWrite(WHITE_LED, 1);
  handleLDR(ldr);
  Serial.println(presence);
  showStatus(name, c, ldr, presence);

  handleBT();

  delay(200);
}
