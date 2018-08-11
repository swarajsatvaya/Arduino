// simplestesp8266clock.ino
//
// Libraries needed:
//  Time.h & TimeLib.h:  https://github.com/PaulStoffregen/Time
//  Timezone.h: https://github.com/JChristensen/Timezone
//  SSD1306.h & SSD1306Wire.h:  https://github.com/squix78/esp8266-oled-ssd1306
//  NTPClient.h: https://github.com/arduino-libraries/NTPClient
//  ESP8266WiFi.h & WifiUDP.h: https://github.com/ekstrand/ESP8266wifi
//
// 128x64 OLED pinout:
// GND goes to ground
// Vin goes to 3.3V
// Data to I2C SDA (GPIO 0)
// Clk to I2C SCL (GPIO 2)

#include <ESP8266WiFi.h>
#include <WifiUDP.h>
#include <String.h>
#include <Wire.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <LiquidCrystal595.h>    // include the library

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "in.pool.ntp.org"//"ca.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

// Create a display object
LiquidCrystal595 lcd(2,1,0);      // datapin, latchpin, clockpin
 
const char* ssid = "BBinatone";   // insert your own ssid 
const char* password = "9474013767";              // and password
String date;
String t;

// constants won't change:
const char * days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"} ;
const char * ampm[] = {"AM", "PM"} ;
String ap;
int cursec;
const long syncinterval = 10;   // Sync Interval in Second
boolean firstsync = 0, syncflag = 0;
unsigned long previousMillis = 0, currentMillis = 0;

byte alarmicon[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b00100,
  0b00000
};

void setup ()
{
  //Serial.begin(115200); // most ESP-01's use 115200 but this could vary
  timeClient.begin();   // Start the NTP UDP client
  lcd.begin(16, 2);     // set up the LCD's number of columns and rows:
  lcd.createChar(0, alarmicon);
  
  lcd.setBacklightOn();
  lcd.clear();          // clear screen
  lcd.setCursor(0, 0);  // set the cursor to (0,0):
  //lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  
  // Connect to wifi
  //Serial.println("");
  //Serial.print("Connecting to ");
  //Serial.print(ssid);
  lcd.print("EnablingInternet");
  lcd.setCursor(0, 1);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    //Serial.print(".");
    if(i==16)
    {
      lcd.clearLine(1);
      lcd.print(".");
    }
    else
    {
      lcd.setCursor(i,1);
      lcd.print(".");
    }
    
  }
  //Serial.println("");
  //Serial.print("Connected to WiFi at ");
  //Serial.print(WiFi.localIP());
  //Serial.println("");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Internet Enabled");
  lcd.setCursor(0,1);
  lcdPrintMiddle("IP: " + WiFi.localIP().toString());
  delay(2000);
}

void lcdPrintMiddle(String str)
{
  if(str.length()<16)
  {
    int bspacel = (16 - str.length())/2;
    String bspace = "";
    for (int i = 0; i < bspacel; i++)
    {
      bspace = bspace + " ";
    }
    str = bspace + str;
  }
  lcd.print(str);
}

void syncWithServer()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    date = "";  // clear the variables
    t = "";
    
    // update the NTP client and get the UNIX UTC timestamp 
    timeClient.update();
    delay(100);
    unsigned long epochTime =  timeClient.getEpochTime();

    // convert received time stamp to time_t object
    time_t local; //, utc;
    //utc = epochTime;
    local = epochTime + 16200;

    // Then convert the UTC UNIX timestamp to local time
    //TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -300};  //UTC - 5 hours - change this as needed
    //TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -360};   //UTC - 6 hours - change this as needed
    //Timezone usEastern(usEDT, usEST);
    //local = utc ;//usEastern.toLocal(utc);

    // now format the Time variables into strings with proper names for month, day etc
    if(day(local)<10)
      date += "0";
      
    date += day(local) ;
    date +="-";
    date += months[month(local)-1];
    date += "-";
    date += year(local);
    date += "  ";
    date += days[weekday(local)-1];
    

    // format the time to 12-hour format with AM/PM and no seconds
    if(hourFormat12(local) < 10)
      t += "0";
    t += hourFormat12(local);
    t += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      t += "0";
    t += minute(local);
    t += ":";
    currentMillis = millis();
    previousMillis = currentMillis;
    cursec = second(local);
    ap = ampm[isPM(local)];
    ap = "  " + ap;
  }
  else // attempt to connect to wifi again if disconnected
  {
    lcd.clear();          // clear screen
    lcd.setCursor(0, 0);  // set the cursor to (0,0):
  
    // Connect to wifi
    //Serial.println("");
    //Serial.print("Connecting to ");
    //Serial.print(ssid);
    lcd.print("EnablingInternet");
    lcd.setCursor(0, 1);
    WiFi.begin(ssid, password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      //Serial.print(".");
      if(i==16)
      {
        lcd.clearLine(1);
        lcd.print(".");
      }
      else
      {
        lcd.setCursor(i,1);
        lcd.print(".");
      }
      
    }
    //Serial.println("");
    //Serial.print("Connected to WiFi at ");
    //Serial.print(WiFi.localIP());
    //Serial.println("");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Internet Enabled");
    lcd.setCursor(0,1);
    lcdPrintMiddle("IP: " + WiFi.localIP().toString());
    delay(2000);
  }
}

void loop() 
{
  String endpart = "";
  unsigned long currentMillis = millis();
  boolean updated = 0;
  if (firstsync == 0 || (cursec%syncinterval == 0 && syncflag == 0))
  {
    syncWithServer();
    firstsync = 1;
    updated = 1;
    syncflag = 1;
  }
  else if(currentMillis - previousMillis >= 1000)
  {
    if(syncflag == 1)
      syncflag = 0;
    previousMillis = currentMillis;
    cursec++;
    updated = 1;
  }
  if(updated == 1)
  {
    if(cursec < 10)
      endpart = "0" + String(cursec) + ap;
    else
      endpart = String(cursec) + ap;
    // Display the date and time
    //Serial.println("");
    //Serial.print("Local date: ");
    //Serial.print(date);
    //Serial.println("");
    //Serial.print("Local time: ");
    //Serial.print(t + endpart);

    // print the date and time on the LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcdPrintMiddle(t + endpart);
    lcd.setCursor(0,1);
    lcdPrintMiddle(date);
    updated = 0;
  }
}
