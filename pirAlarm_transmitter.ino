//https://www.instructables.com/ARDUINO-WIRELESS-HOME-SECURITY-SYSTEM/
// Include VirtualWire library
#include <VirtualWire.h>

int led_pin = 13;
int transmit_pin = 12;
int pir_pin = 2;
int val = 0; 
int pir_state = LOW;

void setup()
{
   Serial.begin(9600);
   vw_set_tx_pin(transmit_pin);
   vw_setup(4000); // Transmission rate
   pinMode(led_pin, OUTPUT);
   pinMode(pir_pin,INPUT);
}
 
void loop()
{
  char msg[1] = {'0'};
  // Get sensor value
  val = digitalRead(pir_pin);
  // Change message if motion is detected
  if (val == 1)
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
