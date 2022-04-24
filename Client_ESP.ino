/*  Client
*   This client will turn the LED on or off every 5 seconds
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiServer server(80);            //Service Port

const char* ssid = "ESP32-Access-Point";   // ssid of access point (Server)
const char* password = "123456789";    // password of access point (Server)
int port = 80;                // port number

byte ip[]= {192,168,4,1};

int LEDstatus = 0;
int a = 2;

//WiFiClient client;  // Declare client
WiFiClient client = server.available();

void setup() 
{
    Serial.begin(115200);
    delay(10);

    WiFi.mode(WIFI_STA);  // set mode to station (client)

    // Connect to wiFi
    Serial.println(); Serial.println();
    Serial.println("CONNECTING TO WiFi");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");  // print dots until connection
    }
    Serial.println();
    Serial.println("WiFi CONNECTED");
    Serial.println(WiFi.localIP());
}

void loop() 
{
  if(!client && a==2)
  {
    // Connect client to server
    Serial.println("CONNECTING CLIENT TO SERVER");
    
    if (client.connect(ip, port))
    {
        Serial.println("CONNECTED_Sending Data");
        // Send message to control the LED
        if (LEDstatus == 0)
        {
          client.println("/OFF/");
          Serial.println("LED OFF");
          LEDstatus = 1;
          a = 1;
        }
        else
        {
          client.println("/ON/");
          Serial.println("LED ON");
          LEDstatus = 0;
          a = 1;
        }
      
      client.println();
    }
    else 
    {
      Serial.println("CONNECTION FAILED");
    }
    client.flush();
  }
  
  if (a == 1)
  {
    server.begin();
    WiFiClient client = server.available();

      // Read the request
      String request = client.readStringUntil('\r');
      Serial.println();

      client.flush();
      delay(1);
      server.stop();
      
      if(client)
      {
        Serial.print("Request = ");
        Serial.println(request);
        a = 2;
        request = "";
        Serial.println();
      }
  }
}



//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
////#include <ESP8266WebServer.h>
//
///*Put your SSID & Password*/
//const char* ssid = "ESP32-Access-Point";    // Enter SSID here
//const char* password = "123456789";  //Enter Password here
//
//String http_addr = "http://192.168.4.1";
//
////const char* server = "192.168.4.1";
//
//
//WiFiClient client;
//// Initiate the HTTP call based on the received User Input
//HTTPClient http;
////ESP8266WebServer server(80);
////
////String url = "";
////String body = "";
//
//void setup() {
//  Serial.begin(115200);
//  delay(1000);
//
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//
//  //connect to your local wi-fi network
//  WiFi.begin(ssid, password);
//
//  //check wi-fi is connected to wi-fi network
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//
//  IPAddress IP = WiFi.localIP();
//  Serial.print("IP address: ");
//  Serial.println(IP);
//
//  
//  
////  String serverPath = serverName + "?temperature=24.37";
//}
//
//void loop() 
//{
//  
//  while (WiFi.status() == WL_CONNECTED) {
//  
//  if (client.connect(server,80))
//  { 
////    String getStr = _getLink;
//
////    client.print("GET "+getStr+"\n");
//    client.print("Sending from NodeMCU\n");
//    
////    while(client.available()){
////      char c = client.read();
////      Serial.print(c);
////    }
////    Serial.println("");
//  }
//  delay(1000);
//  while(client.available()){
//    char c = client.read();
//    Serial.print(c);
//  }
//  Serial.println("");
//  client.stop();
////  Serial.println("Waiting…");
////  delay(10000);
//}
//}
