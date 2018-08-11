#include <hcsr04.h>

#define TRIG_PIN 6
#define ECHO_PIN 10

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN);

void setup(){
    Serial.begin(9600);
}

void loop() {

    // Output the distance in mm
    Serial.println(hcsr04.distanceInMillimeters());
    if(hcsr04.distanceInMillimeters() > 100 && hcsr04.distanceInMillimeters() < 1000)
    {
      tone(4, 3000, 50000);
      delay(50000);
    }

    // Output information about the device, driver, and distance in Bifrost JSON format
    //Serial.println(hcsr04.ToString());

    delay(20);
}
