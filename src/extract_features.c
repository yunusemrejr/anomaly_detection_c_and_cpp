#include "anomaly_detection.h"
#include <stdlib.h>
#include <stdio.h>

// Function to extract features from input data
// Parameters:
//   - data: pointer to an array of float values
//   - num_samples: number of samples in the data array
// Returns: a 2D array of floats, where each row contains two features
float** extract_features(const float* data, int num_samples) {
    // Print the input data for debugging purposes
    printf("Data received for extraction:\n");
    for (int i = 0; i < num_samples; i++) {
        printf("%f ", data[i]);
    }
    printf("\n");

    // Allocate memory for the 2D array to store features
    // Each row will have 2 float values: the original value and a derived feature
    float** features = (float**)malloc(num_samples * sizeof(float*));
    
    // Loop through each sample to extract features
    for (int i = 0; i < num_samples; i++) {
        // Allocate memory for each row in the features array
        features[i] = (float*)malloc(2 * sizeof(float));
        
        // First feature: the original value
        features[i][0] = data[i];
        
        // Second feature: square of the original value
        // This could potentially highlight larger deviations from the mean
        features[i][1] = data[i] * data[i];
    }
    
    // Return the 2D array containing the extracted features
    return features;
}

/*
 __   __                      _____                    __   __                         
 \ \ / /   _ _ __  _   _ ___ | ____|_ __ ___  _ __ ___ \ \ / /   _ _ __ __ _ _   _ _ __  
  \ V / | | | '_ \| | | / __||  _| | '_ ` _ \| '__/ _ \ \ V / | | | '__/ _` | | | | '_ \ 
   | || |_| | | | | |_| \__ \| |___| | | | | | | |  __/  | || |_| | | | (_| | |_| | | | |
   |_| \__,_|_| |_|\__,_|___/|_____|_| |_| |_|_|  \___|  |_| \__,_|_|  \__, |\__,_|_| |_|
                                                                       |___/             
*/
