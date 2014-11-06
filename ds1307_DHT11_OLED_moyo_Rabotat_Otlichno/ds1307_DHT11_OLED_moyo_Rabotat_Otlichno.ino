// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
//Arduino UNO + ds1307 + OLED display 1,3" IIC 128x64 + signal LED
#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"
#include <MicroLCD.h>
#include <SPI.h>
#include "DHT.h"
LCD_SH1106 lcd; /* for SH1106 OLED module (blue) */
//LCD_SSD1306 lcd; /* for SSD1306 OLED module(white) */
#define DHTTYPE DHT11
#define DHTPIN 7
DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 rtc;

int led = 2; //pin for signal LED

void setup () {
  {
	lcd.begin();
        dht.begin();
}
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    
  }
}

void loop () {
  {
	lcd.setFontSize(FONT_SIZE_MEDIUM);
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  DateTime now = rtc.now();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)); 
  else {
   {
     lcd.clear();
	lcd.setCursor(0, 0);
	lcd.setFontSize(FONT_SIZE_MEDIUM); //medium font
    lcd.print(" Humidity:      "); //space need to fine read on display
    lcd.print(h);
    lcd.print("  %");
   
    lcd.print("      Temperature:   +"); 
    lcd.print(t);
    lcd.print(" *C");
    delay(10000);
    lcd.clear();
    
    lcd.print("Data:          ");
    //lcd.print(now.day(), DEC);
    lcd.print(now.day()/10);
    lcd.print(now.day()%10);
    lcd.print('.');
    //lcd.print(now.month(), DEC);    //Witthout  "0"
    lcd.print(now.month()/10);   //With "0" (ecsamp. -  01. 02 etc.)
    lcd.print(now.month()%10);   //With "0" (ecsamp. -  01. 02 etc.)
    lcd.print('.');
    lcd.print(now.year(), DEC);
    lcd.print(' ');
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time:          ");
    //lcd.print(now.hour(), DEC);
    lcd.print(now.hour()/10);
    lcd.print(now.hour()%10);
    lcd.print(':');
    //lcd.print(now.minute(), DEC);
    lcd.print(now.minute()/10);
    lcd.print(now.minute()%10);
    lcd.print(':');
   // lcd.print(now.second(), DEC);
    lcd.print(now.second()/10);
    lcd.print(now.second()%10);
    lcd.print(' ');
    delay(5000);
    //Set time to switch the LED on pin2 
    if (now.hour() >= 17 && now.hour() < 18 && now.minute() >=10 && now.minute() < 15)
    
    
     
    digitalWrite(led, HIGH);  //switch on the led
    
    else
    
     digitalWrite(led,LOW);  // switch off the led
     
     if((t)>25)            //If temperature > 25*   switch on the LED on pin2
      digitalWrite(led, HIGH);
    
    else
    
     digitalWrite(led,LOW);  //If temperature < 25*  switch off the led
     
     
    }
  }
}
}

