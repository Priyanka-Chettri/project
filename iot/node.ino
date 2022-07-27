// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"


#define ONE_WIRE_BUS 2
#define DHTPIN 3
#define DHTTYPE DHT11


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
DHT dht(DHTPIN, DHTTYPE);


void setup(void)
{
  Serial.begin(9600);

  sensors.begin();
  sensors.setResolution(insideThermometer, 9); 
  dht.begin();  
  Serial.println();


}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print("Temperature : ");
  Serial.println(tempC);
  Serial.println(F("°C")); 
}
void printHumidity(){
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println(F("%"));  
}
void tempDHT(){
  float t = dht.readTemperature();
  Serial.print(F("Temperature from DHT11 : "));
  Serial.print(t);
  Serial.println(F("°C"));  
}
void loop(void)
{ 
  sensors.requestTemperatures();
  printTemperature(insideThermometer); 
  printHumidity();
  tempDHT();
  delay(5000);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
