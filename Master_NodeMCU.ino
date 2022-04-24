#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Coderatory_";       // ssid of router
const char* password = "q1werty6068";        // password of router
const char* ap_ssid = "ESP32-Access-Point";       // ssid of server (Access Point (AP))
const char* ap_password = "123456789";        // password of server (Access Point (AP))
WiFiServer server(80);            //Service Port
HTTPClient http;    //Declare object of class HTTPClient

//Pin connected to ST_CP of 74HC595
int latchPin = D6;
//Pin connected to SH_CP of 74HC595
int clockPin = D7;
//Pin connected to DS of 74HC595
int dataPin = D5;

int data = 0;
int L1 = 0;
int L2 = 0;
int L3 = 0;
int L4 = 0;

void shift()
{
  Serial.println(data);
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, data);
  digitalWrite(latchPin, HIGH);
}

void setup() 
{
  Serial.begin(115200);    // to use tools->serial monitor
  // Begin Access Point
  WiFi.mode(WIFI_AP_STA);  // Set WiFi to AP and station mod
  WiFi.softAP(ap_ssid, ap_password);
  // Connect to the WiFi network
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("IP address for network ");
  Serial.print(ap_ssid);
  Serial.print(" : ");
  Serial.println(WiFi.softAPIP());
  
  // Start the server
  server.begin();
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  shift();
}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the message
  String msg = client.readString();
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  if (msg.endsWith("R1"))
  {
    if (msg.endsWith("B1ONR1"))
    {
      if (L1 == 0)
      {
        Serial.println("Load 1 ON");
        client.print("Load 1 ON");
        data = data + 1;
        shift();
        L1 = 1;
      }
    }
    else if (msg.endsWith("B1OFFR1"))
    {
      if (L1 == 1)
      {
        Serial.println("Load 1 OFF");
        client.print("Load 1 OFF");
        data = data - 1;
        shift();
        L1 = 0;
      }
    }
    else if (msg.endsWith("B2ONR1"))
    {
      if (L2 == 0)
      {
        Serial.println("Load 2 ON");
        client.print("Load 2 ON");
        data = data + 2;
        shift();
        L2 = 1;
      }
    }
    else if (msg.endsWith("B2OFFR1"))
    {
      if (L2 == 1)
      {
        Serial.println("Load 2 OFF");
        client.print("Load 2 OFF");
        data = data - 2;
        shift();
        L2 = 0;
      }
    }
    else if (msg.endsWith("B3ONR1"))
    {
      if (L3 == 0)
      {
        Serial.println("Load 3 ON");
        client.print("Load 3 ON");
        data = data + 4;
        shift();
        L3 = 1;
      }
    }
    else if (msg.endsWith("B3OFFR1"))
    {
      if (L3 == 1)
      {
        Serial.println("Load 3 OFF");
        client.print("Load 3 OFF");
        data = data - 4;
        shift();
        L3 = 0;
      }
    }
    else if (msg.endsWith("B4ONR1"))
    {
      if (L4 == 0)
      {
        Serial.println("Load 4 ON");
        client.print("Load 4 ON");
        data = data + 8;
        shift();
        L4 = 1;
      }
    }
    else if (msg.endsWith("B4OFFR1"))
    {
      if (L4 == 1)
      {
        Serial.println("Load 4 OFF");
        client.print("Load 4 OFF");
        data = data - 8;
        shift();
        L4 = 0;
      }
    }
    else
    {
      String ab = msg.substring(msg.length()-5, msg.length()-2);
      int slider = ab.toInt();
      Serial.println(slider);
    }
  }
  else if (msg.endsWith("R2"))
  {
    Serial.println("Sending command to Room2");
  }
}
