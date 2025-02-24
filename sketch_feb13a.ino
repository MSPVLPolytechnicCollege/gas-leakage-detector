#include <LiquidCrystal.h>

// LCD pin configuration
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensor and output pins
const int gasSensor = A0;
const int buzzer = 13;
const int ledIndicator = 7;
const int led_Indicator = 8;

void setup() {
    Serial.begin(115200); // Start serial communication
    lcd.begin(16, 2); // Initialize LCD

    pinMode(gasSensor, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(ledIndicator, OUTPUT);
    pinMode(led_Indicator, OUTPUT);

    lcd.print("Gas Detector");
    lcd.setCursor(0, 1);
    lcd.print("Ready...");
    delay(2000);
    lcd.clear();
}

void loop() {
    int gasLevel = analogRead(gasSensor);  // Read gas sensor value
    Serial.println(gasLevel);  // Send data to Flask

    lcd.setCursor(0, 0);
    lcd.print("Gas Level: ");
    lcd.print(gasLevel);

    if (gasLevel > 500) {  
        lcd.setCursor(0, 1);
        lcd.print("Warning! Leak!");
        digitalWrite(ledIndicator, HIGH);
        tone(buzzer, 1000);
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Status: Normal ");
        digitalWrite(led_Indicator, HIGH);
        delay(500);
        digitalWrite(led_Indicator, LOW);
        delay(500);
        
        noTone(buzzer);
        digitalWrite(ledIndicator, LOW);
    }

    delay(1000);
    lcd.clear();
}
