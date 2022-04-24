#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "ESP32-Access-Point";    // Enter SSID here
const char* password = "123456789";  //Enter Password here

String http_addr = "http://192.168.4.1";

//const char* server = "192.168.4.1";


WiFiClient client;
// Initiate the HTTP call based on the received User Input
HTTPClient http;
ESP8266WebServer server(80);

String url = "";
String body = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  IPAddress IP = WiFi.localIP();
  Serial.print("IP address: ");
  Serial.println(IP);

  
  
//  String serverPath = serverName + "?temperature=24.37";
}

void loop() 
{
  
  while (WiFi.status() == WL_CONNECTED) {
    
    body = "http_message from NodeMCU";
    
    if((body.length()>0)) {
  
          url = http_addr + "/message?body=" + body;
          Serial.print("\n[HTTP] starting...\n");
          // configure traged server and url
          Serial.println(url);
          http.begin(client, url);
  
          Serial.print("Sending message - ");
          Serial.println(body);
          // start connection and send HTTP header
          int httpCode = http.GET();

        
          // httpCode will be negative on error
          if(httpCode > 0) {
              // Receive the Server response
              if(httpCode == HTTP_CODE_OK) {
                  Serial.print("Received Response\n");
                  String payload = http.getString();
                  Serial.println(payload);
                  Serial.flush();
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
  
          http.end();
    }
    delay(2000);
  }
}  
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
