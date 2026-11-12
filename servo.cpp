#include "servo.h"
#include <Servo.h>

#define Servo_PIN 5

Servo persiana;
static int currentAngle = 0;

void initServo() {
  currentAngle = 0;
}

void moverServo(int angulo) {
  angulo = constrain(angulo, 0, 180);
  
  persiana.attach(Servo_PIN);
  persiana.write(angulo);
  
  int diferencia = abs(angulo - currentAngle);
  int tiempoEspera = max(150, diferencia * 4);
  delay(tiempoEspera);
  
  persiana.detach();
  currentAngle = angulo;
}

void moveServo(int angle) {
  moverServo(angle);
}

int getServoAngle() {
  return currentAngle;
}

void moverPersianaPorcentaje(int porcentaje) {
  porcentaje = constrain(porcentaje, 0, 100);
  int angulo = map(porcentaje, 0, 100, 0, 180);
  moverServo(angulo);
}
