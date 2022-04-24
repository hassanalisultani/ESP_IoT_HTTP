/* Server
*  We write the server first because we need its IP address
*/

#include <WiFi.h>
#include <WiFiClient.h> 
#include <WebServer.h>

const char* ssid = "ESP32-Access-Point";       // ssid of server (Access Point (AP))
const char* password = "123456789";        // password of server (Access Point (AP))
int port = 80;                // port number
WiFiServer server(80);            //Service Port

int ledPin = 2; // GPIO2 of Server ESP8266
byte ip[]= {192,168,4,2};

void setup() 
{
    delay(1000);
    Serial.begin(115200);    // to use tools->serial monitor

    pinMode(ledPin, OUTPUT);   // set GPIO 2 as an output

    WiFi.mode(WIFI_AP_STA);  // Set WiFi to AP and station mode

    // Connect to the WiFi network
    Serial.println();
    Serial.print("Connecting to: ");
    Serial.println(ssid);
    WiFi.softAP(ssid, password);
    
    // Display the server address
    Serial.print("Connected, My address: ");
    Serial.print("http://");
    Serial.print(WiFi.softAPIP());
    Serial.println("/");

    // Tell the server to begin listening for incoming connections
    server.begin();
    Serial.println("Server listening for incoming connections");
}  

void loop() 
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) // if not available, return
    {
        return;
    }
    else
    {

    // Wait until the client sends some data
    Serial.println();
    Serial.println("Client connected");
    while(!client.available())
    {
        delay(1);
    }

    // Read the request
    String request = client.readStringUntil('\r');  
    Serial.print("Request = ");
    Serial.println(request);

    if (request.indexOf("/ON/") != -1) 
    {
        digitalWrite(ledPin, HIGH); // turn LED on
    } 
    if (request.indexOf("/OFF/") != -1)
    {
        digitalWrite(ledPin, LOW); // turn LED off
    }
    client.flush();
    server.stop();
    }
    
    delay(5000);
    if (client.connect(ip, port))
    {
      client.println("Sending from esp32");
      Serial.println("Client disconnected");
      server.begin();
    }
}



//#include <WiFi.h>
//#include <WiFiClient.h>
//
//// Replace with your network credentials
//const char* ssid     = "ESP32-Access-Point";
//const char* password = "123456789";
//
//IPAddress apIP(192,168,4,1);  // Defining a static IP address for the Server
//
//// Set web server port number to 80
//WiFiServer server(80);
//WiFiClient client;
//
//void setup() {
//  Serial.begin(115200);
//  
//  // Start the Access Point
//  WiFi.softAP(ssid, password);
//  // Serial messages with Access Point details
//  IPAddress myIP = WiFi.softAPIP();
//  Serial.print("AP IP address: ");
//  Serial.println(myIP);
//}
//
//void loop() 
//{
//  WiFiClient client = server.available();   // Listen for incoming clients
//  if (client) {                             // If a new client connects,
//    Serial.println("New Client.");          // print a message out in the serial port
//    String currentLine = "";                // make a String to hold incoming data from the client
//    while (client.connected()) {            // loop while the client's connected
//      if (client.available()) {             // if there's bytes to read from the client,
//      char c = client.read();             // read a byte, then
//      Serial.write(c);                    // print it out the serial monitor
////      header += c;
//      if (c == '\n') {                    // if the byte is a newline character
//        client.println("Recieved at ESP32..");
//      }
//      }
//    }
//  }
//  client.stop();
//}

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
//          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
//            client.println("Recieved..");
//            client.println("Content-type:text/html");
//            client.println("Connection: close");
//            client.println();
            
            // turns the GPIOs on and off
//            if (header.indexOf("GET /26/on") >= 0) {
//              Serial.println("GPIO 26 on");
//              output26State = "on";
//              digitalWrite(output26, HIGH);
//            } else if (header.indexOf("GET /26/off") >= 0) {
//              Serial.println("GPIO 26 off");
//              output26State = "off";
//              digitalWrite(output26, LOW);
//            } else if (header.indexOf("GET /27/on") >= 0) {
//              Serial.println("GPIO 27 on");
//              output27State = "on";
//              digitalWrite(output27, HIGH);
//            } else if (header.indexOf("GET /27/off") >= 0) {
//              Serial.println("GPIO 27 off");
//              output27State = "off";
//              digitalWrite(output27, LOW);
//            }
            
            // Display the HTML web page
//            client.println("<!DOCTYPE html><html>");
//            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
//            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
//            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
//            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
//            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
//            if (output26State=="off") {
//              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
//            } else {
//              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
//            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
//            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
//            if (output27State=="off") {
//              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
//            } else {
//              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
//            }
//            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
//            client.println();
            // Break out of the while loop
//            break;
//          } else { // if you got a newline, then clear currentLine
//            currentLine = "";
//          }
//        } else if (c != '\r') {  // if you got anything else but a carriage return character,
//          currentLine += c;      // add it to the end of the currentLine
//        }
//      }
//      client.println("Recieved..");
//    }
    // Clear the header variable
//    header = "";
    // Close the connection
//    client.stop();
//    Serial.println("Client disconnected.");
//    Serial.println("");
