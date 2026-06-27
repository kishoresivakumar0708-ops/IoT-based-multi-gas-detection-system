# 🔍 System Troubleshooting & Common Error Codes

This guide helps diagnose and resolve common issues with the SnO2-Gas-Analytics system.

## 📡 1. Networking Issues

**Problem**: ESP32 Serial Monitor shows `Send failed: connection lost`.
- **Cause**: WiFi signal strength (RSSI) is too low or the server is down.
- **Solution**: 
    - Check that the `serverUrl` in the code matches your computer's IP (`ipconfig` on Windows).
    - Ensure your firewall allows incoming traffic on port 5000.
    - Check the WiFi strength at the sensor location (RSSI should be > -75dBm).

---

## 🔬 2. Sensor Value Anomalies

**Problem**: All sensors reading `Ratio: 1.0` or `Ratio: 0.0`.
- **Cause**: 
    - **1.0**: The sensor is not yet heated or the clean air is identical to the baseline R0.
    - **0.0**: The load resistor (RL) is disconnected or the ADC pin is grounded.
- **Solution**: 
    - Verify that the sensors feel warm (5V heater is active).
    - Check continuity between the B-pin and the Load Resistor.

**Problem**: Significant drift in Clean Air.
- **Cause**: High humidity or temperature shifts.
- **Solution**: The **Adaptive Baseline Algorithm** will correct this over time. For immediate fixes, perform a manual R0 capture (see `docs/field_calibration.md`).

---

## 🛠 3. Common Error Logs

| Error Code / Message | Meaning | Resolution |
| :--- | :--- | :--- |
| `HTTP 400` | Malformed JSON | Check `String json = ...` formatting in `.ino` file. |
| `HTTP 404` | Endpoint not found | Verify `serverUrl` includes the `/log` path. |
| `ADC: 4095` | ADC Saturated | The sensor resistance is too low. Check for gas leaks or short circuits. |
| `Ratio > 2.0` | Incorrect Baseline | R0 is too low. Recalibrate in clean air. |
