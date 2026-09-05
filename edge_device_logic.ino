// 1. Data Acquisition
int soilRaw = analogRead(SOIL_MOISTURE_PIN);
int lightRaw = analogRead(LIGHT_PIN);
int npkRaw = analogRead(NPK_PIN);
float temp = dht.readTemperature();
float humidity = dht.readHumidity();

// 2. Data Filtering
int soil = (soilRaw >= 0 && soilRaw <= MAX_SOIL)? soilRaw : -1;
int light = (lightRaw >= 0 && lightRaw <= MAX_LIGHT)? lightRaw : -1;
int npk = (npkRaw >= 0 && npkRaw <= MAX_NPK)? npkRaw : -1;
temp = isnan(temp)? -100 : temp; // Flag error as -100
humidity = isnan(humidity)? -1 : humidity;

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
doc["npk"] = npk;
doc["temperature"] = temp;
doc["humidity"] = humidity;
char jsonBuffer[256];
serializeJson(doc, jsonBuffer);
Serial.println(jsonBuffer);
