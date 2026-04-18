# 🌐 API Communication Protocol

This document defines the REST API interface used by the ESP32 and potential mobile dashboards to interact with the SnO2-Gas-Analytics backend server.

## 📡 Endpoints Overview

### 1. Data Ingestion (`POST /log`)
This is the primary endpoint used by the ESP32 to transmit real-time sensor readings.

**JSON Schema**:
```json
{
  "date": "YYYY-MM-DD",
  "time": "HH:MM:SS",
  "mq2_adc": 1234,
  "mq2_rs": 25000.5,
  "mq2_ratio": 0.95,
  "mq2_ppm": 10.5,
  "mq135_adc": 1100,
  "mq7_adc": 800,
  "mq2_delta": 0.02,
  "label": 0
}
```

**Response Codes**:
- `200 OK`: Data successfully logged to `multi_sensor_data.csv`.
- `400 Bad Request`: Missing mandatory fields or malformed JSON.

---

### 2. Status Check (`GET /status`)
Used to verify server connectivity and retrieve current baseline configuration.

**Response Schema**:
```json
{
    "status": "active",
    "uptime": "12:34:56",
    "active_r0": {
        "mq2": 25770.0,
        "mq135": 10582.0,
        "mq7": 27584.0
    }
}
```

---

### 3. Model Metadata (`GET /model/info`)
Retrieves the current active model version and its performance characteristics.

**Response Schema**:
```json
{
    "version": "v2.1-stacked",
    "accuracy": 0.909,
    "last_trained": "2026-04-07",
    "features": ["log_ratio", "rolling_mean", "rolling_std", "interactions"]
}
```

## 🛠 Testing with cURL
You can test the ingestion endpoint from your terminal:
```bash
curl -X POST http://localhost:5000/log \
     -H "Content-Type: application/json" \
     -d '{"mq2_adc": 1500, "label": 0}'
```
