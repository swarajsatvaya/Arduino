#include <LiquidCrystal595.h>    // include the library
//#include <IRremote.h>
//#include <LiquidCrystal_SR.h>

//LiquidCrystal_SR lcd(7,8,TWO_WIRE);

//For remote
//int IRpin = 3;
//IRrecv irrecv(IRpin);
//decode_results results;
//unsigned long starttime = 0;

LiquidCrystal595 lcd(2,1,0);     // datapin, latchpin, clockpin
int i=0;
void setup() {
    lcd.begin(16,2);             // 16 characters, 2 rows
    lcd.clear();
    //delay(2000);
    lcd.setBacklightOn();
    //delay(2000);
    lcd.setCursor(0,0);
    //lcd.digitalOut(HIGH);
    /*delay(2000);*/
    lcd.print("Wow. 3 pins!");
    //lcd.print("     IR Test     ");
    /*lcd.autoscroll();
    delay(2000);
    lcd.setCursor(0,1);
    lcd.setBacklightOff();
    delay(2000);
    lcd.print("Fabulous");    
    lcd.digitalOut(LOW);
    delay(2000);*/
    //Serial.begin(115200);
    //irrecv.enableIRIn(); 
}

void loop() {
    //if (irrecv.decode(&results))
    //{
        //Serial.println(results.value); // Print the Serial 'results.value'
        lcd.clearLine(1);
        lcd.print(i++);
        //lcd.cursor();
        //lcd.blink();
        
        delay(250);
        //irrecv.resume();
    //}
}
