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

  // ⚗️ pH (simulated using potentiometer)
  int phValue = analogRead(phPin);
  float ph = (phValue * 14.0) / 1023.0;

  // 💧 Turbidity (photoresistor)
  int turbidity = analogRead(turbidityPin);

  // 🚨 Buzzer condition (dirty water)
  if (turbidity < 800) {
    digitalWrite(buzzer, HIGH);  // ON
  } else {
    digitalWrite(buzzer, LOW);   // OFF
  }

  // 📺 LCD Display - Screen 1
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature);

  lcd.setCursor(0, 1);
  lcd.print("pH:");
  lcd.print(ph);

  delay(2000);

  // 📺 LCD Display - Screen 2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Turb:");
  lcd.print(turbidity);

  if (turbidity < 800) {
    lcd.setCursor(0, 1);
    lcd.print("Water: DIRTY");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Water: CLEAN");
  }

  delay(2000);

  // 🖥️ Serial Monitor (for checking)
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | pH: ");
  Serial.print(ph);
  Serial.print(" | Turbidity: ");
  Serial.println(turbidity);

  delay(1000);
}
