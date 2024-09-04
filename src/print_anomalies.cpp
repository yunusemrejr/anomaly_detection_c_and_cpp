#include "anomaly_detection.h"
#include <iostream>
#include <vector>

// Function to print and return detected anomalies from the input data
std::vector<std::vector<float>> print_anomalies(float* data, int num_samples) {
    // Vector to store anomalies (index and value pairs)
    std::vector<std::vector<float>> anomalies;
    
    // Detect anomalies using the C function from anomaly_detection.h
    float** detected_anomalies = detect_anomalies(data, num_samples);
    
    std::cout << "Detected anomalies:" << std::endl;
    
    // Iterate through all samples
    for (int i = 0; i < num_samples; i++) {
        // Check if the current sample is flagged as an anomaly (1.0f indicates an anomaly)
        if (detected_anomalies[i][1] == 1.0f) {
            // Print the anomaly information
            std::cout << "Anomaly at index " << i << ": " << detected_anomalies[i][0] << std::endl;
            
            // Add the anomaly to our vector (storing index and value)
            anomalies.push_back({static_cast<float>(i), detected_anomalies[i][0]});
        }
        
        // Free the memory allocated for each row in detected_anomalies
        free(detected_anomalies[i]);
    }
    
    // Free the memory allocated for the detected_anomalies array
    free(detected_anomalies);
    
    // Return the vector of detected anomalies
    return anomalies;
}



/*
 __   __                      _____                    __   __                         
 \ \ / /   _ _ __  _   _ ___ | ____|_ __ ___  _ __ ___ \ \ / /   _ _ __ __ _ _   _ _ __  
  \ V / | | | '_ \| | | / __||  _| | '_ ` _ \| '__/ _ \ \ V / | | | '__/ _` | | | | '_ \ 
   | || |_| | | | | |_| \__ \| |___| | | | | | | |  __/  | || |_| | | | (_| | |_| | | | |
   |_| \__,_|_| |_|\__,_|___/|_____|_| |_| |_|_|  \___|  |_| \__,_|_|  \__, |\__,_|_| |_|
                                                                       |___/             
*/
