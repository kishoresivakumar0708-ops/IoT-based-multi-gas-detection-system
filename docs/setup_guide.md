# 📂 Software Setup & Configuration Guide

This guide provides step-by-step instructions for setting up the SnO2-Gas-Analytics software environment on both the backend server and the ESP32 microcontroller.

## 🐍 Backend Environment Setup

The backend is built using Python 3.9+. Follow these steps to prepare your server:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/aashishniranjanb/SnO2-Gas-Analytics.git
   cd SnO2-Gas-Analytics/backend-server
   ```

2. **Create a Virtual Environment**:
   ```bash
   python -m venv venv
   source venv/bin/activate  # On Windows: venv\Scripts\activate
   ```

3. **Install Dependencies**:
   ```bash
   pip install -r requirements.txt
   ```

4. **Required Libraries**:
   - `flask` (Server communication)
   - `pandas` (Data logging)
   - `xgboost` (Predictive modeling)
   - `scikit-learn` (ML utilities)

## 📡 ESP32 Firmware Setup

1. **Install Arduino IDE**: Ensure you have the latest version of the Arduino IDE or PlatformIO.
2. **Install ESP32 Boards**: Add the ESP32 board URL to your preferences and install the `esp32` board family.
3. **Libraries Required**:
   - `WiFi.h` (Native)
   - `HTTPClient.h` (Native)
   - `time.h` (Native)
4. **Configuration**:
   - Open `esp32_multi_sensor/esp32_multi_sensor.ino`.
   - Update the `ssid` and `password` variables for your WiFi network.
   - Update the `serverUrl` to match your local machine's IP address.

## 🚀 Running the System

1. Start the backend: `python server.py`.
2. Power the ESP32 and monitor the Serial Monitor (115200 baud).
3. Confirm that data is being logged to `multi_sensor_data.csv`.
