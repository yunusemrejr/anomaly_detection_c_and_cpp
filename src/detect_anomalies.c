#include "anomaly_detection.h" // Include the header file for function declarations
#include <stdlib.h> // Include for memory allocation functions like malloc
#include <stdio.h>  // Include for input/output operations (not used in this function)
#include <math.h>   // Include for mathematical functions like sqrt and fabs

// Function to detect anomalies in a given dataset using statistical methods
// This function implements a simple but effective anomaly detection algorithm
// based on the assumption that the data follows a normal distribution.
// It uses the mean and standard deviation to identify outliers.
//
// Parameters:
//   - data: pointer to an array of float values representing the dataset
//   - num_samples: number of samples in the data array
// Returns: a 2D array of floats, where each row contains:
//   - the original value from the dataset
//   - a flag (1.0 or 0.0) indicating whether the value is considered an anomaly
float** detect_anomalies(float* data, int num_samples) {
    // Allocate memory for the 2D array to store anomaly results
    // This array will have the same number of rows as the input data
    // Each row will contain 2 float values: the original value and the anomaly flag
    float** anomalies = (float**)malloc(num_samples * sizeof(float*));
    
    // Variables to calculate mean and standard deviation
    // We use a two-pass algorithm to compute these statistics accurately
    float sum = 0, sum_sq = 0;
    
    // First pass: calculate sum and sum of squares
    // This pass computes the necessary components for mean and variance calculation
    for (int i = 0; i < num_samples; i++) {
        sum += data[i];         // Accumulate the sum for mean calculation
        sum_sq += data[i] * data[i];  // Accumulate the sum of squares for variance calculation
    }
    
    // Calculate mean (average) of the dataset
    // The mean represents the central tendency of the data
    float mean = sum / num_samples;
    
    // Calculate standard deviation using the formula: sqrt(E[X^2] - (E[X])^2)
    // Where E[X] is the mean and E[X^2] is the mean of squared values
    // The standard deviation measures the amount of variation or dispersion in the dataset
    float std_dev = sqrt(sum_sq / num_samples - mean * mean);
    
    // Second pass: determine anomalies and populate the result array
    // We consider a data point an anomaly if it's more than 2 standard deviations away from the mean
    // This is based on the empirical rule (68-95-99.7 rule) for normal distributions
    for (int i = 0; i < num_samples; i++) {
        // Allocate memory for each row in the anomalies array
        anomalies[i] = (float*)malloc(2 * sizeof(float));
        
        // Store the original value in the first column
        // This allows for easy reference back to the original data
        anomalies[i][0] = data[i];
        
        // Determine if the value is an anomaly and store the result in the second column
        // We use the absolute difference from the mean to catch both high and low outliers
        // The threshold of 2 standard deviations captures approximately 95% of the data in a normal distribution
        // 1.0f indicates an anomaly, 0.0f indicates a normal value
        anomalies[i][1] = fabs(data[i] - mean) > 2 * std_dev ? 1.0f : 0.0f;
    }
    
    // Return the 2D array containing the anomaly detection results
    // This array can be used by other parts of the program to process or display the anomalies
    return anomalies;
}


/*
SOURCES TO UNDERSTAND THE STATISTICAL METHODS USED IN THIS CODE:

https://en.wikipedia.org/wiki/Arithmetic_mean
https://en.wikipedia.org/wiki/Standard_deviation
https://en.wikipedia.org/wiki/Normal_distribution   
https://en.wikipedia.org/wiki/Variance
https://en.wikipedia.org/wiki/68%E2%80%9395%E2%80%9399.7_rule
https://en.wikipedia.org/wiki/Outlier


*/

/*
 __   __                      _____                    __   __                         
 \ \ / /   _ _ __  _   _ ___ | ____|_ __ ___  _ __ ___ \ \ / /   _ _ __ __ _ _   _ _ __  
  \ V / | | | '_ \| | | / __||  _| | '_ ` _ \| '__/ _ \ \ V / | | | '__/ _` | | | | '_ \ 
   | || |_| | | | | |_| \__ \| |___| | | | | | | |  __/  | || |_| | | | (_| | |_| | | | |
   |_| \__,_|_| |_|\__,_|___/|_____|_| |_| |_|_|  \___|  |_| \__,_|_|  \__, |\__,_|_| |_|
                                                                       |___/             
*/
