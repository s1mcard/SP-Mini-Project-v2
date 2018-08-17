/*
[i]Disclaimer: 
This is a cut and paste from various sources of code for a school project.
Not all the codes are written from scratch.

[ii] What does this sketch do ?
It connects to an AP and uses the ip that is allocated to turn on/off an LED connected on pin 5

[iii] Selection for WeMOS D1 R1 when using Android Studio 
USB-SERIAL CH340 (COM23)

[iv] The output on http://192.168.2.2 (Example)
-----------------------------------------------
Led pin is now: On
Click here turn the LED on pin 5 ON
Click here turn the LED on pin 5 OFF
-----------------------------------------------

[v] Notes:
[N1] The pinout of WeMos D1 R2 is different
[N2] Some pictures of the WeMos D1 R1 also has different pin out
[N3] The pinout below is a "picture" of my actual WeMos D1 R1
[N4] All pins are rated 3.3v


[vi] Picture: https://www.facebook.com/photo.php?fbid=699102057112770&set=p.699102057112770&type=3&theater


                   ___/LED\__________
                  |                  |
  __________      |             __   |            ___ 
 |          +-+-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+    \
 |          D D - G D D D D D D  D D D D D D D D     \    
 |          1 1   N 1 1 1 1 0 0  0 0 0 0 0 0 0 0      \_   
 | ----     5 4   D 3 2 1 0 9 8  7 6 5 4 3 2 1 0        |
 | USB |    -------------------  ---------------        |
 | ----     S S - - S M M S T -  D D D D D - - -        |
 |          C D - - C I O S X    0 1 1 1 1              |
 |          L A - - K S S   1    1 2 3 4 5              |
 |                    O I                               |
 |          -------------------  ---------------        |
 |                               M M S S S -T R         |
 |                               O I C D C  X X         | 
 |                               S S K A L              |
 |                               I O                    |
 |                                                      |
 |                                                      |
 |                                                      |
 |                R 3                                   |
 |--------        E .   G G V                           |
PowerJack |     5 S 3 5 N N I    A                      |
 |--------    - v T v v D D N    0 - - - - -            /
 |____________+-+-+-+-+-+-+-+____+-+-+-+-+-+___________/

*/


//[A]////////////////////////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
 
const char* ssid = "12-219";
const char* password = "12348765123";

 
int ledPin = D5;
WiFiServer server(80);
 
//[B]////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("GitHub version - WeNOS_IP_ledv3.ino");
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}//f01
 
//[C]////////////////////////////////////////////////////////////////////////////////////
void loop() {

 f01_connectWifi ();
 
 /*
 //Commented off on 17-Aug-2018 22:58
 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("SSID is ");
  client.print(ssid); 
  client.println("<br>");

  client.print("IP is ");
  client.print(WiFi.localIP());
  client.println("<br>");
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  
  client.println("<br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
  client.println("</html>");
 
  delay(10);
  Serial.println("Client disconnected");
  Serial.println("");
//Commented off on 17-Aug-2018 22:58
*/

} //void

//[D]////////////////////////////////////////////////////////////////////////////////////
//[D1]
void blinkLED () {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}

//[D2]
void  f01_connectWifi () {
 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  
 if (request.indexOf("/LED=ON") != -1) 
 {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
 
 if (request.indexOf("/LED=OFF") != -1)
 {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("SSID is ");
  client.print(ssid); 
  client.println("<br>");

  client.print("IP is ");
  client.print(WiFi.localIP());
  client.println("<br>");
  client.print("Led pin is now: ");
   
  if(value == HIGH) 
  {
    client.print("On");  
  } 
 else 
 {
    client.print("Off");
  }
  
  client.println("<br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
  client.println("</html>");
 
  delay(10);
  Serial.println("Client disconnected");
  Serial.println("");
//Commented off on 17-Aug-2018 22:58


} 

//[END]/////////////////////////////////////////////////////////////////////////////////
