/*
//
WeMOS_IRremote_OK_v2

Source  http://www.esp8266learning.com/wemos-infrared-receiver-example.php
Library https://github.com/markszabo/IRremoteESP8266
Ref     https://forum.arduino.cc/index.php?topic=384530.0
   ___
  | X |   VCC = 3.3v
  | \ |   Picture is the front view of the IR Reciever
   ---    0 = FD30CF       5 = FDA857        
  | | |   1 = FD08F7       6 = FD6897
  | | |   2 = FD8877       7 = FD18E7
  1 2 3   3 = FD48B7       8 = FD9867
  O G V   4 = FD28D7       9 = FD58A7
  U N C   
  T D C


0 = 16593103 
1 = 16582903 
2 = 16615543 
3 = 16599223 
4 = 16591063 
5 = 16623703 
6 = 16607383 
7 = 16586983 
8 = 16619623 
9 = 16603303 

  
 //
*/


#include <IRremoteESP8266.h> 
#include <IRrecv.h>
#include <IRutils.h>

int RECV_PIN = D8; //an IR detector connected to D8
IRrecv irrecv(RECV_PIN);
decode_results results;


 
void setup()
{

  pinMode(D10,OUTPUT); //red    square led
  pinMode(D11,OUTPUT); //yellow square led
  pinMode(D12,OUTPUT); //green  square led
  
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
}


 
void loop() 
{

  
  if (irrecv.decode(&results)) 
  {
   
   serialPrintUint64(results.value,HEX);
   Serial.println(" ");

  
   if (results.value == 0xFD08F7)
   {
    int key = 1;
    //Red Square LED
    digitalWrite(D10,HIGH);
    delay(1000);
    digitalWrite(D10,LOW);
   }


   if (results.value == 0xFD8877)
   {
    int key = 2;
    //yellow square led
    digitalWrite(D11,HIGH);
    delay(1000);
    digitalWrite(D11,LOW);
   }


   if (results.value == 0xFD48B7)
   {
    int key = 3;
    //green square led
    digitalWrite(D12,HIGH);
    delay(1000);
    digitalWrite(D12,LOW);
   }
  
   
   
   irrecv.resume(); // Receive the next value
  }
  delay(100);

  
}//void_loop

