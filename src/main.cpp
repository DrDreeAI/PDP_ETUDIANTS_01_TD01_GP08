#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Définir les broches utilisées
#define CAPTEUR 33 // GPIO connecté au DHT
#define LED 26     // GPIO pour la LED

// Définir le type de capteur utilisé (DHT11 ou DHT22)
#define DHTTYPE DHT22 // Remplacez par DHT11 si nécessaire

// Initialiser le capteur DHT
DHT_Unified dht(CAPTEUR, DHTTYPE);

// Variable pour le délai entre les lectures
uint32_t delayMS;

void setup()
{
  // Initialisation de la LED
  pinMode(LED, OUTPUT);

  // Initialisation de la communication série
  Serial.begin(9600);

  // Initialiser le capteur DHT
  dht.begin();
  Serial.println(F("DHTxx Capteur Température & Humidité"));

  // Obtenir les détails du capteur
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("Capteur de température initialisé"));
  Serial.println(F("------------------------------------"));
  Serial.print(F("Type de capteur : "));
  Serial.println(sensor.name);
  Serial.print(F("Version du pilote : "));
  Serial.println(sensor.version);
  Serial.print(F("Plage de mesure : "));
  Serial.print(sensor.min_value);
  Serial.print(F("°C à "));
  Serial.print(sensor.max_value);
  Serial.println(F("°C"));
  Serial.print(F("Résolution : "));
  Serial.print(sensor.resolution);
  Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  dht.humidity().getSensor(&sensor);
  Serial.println(F("Capteur d'humidité initialisé"));
  Serial.println(F("------------------------------------"));
  Serial.print(F("Type de capteur : "));
  Serial.println(sensor.name);
  Serial.print(F("Version du pilote : "));
  Serial.println(sensor.version);
  Serial.print(F("Plage de mesure : "));
  Serial.print(sensor.min_value);
  Serial.print(F("% à "));
  Serial.print(sensor.max_value);
  Serial.println(F("%"));
  Serial.print(F("Résolution : "));
  Serial.print(sensor.resolution);
  Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  // Délai minimal entre les lectures du capteur
  delayMS = sensor.min_delay / 1000;
}

void loop()
{
  // Effectuer une mesure toutes les 5 secondes
  delay(5000);

  // Lire la température
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println(F("Erreur de lecture de la température !"));
  }
  else
  {
    Serial.print(F("Température : "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

    // Contrôler la LED en fonction de la température
    if (event.temperature > 30.0)
    {                          // Température > 30°C
      digitalWrite(LED, HIGH); // Allumer la LED
      Serial.println(F("LED allumée (température élevée)"));
    }
    else
    {
      digitalWrite(LED, LOW); // Éteindre la LED
      Serial.println(F("LED éteinte (température normale)"));
    }
  }

  // Lire l'humidité
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    Serial.println(F("Erreur de lecture de l'humidité !"));
  }
  else
  {
    Serial.print(F("Humidité : "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
