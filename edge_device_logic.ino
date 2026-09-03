#include <ArduinoJson.h>
#include <DHT.h>

// Sensor pins definition
#define SOIL_MOISTURE_PIN A0
#define LIGHT_PIN A1
#define NPK_PIN A2
#define MAX_SOIL 1023
#define MAX_LIGHT 1023
#define MAX_NPK 1023
#define SOIL_MOISTURE_THRESHOLD 300
#define LIGHT_INTENSITY_THRESHOLD 800

DHT dht(2, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // 1. Data Acquisition
  int soilRaw = analogRead(SOIL_MOISTURE_PIN);
  int lightRaw = analogRead(LIGHT_PIN);
  int npkRaw = analogRead(NPK_PIN);
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // 2. Data Filtering (Remove outliers)
  int soil = (soilRaw >= 0 && soilRaw <= MAX_SOIL) ? soilRaw : -1;
  int light = (lightRaw >= 0 && lightRaw <= MAX_LIGHT) ? lightRaw : -1;
  int npk = (npkRaw >= 0 && npkRaw <= MAX_NPK) ? npkRaw : -1;
  temp = isnan(temp) ? -100 : temp; // Flag error as -100
  humidity = isnan(humidity) ? -1 : humidity;

  // 3. Edge Computing Logic
  if (soil != -1 && soil < SOIL_MOISTURE_THRESHOLD) {
    triggerWaterValve();
  }
  if (light != -1 && light > LIGHT_INTENSITY_THRESHOLD) {
    activateShield();
  }

  // 4. Format into JSON Payload
  StaticJsonDocument<256> doc;
  doc["soil_moisture"] = soil;
  doc["light_intensity"] = light;
  doc["npk_level"] = npk;
  doc["temperature"] = temp;
  doc["humidity"] = humidity;

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);
  Serial.println(jsonBuffer);
  
  delay(10000); 
}

void triggerWaterValve() {
  // Logic to open water valve autonomously at the edge
}

void activateShield() {
  // Logic to activate shield based on light intensity
}
