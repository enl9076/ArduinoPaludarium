/*
    Name:       paludarium_new.ino
    Created:	1/12/2021 10:51:25 AM
    Author:     DESKTOP-ERACB7G\enl90
*/
#include <SoftwareSerial.h>
#include <SPI.h>


// libraries & calls for clock and display screen
#include "RTClib.h"
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> 
RTC_Millis rtc;
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// libraries and calls for sensors
#include <Wire.h>
#include <DHT_U.h>
#include <DHT.h>
#include <BH1750_WE.h>
#define DHTTYPE DHT11
#define BH1750_ADDRESS 0x23
BH1750_WE myBH1750(BH1750_ADDRESS);


//define necessary variables
const int tempHum = 22;
DHT dht(tempHum, DHTTYPE);
const int relay = 31;
const int touch = 35;
const int waterPin = A15;
const int uv = A14;


void setup()
{
  Serial.begin(9600);
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  dht.begin();
  Wire.begin();
  uint16_t identifier = tft.readID();
  identifier = 0x9341;
  myBH1750.init();
  pinMode(relay, OUTPUT);
  pinMode(touch, INPUT);
  pinMode(tempHum, INPUT);
  pinMode(uv, INPUT);
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
}

void loop()
{
  tft.fillScreen(BLACK);
  //GET TIME AND SENSOR VALUES
  getTime();
  float lightIntensity = myBH1750.getLux();
  int water_level = analogRead(waterPin);
  int uv_value = analogRead(uv);
  float t = dht.readTemperature(true);
  float h = dht.readHumidity();
  //PRINT TEMP AND HUMIDITY TO THE SCREEN
  tft.setCursor(2, 40);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.print(F("Temp"));
  tft.setTextColor(WHITE);
  tft.setCursor(10, 72);
  tft.print(t);
  tft.print(F(" F"));
  tft.setCursor(130, 40);
  tft.setTextColor(CYAN);
  tft.print(F("Humidity"));
  tft.setTextColor(WHITE);
  tft.setCursor(155, 72);
  tft.print(h);
  tft.println(F("%"));
  
  // PRINT LIGHT VALUES TO THE SCREEN
  tft.setCursor(15, 120);
  tft.setTextColor(CYAN);
  tft.print(F("Light"));
  tft.setTextColor(WHITE);
  tft.setCursor(5, 148);
  tft.print(lightIntensity);
  tft.println(F(" Lux"));
  tft.setTextColor(CYAN);
  tft.setCursor(170, 120);
  tft.print(F("UV"));
  tft.setTextColor(WHITE);
  tft.setCursor(170, 148);
  tft.print(uv_value);
  
  //PRINT WATER LEVEL TO SCREEN
  tft.setCursor(20, 190);
  tft.setTextColor(CYAN);
  tft.print("Water Reservoir");

  if(water_level<=100){
	  tft.setTextColor(WHITE);
      tft.setCursor(70, 220);
	  tft.print("GOOD");
  }else{
	  tft.setTextColor(WHITE);
	  tft.setCursor(70, 220);
	  tft.print("NEED WATER");
  }
  
  //SET TIMER FOR MISTER
  DateTime now = rtc.now();
  if ((now.hour() == 9 && now.minute()== 0)||(now.hour() == 12 && now.minute()== 0)||(now.hour() == 15 && now.minute()== 0)|| (now.hour() == 18 && now.minute() == 0)){
   digitalWrite(relay, HIGH);
   delay(65000);
   digitalWrite(relay, LOW);
  }
  if (digitalRead(touch) == HIGH){
    digitalWrite(relay, HIGH);
  }else{
    digitalWrite(relay, LOW);
  }
  delay(2000);
}

void getTime() {
	tft.setCursor(50, 2);
	tft.setTextColor(RED);
	tft.setTextSize(2);
    DateTime now = rtc.now();
    tft.print(now.month(), DEC);
	tft.print('.');
	tft.print(now.day(), DEC);
	tft.print('.');
	tft.print(now.year(), DEC);
	tft.print(' ');
	tft.print(now.hour(), DEC);
	tft.print(':');
	tft.print(now.minute(), DEC);
	tft.print(':');
	tft.print(now.second(), DEC);
}
