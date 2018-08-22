/*
 * Heltec WiFi Kit 8 
 * https://www.facebook.com/photo.php?fbid=704156653273977&l=676a0f55ab
 * https://robotzero.one/heltec-wifi-kit-8/
 * https://www.aliexpress.com/item/Aihasd-0-91-Inch-OLED-Display-ESP8266-Wifi-Kit8-Development-Board-for-Arduino-NodeMCU-128X32-White/32829791335.html
 * In the Arduino IDE, in the Tools > Board menu choose NodeMCU 1.0 (ESP-12E Module)
 *       
 *                                 --|USB|--   
 *                                |  -----  |
 *                                |         |
 *                                |         | 
 *                    GND         +         +   GND
 *                    5v          +         +   5v
 *                    3V3         +         +   3V3
 *                    GND         +         +   GND
 *             CS2|GPIO-00(*) [D2]+[0]      +   CTS
 *  ^OLED_SDA|TXD1|GPIO-02(*) [D3]+[2]      +   DTR    
 *    CS|RST0|TXD2|GPIO-15    [D8]+[15]  [5]+ (*)GPIO-05|SCL    
 *  MOSI|CTS0|RXD2|GPIO-13(*) [D7]+[13]  [1]+ (*)GPIO-01|TXD0|CS1    
 *            MISO|GPIO-12(*) [D6]+[12]  [3]+ (*)GPIO-03|RXD0    
 *   ^OLED_SCL|CLK|GPIO-14(*)     +[14]     +   RST
 *                 GPIO-16    [D0]+[16]  [4]+ (*)GPIO-04|SDA|OLED_RST^
 *                 ADC        [A0]+         +   RST
 *                                |         |
 *                                |         |
 *                                | antenna | 
 *                                |_________| 
 * 
 * Only ADC is the analog pin and max voltage is 3V3
 * Three pins marked with ^(OLED) are for OLED
 * (*) PWM/1WIRE/I2C
 * Interrupt/pwm/I2C/1WIRE are supported on all IO except D0
 * Logic level is 3V3 on all IO
 * [x]arduino pin
*/


int pinLedGreen = D0;

void setup() {
  // put your setup code here, to run once:
    pinMode(pinLedGreen,OUTPUT);  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinLedGreen,HIGH);
  delay(1000);
  digitalWrite(pinLedGreen,LOW);
  delay (1000);
}
