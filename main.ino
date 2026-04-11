#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Sensor pins
int tempPin = A0;
int phPin = A1;
int turbidityPin = A2;

// Buzzer pin
int buzzer = 6;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop() {

  // 🌡️ Temperature
  int tempValue = analogRead(tempPin);
  float voltage = tempValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;

  // ⚗️ pH (simulated)
  int phValue = analogRead(phPin);
  float ph = (phValue * 14.0) / 1023.0;

  // 💧 Turbidity
  int turbidity = analogRead(turbidityPin);

  // 🔍 Status Logic (SAFE / WARNING / UNSAFE)
  String status;

  // 🔴 UNSAFE
  if (temperature < 15 || temperature > 40 ||
      ph < 5.5 || ph > 9.5 ||
      turbidity < 600) {

    status = "UNSAFE";
  }

  // 🟡 WARNING
  else if ((temperature >= 15 && temperature < 20) || (temperature > 35 && temperature <= 40) ||
           (ph >= 5.5 && ph < 6.5) || (ph > 8.5 && ph <= 9.5) ||
           (turbidity >= 600 && turbidity < 800)) {

    status = "WARNING";
  }

  // 🟢 SAFE
  else {
    status = "SAFE";
  }

  // 🚨 Buzzer (only for UNSAFE)
  if (status == "UNSAFE") {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  // 📺 LCD Display - Screen 1 (Temp + pH)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);

  lcd.setCursor(0, 1);
  lcd.print("pH:");
  lcd.print(ph);

  delay(2000);

  // 📺 LCD Display - Screen 2 (Turbidity + Message)
  lcd.clear();

  // Line 1 → Turbidity value
  lcd.setCursor(0, 0);
  lcd.print("Turb:");
  lcd.print(turbidity);

  // Line 2 → Message
  lcd.setCursor(0, 1);

  if (status == "SAFE") {
    lcd.print("SAFE FOR USE ");
  }
  else if (status == "WARNING") {
    lcd.print("CHECK WATER  ");
  }
  else {
    lcd.print("DO NOT USE   ");
  }

  delay(2000);

  // 🖥️ Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | pH: ");
  Serial.print(ph);
  Serial.print(" | Turbidity: ");
  Serial.print(turbidity);

  Serial.print(" | Status: ");
  Serial.println(status);

  delay(1000);
}
