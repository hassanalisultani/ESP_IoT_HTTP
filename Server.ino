/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

IPAddress apIP(192,168,4,1);  // Defining a static IP address for the Server
String http_addr = "http://192.168.4.2";

String body = "";
String url = "";

String msgBody = "";

// Set web server port number to 80
//WiFiServer server(80);
WebServer server(80);
WiFiClient client;
HTTPClient http;


// handle requests at the root endpoint (http://xxx.xxx.xxx.xxx/)
void handleRoot() {
  Serial.println("Root page accessed by a client!");

// Respond with a mini HTML page
  server.send ( 200, "text/html", "<h1><b>Hi</b> There!</h1>");
}

void handleMessage(){
  
  // Check for valid request with a message (in the expected format)
  if(server.hasArg("body")){
    Serial.println("Message received from Client:");
    msgBody = server.arg("body");
    Serial.println(msgBody);

    // Generate and send back an acknowledgement response
    msgBody = "Hi, this is the Server. I got your message saying : " + msgBody;
    server.send ( 200, "text/plain", msgBody);
    delay(500);
  }
  // handle messages with invalid bodies
  else {
    Serial.println("Invalid message received");
    server.send ( 200, "text/plain", "Recevied a message without a body!");
  }

  Serial.println("-------------------------------------");
}

// handle invalid requests
void handleNotFound() {
  server.send ( 404, "text/plain", "404, No resource found");
}


void setup() {
  Serial.begin(115200);
  
  // Start the Access Point
  WiFi.softAP(ssid, password);
  // Serial messages with Access Point details
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  server.on ( "/", handleRoot );
  server.on ( "/message", handleMessage );
  server.onNotFound ( handleNotFound );
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  // Constantly listen for Client requests
  server.handleClient();
}

//
//  http.begin(client, "192.168.4.1");
//  
//  int httpResponseCode = http.GET();
//  if (httpResponseCode>0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
//    String payload = http.getString();
//    Serial.println(payload);
//  }
//  else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
//  }
//  delay(5000);
//  // Free resources
//  http.end();
//  
//  WiFiClient client = server.available();   // Listen for incoming clients
//
//  if (client) {                             // If a new client connects,
//    Serial.println("New Client.");          // print a message out in the serial port
//    String currentLine = "";                // make a String to hold incoming data from the client
//    while (client.connected()) {            // loop while the client's connected
//      if (client.available()) {             // if there's bytes to read from the client,
//        char c = client.read();             // read a byte, then
//        Serial.write(c);                    // print it out the serial monitor
////        header += c;
//        if (c == '\n') {                    // if the byte is a newline character
//          client.println("Recieved at ESP32..");
//        }
//          // if the current line is blank, you got two newline characters in a row.
//          // that's the end of the client HTTP request, so send a response:
////          if (currentLine.length() == 0) {
//            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//            // and a content-type so the client knows what's coming, then a blank line:
////            client.println("Recieved..");
////            client.println("Content-type:text/html");
////            client.println("Connection: close");
////            client.println();
//            
//            // turns the GPIOs on and off
////            if (header.indexOf("GET /26/on") >= 0) {
////              Serial.println("GPIO 26 on");
////              output26State = "on";
////              digitalWrite(output26, HIGH);
////            } else if (header.indexOf("GET /26/off") >= 0) {
////              Serial.println("GPIO 26 off");
////              output26State = "off";
////              digitalWrite(output26, LOW);
////            } else if (header.indexOf("GET /27/on") >= 0) {
////              Serial.println("GPIO 27 on");
////              output27State = "on";
////              digitalWrite(output27, HIGH);
////            } else if (header.indexOf("GET /27/off") >= 0) {
////              Serial.println("GPIO 27 off");
////              output27State = "off";
////              digitalWrite(output27, LOW);
////            }
//            
//            // Display the HTML web page
////            client.println("<!DOCTYPE html><html>");
////            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
////            client.println("<link rel=\"icon\" href=\"data:,\">");
//            // CSS to style the on/off buttons 
//            // Feel free to change the background-color and font-size attributes to fit your preferences
////            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
////            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
////            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
////            client.println(".button2 {background-color: #555555;}</style></head>");
//            
//            // Web Page Heading
////            client.println("<body><h1>ESP32 Web Server</h1>");
//            
//            // Display current state, and ON/OFF buttons for GPIO 26  
////            client.println("<p>GPIO 26 - State " + output26State + "</p>");
//            // If the output26State is off, it displays the ON button       
////            if (output26State=="off") {
////              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
////            } else {
////              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
////            } 
//               
//            // Display current state, and ON/OFF buttons for GPIO 27  
////            client.println("<p>GPIO 27 - State " + output27State + "</p>");
//            // If the output27State is off, it displays the ON button       
////            if (output27State=="off") {
////              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
////            } else {
////              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
////            }
////            client.println("</body></html>");
//            
//            // The HTTP response ends with another blank line
////            client.println();
//            // Break out of the while loop
////            break;
////          } else { // if you got a newline, then clear currentLine
////            currentLine = "";
////          }
////        } else if (c != '\r') {  // if you got anything else but a carriage return character,
////          currentLine += c;      // add it to the end of the currentLine
////        }
//      }
////      client.println("Recieved..");
//    }
//    // Clear the header variable
////    header = "";
//    // Close the connection
//    client.stop();
////    Serial.println("Client disconnected.");
////    Serial.println("");
//  }
//}
