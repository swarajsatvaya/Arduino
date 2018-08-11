#include<DHT.h>
#include <LiquidCrystal595.h>

#define dht_dpin A5 
DHT dht(dht_dpin, DHT11);
LiquidCrystal595 lcd(6,7,8);

float humi,tem;

void setup() {
    lcd.begin(16,2);
    lcd.clear();
    lcd.setBacklightOn();
    dht.begin();
    Serial.begin(115200);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Humid: ");
  humi=dht.readHumidity();
  lcd.print(humi);   // printing Humidity on LCD
  lcd.print(" %    ");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  tem=dht.readTemperature();
  lcd.print(tem);   // Printing temperature on LCD
  lcd.print((char)223);
  lcd.print("C");
  
  Serial.print("Humidity: ");
  Serial.print(humi);   
  Serial.print(" %    ");
  Serial.print("Temperature: ");
  Serial.print(tem);   // 
  Serial.print((char)223);
  Serial.println("C");
  
  delay(2000);
}
