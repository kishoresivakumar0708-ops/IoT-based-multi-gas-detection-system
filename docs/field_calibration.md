# 🩹 Field Calibration & Maintenance Guide

Maintaining a semi-conductor (SnO₂) based gas detection system over the long term requires structured calibration protocols to compensate for environmental aging and sensor drift.

## 🌡 1. Pre-Deployment Burn-in

Before any data collection or deployment, the sensors must be "burned-in":
- **Initial Phase**: Power the sensors continuously for 24-48 hours.
- **Why?**: To stabilize the internal heating element and burn off manufacturing residues (protective coatings) that cause high initial resistance readings.

## ⚖ 2. In-Situ Calibration (R0 Mapping)

The system automatically performs **Adaptive Baseline Correction**, but intentional manual calibration should be done monthly:
1. **Clean Air Exposure**: Ensure the station is in a zero-VOC environmental for at least 30 minutes.
2. **Baseline Capture**: Record the lowest stable resistance values (R0).
3. **Software Update**: Update the `R0_MQx` constants in the ESP32 code if the drift exceeds ±15% of the initial 8-hour baseline.

## 🛠 3. Maintenance Checklist

| Task | Frequency | Description |
| :--- | :--- | :--- |
| **Visual Inspection** | Weekly | Check for dust accumulation or spider webs on the sensor mesh. |
| **Dust Cleaning** | Monthly | Use canned air (filtered) to gently blow debris off the mesh. |
| **Heater Verification** | Monthly | Verify that the sensor is warm to the touch and consuming the rated current. |
| **Cross-Validation** | Quarterly | Test the system against a known calibration gas to verify sensitivity. |

## 📉 Handling Long-Term Drift

Semiconductor sensors inherently drift over months of operation. Our **Adaptive Drift Algorithm** models this by:
- Tracking the 5th-percentile Rs values over a 24-hour sliding window.
- Automatically shifting the R0 constant if the clean-air baseline shifts permanently.
