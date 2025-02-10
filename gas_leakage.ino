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
  lcd.println(data);
  delay(1000);
 
  if ( data > 500) // The gas level above 500
  {
    SendMessage();
    Serial.println("Gas detection alarm");
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
    Serial.println("Gas Level Low");
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
  // List of phone numbers you want to send the SMS 
  String phoneNumbers[] = {
    "+91xxxxxxxxxx",  // First phone number
    "+91yyyyyyyyyy",  // Second phone number
    "+91zzzzzzzzzz",  // Third phone number
    // Add more numbers here as needed
  };

  // Message to send
  String message = "Warning Excess Gas Detected!!";

  Serial.println("SMS sending");

  // Loop through each phone number and send the SMS
  for (int i = 0; i < sizeof(phoneNumbers) / sizeof(phoneNumbers[0]); i++) {
    String phoneNumber = phoneNumbers[i];
    Serial.print("Sending SMS to: ");
    Serial.println(phoneNumber);

    // Set the GSM module to text mode
    mySerial.println("AT+CMGF=1");
    
    // Set the recipient phone number
    mySerial.print("AT+CMGS=\"");
    mySerial.print(phoneNumber);     // Phone number
    mySerial.println("\"");

    // Send the message text
    mySerial.println(message);

    // Send Ctrl+Z (ASCII code 26) to indicate the end of the message and send it
    mySerial.write(26); // Ctrl+Z character to send the message
    delay(1000);  // Wait a bit to ensure message is sent
  }

  Serial.println("All SMS messages sent.");
}
