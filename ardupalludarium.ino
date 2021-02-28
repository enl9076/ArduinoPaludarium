/*
    Name:       paludarium_new.ino
    Created:	1/12/2021 10:51:25 AM
    Author:     DESKTOP-ERACB7G\enl90
*/
//#include <SPI.h>

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


void setup()
{
  Serial.begin(9600);
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  dht.begin();
  //sensor_t sensor;
  Wire.begin();
  uint16_t identifier = tft.readID();
  identifier = 0x9341;
  myBH1750.init();
  pinMode(relay, OUTPUT);
  pinMode(touch, INPUT);
  pinMode(tempHum, INPUT);
  tft.begin(identifier);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
}

void loop()
{
	tft.fillScreen(BLACK);
  getTime();
  float lightIntensity = myBH1750.getLux();
  int water_level = analogRead(waterPin);
  // Get temperature event and print its value.
  //sensors_event_t event;
  float t = dht.readTemperature(true);
  //float tF = (t * 1.8) + 32;
  tft.setCursor(2, 40);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.print(F("Temp"));
  tft.setTextColor(WHITE);
  tft.setCursor(10, 72);
  tft.print(t);
  tft.print(F(" F"));
  // Get humidity event and print its value.
  float h = dht.readHumidity();
  tft.setCursor(130, 40);
  tft.setTextColor(CYAN);
  tft.print(F("Humidity"));
  tft.setTextColor(WHITE);
  tft.setCursor(155, 72);
  tft.print(h);
  tft.println(F("%"));
  // Get light value & print to screen
  tft.setCursor(80, 105);
  tft.setTextColor(CYAN);
  tft.print(F("Light"));
  tft.setTextColor(WHITE);
  tft.setCursor(85, 138);
  tft.print(lightIntensity);
  tft.println(F(" Lux"));
  // Get water level & print to screen
  tft.setCursor(20, 160);
  tft.setTextColor(CYAN);
  tft.print("Water Reservoir");

  if(water_level>600){
	  tft.setTextColor(WHITE);
    tft.setCursor(70, 180);
	  tft.print("GOOD");
  }else if(water_level>450 && water_level<600){
	  tft.setTextColor(WHITE);
    tft.setCursor(70, 180);
	  tft.print("OK");
  }else{
	  tft.setTextColor(WHITE);
    tft.setCursor(70, 180);
	  tft.print("NEED WATER");
  }

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
  delay(5000);
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
