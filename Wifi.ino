#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         
#include <EEPROM.h>

String IFTTT_KEY = "cmB-6qGrAEIMc6q-dvkcyV"; //replace this with your IFTTT applet key
int a=0;
const char* eventName  = "demo";
const char* IFTTT_URL = "maker.ifttt.com";

const char* ssid     = "CuriosityGym";
const char* password = "#3Twinkle3#";
void setup()
{
    pinMode(D7,INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
      
      
}

void loop()
{ 
  Serial.println(digitalRead(D7));
  if(digitalRead(D7)==LOW && a==0){
// Define the WiFi Client
       WiFiClient client;
       // Set the http Port
       const int httpPort = 80;

       // Make sure we can connect
       if (!client.connect(IFTTT_URL, httpPort))
          {
            return;
          }

       // We now create a URI for the request
       // String url = "/trigger/" + String(eventName) + "-"+String(eventCount)+ "/with/key/" + String(IFTTT_KEY);
       String url = "/trigger/" + String(eventName) + "/with/key/" + String(IFTTT_KEY);

       // Set some values for the JSON data depending on which event has been triggered
       IPAddress ip = WiFi.localIP();
       String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
       //String value_1 = "MH 37T 5770";
       //String value_2 = String(h);
       //String value_3 = "";
       


        // Build JSON data string
        String data = "";
        //data = data + "\n" + "{\"value1\":\"" + value_1 + "\"}"; //,"value2\":\""+ value_2 +"\"}";

        // Post the button press to IFTTT
        if (client.connect(IFTTT_URL, httpPort))
           {

             // Sent HTTP POST Request with JSON data
             client.println("POST " + url + " HTTP/1.1");
             Serial.println("POST " + url + " HTTP/1.1");
             client.println("Host: " + String(IFTTT_URL));
             Serial.println("Host: " + String(IFTTT_URL));
             client.println("User-Agent: Arduino/1.0");
             Serial.println("User-Agent: Arduino/1.0");
             client.print("Accept: *");
             Serial.print("Accept: *");
             client.print("/");
             Serial.print("/");
             client.println("*");
             Serial.println("*");
             client.print("Content-Length: ");
             Serial.print("Content-Length: ");
             client.println(data.length());
             Serial.println(data.length());
             client.println("Content-Type: application/json");
             Serial.println("Content-Type: application/json");
             client.println("Connection: close");
             Serial.println("Connection: close");
             client.println();
             Serial.println();
             client.println(data);
             Serial.println(data); 
           }
           a=1;
}
  delay(1000);
}
