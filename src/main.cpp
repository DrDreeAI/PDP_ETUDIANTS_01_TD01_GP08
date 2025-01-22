#include <Arduino.h>

// Define the pins that we will use
#define LED 26

// DHT Temperature & Humidity Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  dht.begin();
  Serial.println(F("DHTxx Unified Sensor with Deep Sleep Example"));

  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println(F("Error reading humidity!"));
  }
  else
  {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  Serial.println(F("Entering deep sleep for 5 seconds..."));
  esp_sleep_enable_timer_wakeup(5000000);
  delay(100);
  esp_deep_sleep_start();
}

void loop()
{
}