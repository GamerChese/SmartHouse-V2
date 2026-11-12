#include "bt.h"
#include <SoftwareSerial.h>

SoftwareSerial BluetoothModule(4, 2);

void initBT() {
  BluetoothModule.begin(9600);
  BluetoothModule.setTimeout(100);
}

void handleBT() {
  if (BluetoothModule.available()) {
    String word = BluetoothModule.readString();
    word.trim();
    word.toLowerCase();

    Serial.print("Recibido por BT: ");
    Serial.println(word);

    if (word.equals("start")) {
      BluetoothModule.println("Bienvenido, ingresa tu nombre");
    }
  }
}