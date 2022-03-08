#include "EEPROM.h"
#include <WiFiManager.h>
#include "FirebaseESP32.h"

//3. Declare the Firebase Data object in global scope

FirebaseData firebaseData;

#define EEPROM_SIZE 100

float duration_us, distance_cm;

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
 
  
  int state = digitalRead(SENSOR_PIN);

  // print state to Serial Monitor
  Serial.println(state);

  if(state==1){
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
