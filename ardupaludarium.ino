
// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       arduPaludarium.ino
    Created:  12/19/2020 8:42:35 PM
    Author:     emily
*/

// libraries for temp/humidity module (DHT11) and uv
#include <DHT_U.h>
#include <DHT.h>
#include <Adafruit_VEML6070.h>
// libraries for the digital temp module
#include <OneWire.h>
#include <DallasTemperature.h>
// libraries for the OLED display
#include <Wire.h>
#include <ArducamSSD1306.h>


// define pins (temp-->7, dht-->4, relay-->12) and variables
#define temp 7
OneWire oneWire(temp);
#define TempHum 4
#define DHTTYPE DHT11
const int relay = 12;
int tempF = 0;
DallasTemperature sensors(&oneWire);
DHT dht(TempHum, DHTTYPE);
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
ArducamSSD1306 display(OLED_RESET);
Adafruit_VEML6070 uv = Adafruit_VEML6070();


/*----------------SETUP-------------------*/
void setup()
{
  Serial.begin(9600);
  sensors.begin();
  dht.begin();
  uv.begin(VEML6070_1_T);
  pinMode(relay, OUTPUT);
   // Clear the buffer.
  display.begin();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();
  delay(500);
}

/*-------------------MAIN LOOP----------------------*/
void loop()
{
  sensors.requestTemperatures();
  tempF = sensors.getTempFByIndex(0);
  float h = dht.readHumidity();
  display.begin();
  display.println(F("_Current_"));
  display.print(F("temp: "));
  display.println(tempF);
  display.print(F("H: "));
  display.print(h);
  display.println(F("%"));
  display.print(F("UV: "));
  display.println(uv.readUV());
  display.display();
  delay(1000);
  if (h < 70)
  {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }

}
