/*
  ESP8266 BlinkWithoutDelay by Simon Peter
  Blink the blue LED on the ESP-01 module
  Based on the Arduino Blink without Delay example
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

int ledState = LOW;

unsigned long previousMillis = 0;
const long interval = 1000;
int curpin = 0;
void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    for(int i=0; i<4; i++)
    {
      if(i == curpin)
        digitalWrite(i, HIGH);
      else
        digitalWrite(i, LOW);
    }
    if(curpin < 3)
      curpin = curpin + 1;
    else
      curpin = 0;
    
  }
}
