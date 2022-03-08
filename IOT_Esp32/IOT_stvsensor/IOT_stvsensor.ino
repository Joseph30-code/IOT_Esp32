#include "EEPROM.h"
#include <WiFiManager.h>
#include "FirebaseESP32.h"

//3. Declare the Firebase Data object in global scope

FirebaseData firebaseData;

#define EEPROM_SIZE 100

int val = 0;

void setup() {
     if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); 
    delay(1000000);
  }

//Initialize the pins
  Serial.begin(115200);
  Serial.println();
  pinMode(13, INPUT); //Pin to Configure Wifi
  pinMode(SENSOR_PIN, INPUT);
  pinMode(SENSOR_PIN1, INPUT);
  pinMode(SENSOR_PIN2, INPUT);
  pinMode(SENSOR_PIN3, INPUT);
  pinMode(SENSOR_PIN4, INPUT);
  pinMode(SENSOR_PIN5, INPUT);
  pinMode(SENSOR_PIN6, INPUT);

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

/*Check if WiFi is available*/    
if(WiFi.status() == WL_CONNECTED)
   { 
 
   int vibsen=digitalRead(SENSOR_PIN);//For vibration sensor
   if(vibsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }

   int tiltsen=digitalRead(SENSOR_PIN1);//For Tilt sensor
   if(tiltsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }

      int soundsen=digitalRead(SENSOR_PIN2);//For Sound sensor
   if(soundsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }

         int rainsen=digitalRead(SENSOR_PIN3);//For Rain sensor
   if(rainsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }  

   int ldrsen=digitalRead(SENSOR_PIN4);//For LDR sensor
   if(ldrsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }  

     int motionsen=digitalRead(SENSOR_PIN5);//For Motion sensor
   if(motionsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }   
      
       int irsen=digitalRead(SENSOR_PIN6);//For IR sensor
   if(irsen==1){
      Firebase.setString(firebaseData,"/PATH/", "Status:HIGH");
   }else{
        Firebase.setString(firebaseData,"/PATH/", "Status:LOW");
   }  

  delay(1500);
    }
    else 
         { 
          Serial.println(firebaseData.errorReason());
          delay(4000);
         }
         

}

