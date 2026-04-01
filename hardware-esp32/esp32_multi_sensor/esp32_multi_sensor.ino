#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"
#include <math.h>

// ================= CONFIG =================
const char* ssid = "Airtel_Barathy";
const char* password = "6384@bank";
const char* serverUrl = "http://192.168.1.5:5000/log";

// ================= PINS =================
#define MQ2_PIN   35
#define MQ135_PIN 34
#define MQ7_PIN   32

// ================= CONSTANTS =================
#define RL 20000.0
#define ADC_MAX 4095.0
#define VCC 3.3

// ====== OVERNIGHT CALIBRATED R0 VALUES ======
// Derived from 8-hour continuous clean-air mapping (Top 10% average Rs / Datasheet ratio)
float R0_MQ2   = 25770.0;
float R0_MQ135 = 10582.0;
float R0_MQ7   = 27584.0;

// ====== MODEL CONSTANTS ======
#define M_SLOPE -0.47
#define B_INTERCEPT 0.08

// ================= TIME =================
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

// ================= CONTROL =================
unsigned long previousMillis = 0;
const long interval = 2000;

int exposureLevel = 0;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("=== MULTI SENSOR CALIBRATION MODE ===");
  Serial.println("Enter label (0–4)");
}

// ================= SENSOR FUNCTION =================
void readSensor(int pin, float R0, int &adc, float &voltage, float &Rs, float &ratio, float &ppm) {

  adc = analogRead(pin);
  voltage = (adc / ADC_MAX) * VCC;

  if (voltage < 0.01) voltage = 0.01;

  Rs = ((VCC - voltage) * RL) / voltage;
  ratio = Rs / R0;

  float logppm = (log10(ratio) - B_INTERCEPT) / M_SLOPE;
  ppm = pow(10, logppm);
}

// ================= LOOP =================
void loop() {

  // ===== SERIAL LABEL INPUT =====
  if (Serial.available()) {
    int incoming = Serial.parseInt();
    if (incoming >= 0 && incoming <= 4) {
      exposureLevel = incoming;
      Serial.print("Label set to: ");
      Serial.println(exposureLevel);
    }
    while (Serial.available()) Serial.read();
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // ===== SENSOR READINGS =====
    int adc2, adc135, adc7;
    float v2, v135, v7;
    float Rs2, Rs135, Rs7;
    float ratio2, ratio135, ratio7;
    float ppm2, ppm135, ppm7;

    readSensor(MQ2_PIN, R0_MQ2, adc2, v2, Rs2, ratio2, ppm2);
    readSensor(MQ135_PIN, R0_MQ135, adc135, v135, Rs135, ratio135, ppm135);
    readSensor(MQ7_PIN, R0_MQ7, adc7, v7, Rs7, ratio7, ppm7);

    // ===== TIME =====
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return;

    char dateStr[20], timeStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &timeinfo);
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);

    // ===== SEND DATA =====
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");

      String json = "{";

      json += "\"date\":\"" + String(dateStr) + "\",";
      json += "\"time\":\"" + String(timeStr) + "\",";

      // MQ2
      json += "\"mq2_adc\":" + String(adc2) + ",";
      json += "\"mq2_rs\":" + String(Rs2) + ",";
      json += "\"mq2_ratio\":" + String(ratio2) + ",";
      json += "\"mq2_ppm\":" + String(ppm2) + ",";

      // MQ135
      json += "\"mq135_adc\":" + String(adc135) + ",";
      json += "\"mq135_rs\":" + String(Rs135) + ",";
      json += "\"mq135_ratio\":" + String(ratio135) + ",";
      json += "\"mq135_ppm\":" + String(ppm135) + ",";

      // MQ7
      json += "\"mq7_adc\":" + String(adc7) + ",";
      json += "\"mq7_rs\":" + String(Rs7) + ",";
      json += "\"mq7_ratio\":" + String(ratio7) + ",";
      json += "\"mq7_ppm\":" + String(ppm7) + ",";

      json += "\"label\":" + String(exposureLevel);

      json += "}";

      http.POST(json);
      http.end();
    }

    // ===== DEBUG PRINT =====
    Serial.println("-----");
    Serial.print("MQ2: "); Serial.print(ppm2);
    Serial.print(" | MQ135: "); Serial.print(ppm135);
    Serial.print(" | MQ7: "); Serial.print(ppm7);
    Serial.print(" | Label: "); Serial.println(exposureLevel);
  }
}
