//https://www.instructables.com/ARDUINO-WIRELESS-HOME-SECURITY-SYSTEM/
// Include VirtualWire library
#include <VirtualWire.h>

int led_pin = 13;// //connect LED to Pin 13 of Arduino
int transmit_pin = 12;//connect RF433 data to Pin 12 of Arduino
int pir_pin = 2;//connect PIR sensor signal pin to Pin 2 of Arduino
int btn_pin = 3;//connect Button to Pin 3 of Arduino
int pir_val = 0; // variable for store the status of PIR sensor
int btn_val = 0;// variable for store the status of push button
int pir_state = LOW;//set LOW the initial value
int btn_state = LOW;//set LOW the initial value
void setup()
{
   Serial.begin(9600);// set baud rate 9600 for serial communication
   vw_set_tx_pin(transmit_pin);
   vw_setup(4000); // Transmission rate
   pinMode(led_pin, OUTPUT);//Initilized pin 13 as an OUTPUT
   pinMode(pir_pin,INPUT);//Initilized pin 2 as an INPUT
   pinMode(btn_pin,INPUT);//Initilized pin 3 as an INPUT
}
 
void loop()
{
  char msg[1] = {'0'};
  // Get sensor value
  pir_val = digitalRead(pir_pin);// variable pir_val will store the value of pir_pin(2)
  btn_val = digitalRead(btn_pin);// variable btn_val will store the value of btn_pin(3)
  // Change message if motion is detected
  if (pir_val || btn_val == 1)
  {
      msg[0] = '1';
      digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
      vw_send((uint8_t *)msg, 1);
      vw_wait_tx(); // Wait until the whole message is gone
      if (pir_state == LOW) 
      {
      Serial.println("Motion detected!");
      pir_state = HIGH;
      }
   }
 else
 {
   msg[0] = '0';
   digitalWrite(led_pin, LOW);
   vw_send((uint8_t *)msg, 1);
   vw_wait_tx(); // Wait until the whole message is gone
   if (pir_state == HIGH)
   {
      Serial.println("Motion ended!");
      pir_state = LOW;
   }
  }
}
