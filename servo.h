#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>

void initServo();
void moverServo(int angulo);
void moveServo(int angle);
int getServoAngle();
void moverPersianaPorcentaje(int porcentaje);

#endif // SERVO_H

