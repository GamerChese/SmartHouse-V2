#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define BT_RX_PIN 4
#define BT_TX_PIN 2

#define LDR_1 A1
#define LDR_2 A2

#define TEMP_PIN A0
#define PIR_PIN 8
#define SERVO_PIN 5

#define RED_LED 11
#define WHITE_LED 10
#define BUZZER_PIN 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial BluetoothModule(BT_RX_PIN, BT_TX_PIN);
Servo persiana;

const char name[] = "Aaron";

unsigned long tiempoInicial = 0;
bool contando = false;

bool ledState = false;
bool whiteLedState = true;

int currentAngle = 0;
bool persianaAutoMode = true;

const unsigned long ALARM_DURATION_MS = 5000;
unsigned long buzzerTimer = 0;
unsigned long lastPresenceTime = 0;
bool buzzerToneState = false;
bool alarmActive = false;

float temperaturaC = 0.0;

void startCounter() {
  tiempoInicial = millis();
  contando = true;
}

bool isCounterDone(unsigned long ms) {
  if (!contando) {
    return false;
  }

  if (millis() - tiempoInicial >= ms) {
    contando = false;
    return true;
  }
  return false;
}

void initLED() {
  pinMode(RED_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  startCounter();
}

void turnON(int ledPin) { digitalWrite(ledPin, HIGH); }

void turnOFF(int ledPin) { digitalWrite(ledPin, LOW); }

void blikLED(int ledPin, unsigned long ms) {
  if (isCounterDone(ms)) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    startCounter();
  }
}

void initBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  noTone(BUZZER_PIN);
}

void sonarAlarma() {
  unsigned long currentMillis = millis();

  if (currentMillis - buzzerTimer >= 150) {
    buzzerTimer = currentMillis;
    buzzerToneState = !buzzerToneState;

    if (buzzerToneState) {
      digitalWrite(BUZZER_PIN, HIGH);
      tone(BUZZER_PIN, 1800);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      tone(BUZZER_PIN, 900);
    }
  }
}

void apagarBuzzer() {
  noTone(BUZZER_PIN);
  digitalWrite(BUZZER_PIN, LOW);
  buzzerToneState = false;
}

void initServo() { currentAngle = 0; }

void moverServo(int angulo) {
  angulo = constrain(angulo, 0, 180);

  persiana.attach(SERVO_PIN);
  persiana.write(angulo);

  int diferencia = abs(angulo - currentAngle);
  int tiempoEspera = max(150, diferencia * 4);
  delay(tiempoEspera);

  persiana.detach();
  currentAngle = angulo;
}

void moveServo(int angle) { moverServo(angle); }

int getServoAngle() { return currentAngle; }

void moverPersianaPorcentaje(int porcentaje) {
  porcentaje = constrain(porcentaje, 0, 100);
  int angulo = map(porcentaje, 0, 100, 0, 180);
  moverServo(angulo);
}

int getLDR1() { return analogRead(LDR_1); }

int getLDR2() { return analogRead(LDR_2); }

float averageLDRs() {
  int a = getLDR1();
  int b = getLDR2();

  return (a + b) / 2.0;
}

int percentLDR() {
  float average = averageLDRs();
  float value = (average * 100.0) / 1023.0;

  return (int)value;
}

void handleLDR(int value) {
  if (value < 25) {
    moverServo(0);
  } else if (value < 50) {
    moverServo(45);
  } else if (value < 75) {
    moverServo(90);
  } else {
    moverServo(180);
  }
}

bool presencePIR() { return digitalRead(PIR_PIN); }

int getCelsius() {
  int total = 0;
  for (int i = 0; i < 5; i++) {
    total += analogRead(TEMP_PIN);
    delay(2);
  }
  float avgRaw = total / 5.0;
  float voltaje = (avgRaw * 5.0) / 1023.0;
  temperaturaC = voltaje * 100.0;

  return round(temperaturaC);
}

int getFahrenheit() {
  float fahrenheit = (temperaturaC * 9.0 / 5.0) + 32.0;
  return round(fahrenheit);
}

bool initDisplay() {
  return display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

void handleIntruder() {}

void showStatus(const char *name, int c, int f, bool presence) {
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
      BluetoothModule.println(F("Bienvenido a Smart House"));
    }
    else if (word.equals("luz on")) {
      whiteLedState = true;
      digitalWrite(WHITE_LED, HIGH);
      BluetoothModule.println(F("OK: Luz interior ENCENDIDA"));
    }
    else if (word.equals("luz off")) {
      whiteLedState = false;
      digitalWrite(WHITE_LED, LOW);
      BluetoothModule.println(F("OK: Luz interior APAGADA"));
    }
    else if (word.equals("abrir")) {
      persianaAutoMode = false;
      moverServo(180);
      BluetoothModule.println(F("OK: Persiana ABIERTA (Modo Manual)"));
    }
    else if (word.equals("cerrar")) {
      persianaAutoMode = false;
      moverServo(0);
      BluetoothModule.println(F("OK: Persiana CERRADA (Modo Manual)"));
    }
    else if (word.equals("auto")) {
      persianaAutoMode = true;
      handleLDR(percentLDR());
      BluetoothModule.println(F("OK: Persiana en Modo AUTOMATICO (por sensor LDR)"));
    }

    else if (word.equals("status")) {
      BluetoothModule.println(F("SMART HOUSE STATUS"));
      BluetoothModule.print(F("Temperatura: "));
      BluetoothModule.print(getCelsius());
      BluetoothModule.println(F(" *C"));
      BluetoothModule.print(F("Luz exterior: "));
      BluetoothModule.print(percentLDR());
      BluetoothModule.println(F(" %"));
      BluetoothModule.print(F("Luz interior: "));
      BluetoothModule.println(whiteLedState ? F("ENCENDIDA") : F("APAGADA"));
      BluetoothModule.print(F("Persiana: "));
      BluetoothModule.print(getServoAngle());
      BluetoothModule.println(persianaAutoMode ? F(" deg [AUTO]")
                                               : F(" deg [MANUAL]"));
      BluetoothModule.print(F("Alarma: "));
      BluetoothModule.println(alarmActive ? F("!ALERTA INTRUSO!")
                                          : F("DESPEJADO (Seguro)"));
    }
  }
}

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
  initBuzzer();
  startCounter();
}

void loop() {
  int c = getCelsius();
  int ldr = percentLDR();
  bool presence = presencePIR();

  if (presence) {
    lastPresenceTime = millis();
    alarmActive = true;
  }

  if (alarmActive) {
    if (millis() - lastPresenceTime < ALARM_DURATION_MS) {
      blikLED(RED_LED, 150);
      sonarAlarma();
    } else {
      alarmActive = false;
      turnOFF(RED_LED);
      apagarBuzzer();
    }
  } else {
    turnOFF(RED_LED);
    apagarBuzzer();
  }

  digitalWrite(WHITE_LED, whiteLedState ? HIGH : LOW);
  if (persianaAutoMode) {
    handleLDR(ldr);
  }
  Serial.println(presence);
  showStatus(name, c, ldr, alarmActive);

  handleBT();

  delay(50);
}
