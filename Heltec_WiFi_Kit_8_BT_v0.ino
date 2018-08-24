/*
2* Bluetooh Basic: LED ON OFF - Avishkar
3* Coder - Mayoogh Girish
4* Website - http://bit.do/Avishkar
5* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
6* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
7* USB-SERIAL CH340 (COM23)
8* plug Tx-Rx after uploading

Result:
20180825 unable to control the led via BT, control from serial monitor is ok
*/
char data = 0;            //Variable for storing received data
//const int yLedPin = D11;
//const int gLedPin = D12;
const int gLedPin = D0;

void setup()
{
    Serial.begin(38400);   //Sets the baud for serial data transmission 
    //Serial.begin(57600);   //Sets the baud for serial data transmission                                                             
    //pinMode(yLedPin, OUTPUT);
    pinMode(gLedPin, OUTPUT);  //Sets digital pin 13 as output pin
}


void loop()
{   
    /*
    //
    digitalWrite(yLedPin,HIGH);
    delay(1000);
    digitalWrite(yLedPin,LOW);
    delay(1000);
    //
    */
       
   // 
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      //Serial.print("\n");        
      
      if(data == '1')              // Checks whether value of data is equal to 1
      {
      digitalWrite(gLedPin, HIGH);   //If value is 1 then LED turns ON
      Serial.println(" ON");
      }
      
      if(data == '0')         //  Checks whether value of data is equal to 0
      {     
       digitalWrite(gLedPin, LOW);    //If value is 0 then LED turns OFF
       Serial.println(" OFF");
      }
      //Serial.print("\n");
   }//if_loop 
   //
   
}//void_loop

