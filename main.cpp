#include <Arduino.h>
#include <WiFi.h>

const char* ssid="Esp32-SoftAP";
const char* password="12345";

WiFiServer  server(80);
String header; //store the http request

  void WiFiStationConnected(WiFiEvent_t event,WiFiEventInfo_t info){
    Serial.println("Connected");
  
  }

void setup() {
Serial.begin(9600);
Serial.println("Setting AP (Access Point)…");
WiFi.softAP(ssid,password);
IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);
  
  server.begin();



WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
WiFi.begin(ssid,password); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
}

void loop() {
 WiFiClient client = server.available();//connecting client stations
 if (client) {                             // If a new client connects,
    Serial.println("New Client.");          
    String currentLine = "";                //  to hold incoming data from the client
    while (client.connected()) {            
      if (client.available()) {             // read incoming data
        char c = client.read();             // output each byte read
                Serial.write(c);                 
        header=header+c;
        if (c == '\n') {                    
          
          
          if (currentLine.length() == 0) {
            // HTTP headers code
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            client.println("<body><h1>ESP32 Web Server</h1>");
            
             client.println("</body></html>");
            client.println();//response
            
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    
    header = "";
    
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }


 while (WiFi.status() != WL_CONNECTED){
   WiFi.mode(WIFI_STA);   //station mode to reconnect when wifi problem
   WiFi.disconnect();        //reconnects to last access point
   Serial.println("Wifi has been disconnected ,check connection");
    
        WiFi.begin(ssid, password);
        Serial.println("Attempting to connect to  network, SSID: ");
        
        Serial.println(ssid);
 
       
       
         //WiFi_Status=WL_CONNECTED
       Serial.println("Wifi is connected!");
    }
  }
