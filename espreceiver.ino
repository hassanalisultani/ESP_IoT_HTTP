#include <ESP8266WiFi.h>

const char* ssid = "Coderatory_"; //"Applied Physics AP 5";
const char* password = "q1werty6068"; //"Blackrose2017";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Start the server
  server.begin();

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
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
  client.print("Message From NODEMCU");
  
  if (msg.endsWith("B1ON"))
  {
    Serial.println("Load 1 ON");
  }
  else if (msg.endsWith("B1OFF"))
  {
    Serial.println("Load 1 OFF");
  }
  else if (msg.endsWith("B2ON"))
  {
    Serial.println("Load 2 ON");
  }
  else if (msg.endsWith("B2OFF"))
  {
    Serial.println("Load 2 OFF");
  }
  else if (msg.endsWith("B3ON"))
  {
    Serial.println("Load 3 ON");
  }
  else if (msg.endsWith("B3OFF"))
  {
    Serial.println("Load 3 OFF");
  }
  else if (msg.endsWith("B4ON"))
  {
    Serial.println("Load 4 ON");
  }
  else if (msg.endsWith("B4OFF"))
  {
    Serial.println("Load 4 OFF");
  }
  else
  {
    Serial.println(msg);
  }
}
