#include <vector>
#include <string>
#include <iostream>
#include "anomaly_detection.h" // Include anomaly_detection.h header for function declarations

// Function to convert a string to a float
// Returns 0.0f if conversion fails due to invalid argument or out of range
float stringToFloat(const std::string& str) {
    try {
        return std::stof(str);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 0.0f;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
        return 0.0f;
    }
}

// Function to preprocess string data into numeric (float) data
// Parameters:
//   - data: 2D vector of strings containing the input data
//   - num_samples: number of samples to print (for debugging purposes)
// Returns: 2D vector of floats containing the preprocessed numeric data
std::vector<std::vector<float>> preprocess_data(const std::vector<std::vector<std::string>>& data, int num_samples) {
    std::vector<std::vector<float>> numeric_data;
    
    // Convert each string field to float
    for (const auto& record : data) {
        std::vector<float> numeric_record;
        for (const auto& field : record) {
            numeric_record.push_back(stringToFloat(field));
        }
        numeric_data.push_back(numeric_record);
    }
  
    // Print preprocessed data for debugging
    std::cout << "Preprocessed data..." << std::endl;
    std::cout << "Numeric data:" << std::endl;
    int samples_printed = 0;
    for (const auto& numeric_record : numeric_data) {
        // Print each value in the record
        for (const auto& value : numeric_record) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        samples_printed++;
        // Stop printing if we've reached the specified number of samples
        if (samples_printed >= num_samples) {
            break;
        }
    }

    return numeric_data;
}


/*
 __   __                      _____                    __   __                         
 \ \ / /   _ _ __  _   _ ___ | ____|_ __ ___  _ __ ___ \ \ / /   _ _ __ __ _ _   _ _ __  
  \ V / | | | '_ \| | | / __||  _| | '_ ` _ \| '__/ _ \ \ V / | | | '__/ _` | | | | '_ \ 
   | || |_| | | | | |_| \__ \| |___| | | | | | | |  __/  | || |_| | | | (_| | |_| | | | |
   |_| \__,_|_| |_|\__,_|___/|_____|_| |_| |_|_|  \___|  |_| \__,_|_|  \__, |\__,_|_| |_|
                                                                       |___/             
*/
