# 🧠 TinyML Architecture & Inference Logic

This document details the transition from server-side deep learning to edge-based **TinyML** inference on the ESP32.

## 🏗 Model Overview

The system utilizes an optimized **Random Forest Classifier** distilled from an ensemble of XGBoost and MLP models. To fit within the constraints of the ESP32 while maintaining >90% accuracy, the model was pruned and quantized using `micromlgen`.

### 📊 Input Feature Vector (11 Dimensions)

The model makes decisions based on an 11-dimensional feature vector calculated in real-time:

1. **Log-Ratio (3)**: `log10(ratio)` for MQ-2, MQ-135, and MQ-7 to linearize sensor response.
2. **Rolling Mean (3)**: 5-sample moving average to dampen electronic noise.
3. **Rolling Std Dev (3)**: 5-sample standard deviation to capture signal volatility during transients.
4. **Interaction Terms (2)**: Cross-product of ratios (e.g., `MQ2 * MQ7`) to identify unique gas signatures.

## 🔄 Real-time Feature Engineering

Since the ESP32 lacks the heavy processing power of a Python backend, we implemented a custom **Circular Buffer** in C++:

- **Buffer Size**: 5 samples.
- **Update Frequency**: 2 seconds.
- **Logic**: Each time a sensor is read, the oldest sample is evicted, and new statistical features (Mean/Std) are re-calculated on the fly before being passed to the `Model.predict()` function.

## 🚀 Performance on ESP32

| Metric | Performance |
| :--- | :--- |
| **Inference Latency** | < 12 ms |
| **RAM Usage** | ~1.5 KB |
| **Flash Impact** | ~22 KB |
| **Prediction Frequency** | 0.5 Hz |

## 🛠 Distillation Process

The model was exported from a Python environment where it was trained on the "Honest Dataset" (properly split to avoid data leakage). The resulting C++ header (`Model.h`) is integrated directly into the Arduino sketch.
