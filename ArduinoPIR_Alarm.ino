// test code for PIR sensor 
// created by deba168 
// dated 25th july 2014

int pir_pin = 2; // PIR pin
int led_pin = 13;   // LED pin
int val = 0;             
 
void setup() 
{
  pinMode(pir_pin, INPUT);    
  pinMode(  led_pin, OUTPUT);     
  Serial.begin(9600);           
}
 
void loop()
{
  val = digitalRead(pir_pin);  
          
  if (val == HIGH) 
  {            
    digitalWrite( led_pin, HIGH); 
    Serial.println("MOTION DETECTED");
    delay(1000);
  }
  else
  {
    digitalWrite( led_pin,LOW);  
  }
}
