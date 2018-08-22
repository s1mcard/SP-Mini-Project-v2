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
 [vi] Picture: https://www.facebook.com/photo.php?fbid=699102057112770&l=abd6baaafc
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
 
 
http://www.esp8266learning.com/wemos-d1-esp8266-based-board.php
Pin  Function  ESP-8266 Pin
D0      RX        GPIO3
D1      TX        GPIO1
D2      IO        GPIO16
D3(D15) IO,SCL    GPIO5
D4(D14) IO,SDA    GPIO4
D5(D13) IO,SCK    GPIO14
D6(D12) IO,MISO   GPIO12
D7(D11) IO,MOSI   GPIO13
D8  IO,Pull-up    GPIO0
D9  IO,pull-up, BUILTIN_LED GPIO2
D10 IO,pull-down,SS GPIO15
A0  Analog Input  A0
 
 */
 //[A]////////////////////////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
 
const char* ssid = "12-219";
const char* password = "12348765ABC";
  
WiFiServer server(80);
 
//[B]////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200);
  delay(10);
 
  //const int ledPin = D5;     //To deleted in next release aftering testing
  //pinMode(ledPin, OUTPUT);   //To deleted in next release aftering testing
  //digitalWrite(ledPin, LOW); //To deleted in next release aftering testing 
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  
  Serial.println("WeNOS_IP_ledv3.ino");
  Serial.println("GitHub version 3c -added pir hc-sr501/505 ");
  Serial.println("GitHub version 3d -added Active Buzzer - A3P5 - pending testing");
  
    
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
  f01_wifiLed ();
 f02_idr ();
 f03_pir ();
  
} //void_loop
 //[D]////////////////////////////////////////////////////////////////////////////////////
 //[D1-F01]
void  f01_wifiLed () 
{
 // Picture of the pinout of the WeMos D1 R1 
 //https://www.facebook.com/photo.php?fbid=699102057112770&l=abd6baaafc
  
  const int ledPin = D5;
  pinMode(ledPin, OUTPUT);
 
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
  client.println("Click <a href=\"/LED=ON\">Turn  ON</a> the LED on pin 5<br>");
  client.println("Click <a href=\"/LED=OFF\">Turn OFF</a> the LED on pin 5<br>");
  client.println("</html>");
 
  delay(10);
  Serial.println("Client disconnected");
  Serial.println("");
//Commented off on 17-Aug-2018 22:58
} //f01
 //[D01-f02]
void f02_idr ()
{
//http://www.esp32learning.com/code/esp32-and-ldr-example.php
//This is a 5v sensor  
//Using 2Kohm + 1Kohm resistor low level the voltage from IDR to A0
   //To be tested in next release
  int idrReading;
  int idrPin = A0;
  int idrLed = D2
  pinMode (idrLed,OUTPUT);
    
  idrReading = analogRead(idrPin); // read analog input pin 0
  Serial.print(idrReading, DEC); // prints the value read
  Serial.print(" \n"); // prints a space between the numbers
  delay(1000); // wait 100ms for next reading
   //idrReading is greater than 500 when block completely
  //idrReading is less    than 150 when not blocked
  //idrReading sensitivity is adjustable
   if (idrReading > 400)
  { 
    digitalWrite (idrLed,HIGH);
    f04_activeBuzzer (); //To be tested in next release
  }
   if (idrReading < 200)
  { 
    digitalWrite (idrLed,LOW);
  }
   
}//f02  
 //[D01-f03]
void f03_pir ()  
{
    //To be tested with a working pir
    //Source: https://www.elecrow.com/wiki/index.php?title=HC-SR505_Mini_PIR_Motion_Sensor
    //Source: PIR http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
    
    boolean pirReading;
    const int pirPin = D3;
    pinMode(D3,INPUT);
     const int pirLed = D4;
    pinMode(pirLed,OUTPUT);
    digitalWrite(pirLed,LOW);
    
    pirReading = digitalRead(pirPin);  
    Serial.println("The PIR recieves a ");
    Serial.print(pirReading);
    Serial.println(" ");
    
    if(pirReading == 1)  
    {
      Serial.println("PIR is high.");
      digitalWrite(pirLed,HIGH);
      f04_activeBuzzer (); //To be tested in next release
    }
     if(pirReading == 0)  
    {
      Serial.println("PIR is low");
      digitalWrite(pirLed,LOW);
    }
    
    delay(100);
}//f03
 void f04_activeBuzzer ()
{
  //source: https://www.sunfounder.com/learn/sensor_kit_v1_for_Arduino/lesson-12-buzzer-sensor-kit-v1-for-arduino.html
  //source: https://www.circuitar.com/projects/controlling-the-buzzer/
   //This is the one i am using
  //source: https://www.ebay.com/itm/metal-active-buzzer-module-low-trigger-buzzer-control-board-for-arduino-A3P5-/253361059935
  
  
  int aBuzzerPin = D6;
  int aBuzzerPower = D7;
  pinMode(aBuzzerPin,OUTPUT);
  pinMode(aBuzzerPower,OUTPUT);
  
  digitalWrite(aBuzzerPower,HIGH);
  digitalWrite(aBuzzerPin,HIGH);
  delay(1000);
  digitalWrite(aBuzzerPin,LOW);
  delay(1000);
   digitalWrite(aBuzzerPower,LOW);
  
  
}//void_f04_activeBuzzer
 //[D01-100]
void blinkLED () 
{
  //For testing the board to ensure it is working
  
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
 //[END]/////////////////////////////////////////////////////////////////////////////////
//Appendix
// [01] WeMos D1 R1 Pinout https://www.facebook.com/photo.php?fbid=699102057112770&l=abd6baaafc
// [02] IDR Pinout         https://www.facebook.com/photo.php?fbid=699688150387494&l=8db126e1e1
// [03] PIR HC-SR505 https://www.elecrow.com/wiki/index.php?title=HC-SR505_Mini_PIR_Motion_Sensor
// [04] PIR HC-SR501 http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
// [05] Active Buzzer A3P5 https://www.ebay.com/itm/metal-active-buzzer-module-low-trigger-buzzer-control-board-for-arduino-A3P5-/253361059935
