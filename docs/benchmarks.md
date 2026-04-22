# 📈 Performance Benchmarks & Model Comparison

This document presents the benchmark results for the various machine learning architectures explored during the development of the SnO2-Gas-Analytics system.

## 📊 Summary Table

| Model Architecture | Test Accuracy | F1-Score | Edge Deployment | Hardware Latency (ESP32) |
| :--- | :--- | :--- | :--- | :--- |
| **Baseline (Decision Tree)** | 71.4% | 0.70 | Possible | ~2 ms |
| **Random Forest (15 Trees)** | 89.5% | 0.89 | **Deployed** | **~12 ms** |
| **XGBoost (Windowed)** | 93.6% | 0.94 | Not Feasible | N/A |
| **Stacked Meta-Ensemble** | **90.9%** | **0.91** | Not Feasible | N/A |

## 🧪 Benchmark Methodology

All models were evaluated on the **Honest Dataset**, which used a group-based temporal split to ensure that no noisy versions of the test samples leaked into the training set.

### 1. Classification Precision (Honest Model)
| Label | Significance | Precision | Recall | F1-Score |
| :--- | :--- | :--- | :--- | :--- |
| **0** | Clean Air | 0.79 | 1.00 | 0.88 |
| **1** | Low Gas | 0.88 | 1.00 | 0.93 |
| **2** | Medium Gas | 1.00 | 0.80 | 0.89 |
| **3** | High Gas | 0.93 | 0.90 | 0.92 |
| **4** | Critical | 1.00 | 0.79 | 0.88 |

## 🧠 Insights & Optimization

- **The Jitter Paradox**: We found that while XGBoost achieved >95% on raw augmented data, its performance dropped Slightly when faced with real-time ADC jitter. The **distilled Random Forest** provided the best balance of stability and hardware compatibility.
- **Memory Efficiency**: The final TinyML header consumes less than 2% of the ESP32's available SRAM, leaving significant room for networking and notification tasks.
- **Safety Margin**: To prioritize safety, the model was tuned for High Recall on Labels 3 and 4, ensuring that hazardous conditions are rarely missed.
