// Include VirtualWire library
#include <VirtualWire.h>
 
// Pins definition
const int led_pin = 13;//connect LED to Pin 13 of Arduino
const int receive_pin = 12;//connect 433Mhz RF Receiver module Data pin  to Pin 12 of Arduino
int Buzzer_pin = 10; //connect Buzzer to Pin 10 of Arduino
 
void setup()
{
   Serial.begin(9600); // Debugging only
   // Initialise the IO and ISR
   vw_set_rx_pin(receive_pin);
   vw_setup(4000); // Transmission rate
   // Start the receiver PLL
   vw_rx_start();
   // Set LED pin and Buzzer
   pinMode(led_pin, OUTPUT);// set led_pin as an OUTPUT
   pinMode(Buzzer_pin, OUTPUT);// set Buzzer_pin as an OUTPUT
}
 
void loop()
{
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
 
   // Check if a message was received
    if (vw_get_message(buf, &buflen)) 
    {
      if(buf[0]=='1')
      {
      Serial.println("Motion detected!");
      digitalWrite(led_pin,1);
      playTone(300, 160);// calling the play_Tone function with frequency-300 for 160 ms
      delay(150);
      }  
     if(buf[0]=='0')
     {
     Serial.println("Motion ended!");
     digitalWrite(led_pin,0);
     playTone(0, 0);// No play_Tone
     delay(300); 
     }
   }
}

// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) // user defined function(playTOne) for Play Buzzer 
{
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) 
    {
    digitalWrite(Buzzer_pin,HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(Buzzer_pin, LOW);
    delayMicroseconds(period / 2);
    elapsed_time += (period);
   }
}
