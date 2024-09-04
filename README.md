# 📊 Anomaly Detection Software

Welcome to **Anomaly Detection Software**, a C/C++ based tool that helps you detect anomalies in numerical datasets using statistical methods. The software uses a straightforward statistical anomaly detection algorithm that can be integrated into any system for identifying outliers in a given dataset.

## ⚙️ Overview

This software implements a **statistical approach** for detecting anomalies based on the assumption that the data follows a **normal distribution**. It identifies outliers using the **mean** and **standard deviation**, flagging data points that are outside a configurable threshold.

## ✨ Key Features

- **🧠 Statistical Detection**: Simple and effective detection using mean and standard deviation. Note: These simpler methods may not be useful for your use-case.
- **📊 Normal Distribution Assumption**: Detects anomalies assuming the data follows a normal distribution.
- **💾 Memory-efficient**: The algorithm processes the dataset in two passes to calculate accurate statistics while minimizing memory use. Note: to be more precise: O(n) time and space complexity...
- **💡 Modular**: The software is split into modular components for preprocessing, detecting, and printing anomalies.

## 🛠️ How It Works

1. **Input**: The software takes an array of float values as input.
2. **Preprocessing**:
   - The dataset is first preprocessed (if necessary) to clean and normalize the data.
3. **Detection**:
   - It computes the **mean** and **standard deviation** of the dataset.
   - Any data point that lies outside a specified number of standard deviations from the mean (default is 2) is flagged as an anomaly.
4. **Output**: The software returns a 2D array where each row contains:
   - The original data point.
   - A flag (`1.0` for anomaly, `0.0` for normal data point).

## 🧑‍💻 Code Breakdown

### Core Files

1. **`detect_anomalies.c`**: Implements the core algorithm for anomaly detection.
   - Computes the mean and standard deviation in two passes.
   - Allocates memory for results and returns a 2D array with the original values and flags for anomalies.
2. **`extract_features.c`**: Handles any feature extraction from the dataset, preparing the data for anomaly detection.
3. **`preprocess_data.cpp`**: Prepares and normalizes the dataset before feeding it into the anomaly detection algorithm.
4. **`print_anomalies.cpp`**: A utility to print the detected anomalies to the console and store them in a structured format.
