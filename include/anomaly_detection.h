#ifndef ANOMALY_DETECTION_H
#define ANOMALY_DETECTION_H


// This preprocessor directive checks if the code is being compiled with a C++ compiler.
// It's used to ensure proper linkage and compatibility between C and C++ code.
// When this header is included in a C++ file, the code inside this block will be compiled.
// This allows us to use C++ features and standard library components in C++ code,
#ifdef __cplusplus

// while still maintaining compatibility with C code that might include this header.
// C++ standard library includes for string manipulation, I/O operations, and data structures
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <cstdlib>

// C++ function declarations

/**
 * Preprocesses string data into numeric (float) data.
 * @param data A 2D vector of strings containing the input data.
 * @param num_samples The number of samples to print for debugging purposes.
 * @return A 2D vector of floats containing the preprocessed numeric data.
 */
std::vector<std::vector<float>> preprocess_data(const std::vector<std::vector<std::string>>& data, int num_samples);

/**
 * Prints and returns detected anomalies from the input data.
 * @param data Pointer to an array of float values representing the dataset.
 * @param num_samples Number of samples in the data array.
 * @return A 2D vector of floats, where each inner vector contains the index and value of an anomaly.
 */
std::vector<std::vector<float>> print_anomalies(float* data, int num_samples);

extern "C" {
#endif

// C function declarations

/**
 * Extracts features from input data.
 * @param data Pointer to an array of float values.
 * @param num_samples Number of samples in the data array.
 * @return A 2D array of floats, where each row contains two features.
 */
float** extract_features(const float* data, int num_samples);

/**
 * Detects anomalies in a given dataset using statistical methods.
 * @param data Pointer to an array of float values representing the dataset.
 * @param num_samples Number of samples in the data array.
 * @return A 2D array of floats, where each row contains the original value and an anomaly flag.
 */
float** detect_anomalies(float* data, int num_samples);

#ifdef __cplusplus
}
#endif

#endif // ANOMALY_DETECTION_H



/*
 __   __                      _____                    __   __                         
 \ \ / /   _ _ __  _   _ ___ | ____|_ __ ___  _ __ ___ \ \ / /   _ _ __ __ _ _   _ _ __  
  \ V / | | | '_ \| | | / __||  _| | '_ ` _ \| '__/ _ \ \ V / | | | '__/ _` | | | | '_ \ 
   | || |_| | | | | |_| \__ \| |___| | | | | | | |  __/  | || |_| | | | (_| | |_| | | | |
   |_| \__,_|_| |_|\__,_|___/|_____|_| |_| |_|_|  \___|  |_| \__,_|_|  \__, |\__,_|_| |_|
                                                                       |___/             
*/
