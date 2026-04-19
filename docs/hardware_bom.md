# 🛠 Hardware Bill of Materials (BOM) & Pinout

This document specifies the hardware components and wiring configuration required to build the multi-sensor gas monitoring station.

## 📋 Components List

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **ESP32 Dev Module** | 1 | Main microcontroller with WiFi connectivity. |
| **MQ-2 Sensor** | 1 | Sensitivity to LPG, Propane, Hydrogen, and Smoke (SnO₂). |
| **MQ-135 Sensor** | 1 | Sensitivity to NH3, NOx, Alcohol, Benzene, Smoke, and CO2. |
| **MQ-7 Sensor** | 1 | Sensitivity to Carbon Monoxide (CO). |
| **Load Resistors** | 3 | 10kΩ or 20kΩ resistors for sensor voltage divider. |
| **Logic Level Shifter** | 1 | Optional: To safely interface ESP32 (3.3V) with MQ sensors (5V). |
| **External 5V PSU** | 1 | High-current power supply for sensor heaters (minimum 1A). |

## 🔌 Pinout Mapping

The sensors are connected to the ESP32 analog pins as follows:

- **MQ-2**: GPIO 35 (ADC1_CH7)
- **MQ-135**: GPIO 34 (ADC1_CH6)
- **MQ-7**: GPIO 32 (ADC1_CH4)

> [!CAUTION]
> **Heater Power**: MQ sensors require significant current (~150mA per heater). **Do not** power the sensors directly from the ESP32's 3.3V or 5V pins. Use an external 5V power source and common the ground with the ESP32.

## 📐 Wiring Diagram Summary

1. Connect the **Heater (H)** pins of all sensors to the **External 5V** and **GND**.
2. Connect the **A** pins of the sensors to the **External 5V**.
3. Connect the **B** pins to the respective **ESP32 GPIO** pins.
4. Place a **Load Resistor (RL)** between the B pins and **GND**.
