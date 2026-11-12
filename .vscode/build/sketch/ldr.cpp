#line 1 "C:\\Users\\Jonatan Robledo\\Desktop\\PIA\\ldr.cpp"
#define LDR_1 A1
#define LDR_2 A2 


int getCelsius() {
  int tempValue = analogRead(TEMP_PIN);
  float voltaje = (tempValue * 5.0) / 1023.0;
  temperaturaC = voltaje * 100.0;

  return round(temperaturaC);
}