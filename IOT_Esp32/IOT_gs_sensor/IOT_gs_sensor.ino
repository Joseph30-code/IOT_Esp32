#include "EEPROM.h"
#include <WiFiManager.h>
#include "FirebaseESP32.h"

// Declare the Firebase Data object in global scope

FirebaseData firebaseData;

/*
# the approximate moisture levels for the sensor reading
# 0 to 300 dry soil
# 300 to 700 humid soil
# 700 to 950 in water
*/
 
# define ledPin 15
# define sensorPin 36 
 
int trigger = 300; // set the level

#define EEPROM_SIZE 100

int Buzzer = 32;        // used for ESP32
int Gas_analog = 4;    // used for ESP32
int Gas_digital = 2;   // used for ESP32

void setup() {
  Serial.begin(115200);
       if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); 
    delay(1000000);
  }
  pinMode(Buzzer, OUTPUT);      
  pinMode(Gas_digital, INPUT);
  pinMode(13, INPUT); //Pin to Configure Wifi
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // turn off LED

   if(digitalRead(16)==HIGH)
   { 
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("AutoConnectAP","password");
    if(!res) {
        Serial.println("Failed to connect");
    } 
    else { 
        Serial.println("connected...yeey :)");
    }
      
   }

   Firebase.begin("URL", "API-KEY");

}

void loop() {
  int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);

  Serial.print("Gas Sensor: ");
  Serial.print(gassensorAnalog);
  Serial.print("\t");
  Serial.print("Gas Class: ");
  Serial.print(gassensorDigital);
  Serial.print("\t");
  Serial.print("\t");
  
  if (gassensorAnalog > 1000) {
    Serial.println("Gas");
     Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
    digitalWrite (Buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite (Buzzer, LOW) ;  //no tone
  }
  else {
    Serial.println("No Gas");
     Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
  }

  Serial.print("Moisture Sensor Value:");
Serial.println(analogRead(sensorPin)); // read the value from the sensor
if (analogRead(sensorPin) &gt;= trigger) 
{
    digitalWrite(ledPin, HIGH); // turn on the LED
    Firebase.setString(firebaseData,"/PATH/", "Status:Dry");
}
else
{
    digitalWrite(ledPin, LOW); // turn off LED
    Firebase.setString(firebaseData,"/PATH/", "Status:Normal");
}
delay(500);

}