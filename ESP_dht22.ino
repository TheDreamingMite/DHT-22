#include <iarduino_RTC.h>
#include "DHT.h"

#define DHTTYPE DHT22
iarduino_RTC time_rtc(RTC_DS1302, 16, 5, 17);  // для модуля DS1302 - RST, CLK, DAT


unsigned long delayTime;
uint8_t DHTPin = 2;
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;
float Temp_Fahrenheit;

void setup() {
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);
  dht.begin();
  time_rtc.begin();
  time_rtc.settime(0, 19, 14, 24, 5, 24, 3); // 0  сек, 30 мин, 18 часов, 12, июня, 2020, четверг
}

void loop(){
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  Temp_Fahrenheit = dht.readTemperature(true);
  if (isnan(Humidity) || isnan(Temperature) || isnan(Temp_Fahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.print(F("°C "));
  Serial.print(Temp_Fahrenheit);
  Serial.print(F("°F "));
  // if (millis() % 1000 == 0) {
  Serial.print(time_rtc.gettime(" d M Y, D "));
  Serial.print(time_rtc.gettime(" H:i:s "));
  Serial.println(time_rtc.gettime(" d M Y, D "));
  delay(500);
  //  }
}

