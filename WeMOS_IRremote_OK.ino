/*
//

Source  http://www.esp8266learning.com/wemos-infrared-receiver-example.php
Library https://github.com/markszabo/IRremoteESP8266
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

  
 //
*/


#include <IRremoteESP8266.h> 
#include <IRrecv.h>
#include <IRutils.h>

int RECV_PIN = D8; //an IR detector connected to D4
IRrecv irrecv(RECV_PIN);
decode_results results;
 
void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
}


 
void loop() {
  if (irrecv.decode(&results)) 
  {
   Serial.println(RECV_PIN);
   serialPrintUint64(results.value, HEX);

   if (results.value == 'FD58A7')
   {
    digitalWrite(D9,HIGH);
    delay (5000);
    digitalWrite(D9,LOW);
   }

   
   
   irrecv.resume(); // Receive the next value
  }
  delay(100);

  
}
