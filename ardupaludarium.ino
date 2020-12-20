// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       arduPaludarium.ino
    Created:	12/19/2020 8:42:35 PM
    Author:     emily
*/

// libraries
#include <DHT_U.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>


// pins, functions, and variables
#define temp 7
OneWire oneWire(temp);
#define TempHum 4
#define DHTTYPE DHT11
const int relay = 12;
int tempF = 0;
DallasTemperature sensors(&oneWire);
DHT dht(TempHum, DHTTYPE);


// The setup() function runs once each time the micro-controller starts

void setup()
{
	Serial.begin(9600);
	sensors.begin();
	dht.begin();
	pinMode(relay, OUTPUT);
}

// Add the main program code into the continuous loop() function
void loop()
{
	sensors.requestTemperatures();
	tempF = sensors.getTempFByIndex(0);
	float h = dht.readHumidity();
	Serial.print("temperature: ");
	Serial.print(tempF);
	Serial.print(", ");
	Serial.print("humidity: ");
	Serial.println(h);
	delay(5000);
	if (tempF > 85 || h < 65)
	{
		digitalWrite(relay, HIGH);
		Serial.println("relay on");
	}
	else
	{
		digitalWrite(relay, LOW);
	}

}
