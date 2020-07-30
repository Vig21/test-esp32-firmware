#include "WiFi.h"
 
const char* ssid = "Warpdrive_EXT";
const char* password =  "$9Lithium";
 
void setup() {
 
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println("Ip address is:");
  Serial.println(WiFi.localIP());
  Serial.println("Hellp");
 
}
 
void loop() {
  while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.mode(WIFI_STA);   //station mode to reconnect when wifi problem
    WiFi.disconnect();        //reconnects to last access point
     Serial.println("Wifi has been disconnected ,check connection");
    delay(1000);
       WiFi.begin(ssid, password);
       Serial.println("Attempting to connect to  network, SSID: ");
        delay(5000);
        Serial.println(ssid);
 
       Serial.println("IP address: ");
       Serial.println(WiFi.localIP());
       
         //WiFi_Status=WL_CONNECTED
       Serial.println("Wifi is connected!");
    }
}

