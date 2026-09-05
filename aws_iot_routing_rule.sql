SELECT 
  device_id, 
  soil_moisture, 
  temperature, 
  humidity, 
  light_intensity, 
  timestamp 
FROM 'farm/+/sensor/#' 
WHERE soil_moisture < 300 AND status_flags.soil_valid = true
