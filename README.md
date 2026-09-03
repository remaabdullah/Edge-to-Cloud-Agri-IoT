# AWS Smart Agricultural Monitoring & Predictive Irrigation

A 3-layer IoT framework (Edge, Fog, Cloud) designed for automated and predictive irrigation using AWS services and machine learning.

## Architecture Stack
* **Edge Layer:** Arduino sensors collecting environmental data (Soil, Temp, Humidity, Light, NPK) with local outlier filtering and JSON packaging.
* **Fog Node:** Local data aggregation, rule execution, and temporary storage (SQLite) to handle internet outages.
* **Cloud Layer (AWS):** Secure data ingestion and processing.

## AWS Services Integrated
* **AWS IoT Core:** Manages secure device communication via MQTT and routes payloads using the Rules Engine.
* **AWS IoT Analytics & S3:** Cleans time-series data streams and archives raw payloads in a scalable Data Lake.
* **Amazon SNS:** Triggers real-time alerts for environmental anomalies (e.g., low soil moisture).
* **Amazon SageMaker:** Hosts an **XGBoost Regression** model for advanced forecasting.

## Predictive Intelligence
The system utilizes an **XGBoost** model trained on historical data to predict soil moisture 24 hours in advance, optimizing irrigation duration and reducing water consumption by up to 30%.
