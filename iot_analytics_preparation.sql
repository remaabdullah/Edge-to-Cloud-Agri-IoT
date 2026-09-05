SELECT 
  device_id, 
  location, 
  date_trunc('day', from_unixtime(timestamp)) AS reading_day, 
  AVG(soil_moisture) AS avg_soil_moisture, 
  AVG(temperature) AS avg_temp, 
  AVG(humidity) AS avg_humidity, 
  AVG(light_intensity) AS avg_light 
FROM farm_data_store 
WHERE status_flags.soil_valid = true 
GROUP BY device_id, location, date_trunc('day', from_unixtime(timestamp))
