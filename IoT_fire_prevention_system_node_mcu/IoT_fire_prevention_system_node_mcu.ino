#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <ArduinoJson.h>

#include <SoftwareSerial.h>
SoftwareSerial noed_mcu(D6,D5);


#define FIREBASE_HOST "vuejshttp-55833.firebaseio.com"
#define FIREBASE_AUTH "NrS5gRlX8VFJU5rcv7s2scm4lz7O75QrbVgtWdYJ"
#define WIFI_SSID "THE DEVELOPER"
#define WIFI_PASSWORD "MANAGEMENT2"

 float data1;
 float data2;
 //This are dummy values to test, this data should come from outside 
 int flame = 46;
 float gas_level = 78; 
 int temp = 498;
 int humidity = 56;

 boolean development = false; // set this value to true during development 
 
void setup() {
  // Initialize Serial port
  if(development){
  Serial.begin(9600);
  noed_mcu.begin(9600);
  while (!Serial) continue;
  } 
   // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("gas_level",gas_level );
  Firebase.set("flame_leve", flame);
  Firebase.set("temp", temp);
  Firebase.set("humidity", humidity);
 
}

 
void loop() {
 StaticJsonBuffer<1000> jsonBuffer; // defines buffer size
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
 
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
//  Serial.print("Data 1 ");
//  Serial.println("");
    data1=root["data1"];
    Firebase.set("gas_level", data1);
//  Serial.print(data1);
//  Serial.print("   Data 2 ");
//  data2=root["data2"];
//  Serial.print(data2);
//  Serial.println("");
  delay(2000);

  
}
