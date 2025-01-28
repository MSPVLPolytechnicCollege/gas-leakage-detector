// This project is arduino based project which is used to Detect the Gas Leakage using MQ4 and send sms to moblie through SIM module.

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(9, 10);
 
int gasValue = A0; 
int data = 0;
const int buz = 13;
void setup()
{
  randomSeed(analogRead(0));
  mySerial.begin(9600); 
  Serial.begin(9600); 
  lcd.begin(16,2);
  pinMode(gasValue, INPUT);
  lcd.print (" Gas Leakage ");
  lcd.setCursor(0,1);
  lcd.print (" Detector Alarm ");
  delay(3000);
  lcd.clear();
  pinMode(buz, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}
 
void loop()
{
 
  data = analogRead(gasValue); // To detect gas level
  Serial.print("Gas Level: ");
  Serial.println(data);
  lcd.print ("Scanning GAS");
  lcd.setCursor(0,1);
  lcd.print("Gas Level: ");
  lcd.print(data);
  delay(1000);
 
  if ( data > 500) // The gas level above 500
  {
    SendMessage();
    Serial.print("Gas detection alarm");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas Level Exceed");
    lcd.setCursor(0,1);
    lcd.print("SMS Sent");
    delay(1000);
    tone(buz,1000);
    delay(1000);
    noTone(buz);
    delay(1000);
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
  }

  else // The gas level below 500
  {
    Serial.print("Gas Level Low");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gas Level Normal");
    delay(1000);
    digitalWrite(11, HIGH);
    delay(1000);
    digitalWrite(11, LOW);
    delay(1000);
  }
lcd.clear();
}
 
void SendMessage() 
{
  Serial.println("SMS sending");
  mySerial.println("AT+CMGF=1"); // Set the gas module in text mode
  delay(1000); 
  mySerial.println("AT+CMGS=\"+91900xxxxxxx\"\r"); 
  delay(1000);
  mySerial.println("Excess Gas Detected!!");
  delay(100);
  mySerial.println((char)26);
  delay(1000);
}
