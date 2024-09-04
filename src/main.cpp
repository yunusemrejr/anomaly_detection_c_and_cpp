#include "anomaly_detection.h"

// Function to print messages to standard output
// Returns 0 to indicate successful execution
int printMessage(const std::string& message) {
    std::cout << message;
    return 0;
}

// Function to check if a string is in CSV format
// Returns true if the string contains multiple comma-separated values
// and has balanced quotation marks (if any)
bool isCSVFormat(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    int numCommas = 0;
    int numQuotes = 0;

    // Count commas and quotation marks in the string
    while (std::getline(iss, token, ',')) {
        numCommas++;
        for (char ch : token) {
            if (ch == '"') {
                numQuotes++;
            }
        }
    }

    // Check if there are multiple commas and an even number of quotation marks
    return numCommas > 1 && numQuotes % 2 == 0;
}

// Function to print a line of stars
// Used for visual separation in the output
int printStars() {
    int i;
    for(i=0; i < 5; i++){
        std::cout << "******" << std::endl;
    }
    return 0;
}

// Main function
int main() {
    printStars();
    printMessage("Welcome to Anomaly Detector!\n");
    printMessage("Input your data in CSV format below:\n");
    printStars();
    
    // Read input data from standard input
    std::stringstream input;
    std::string line;
    const size_t maxInputSize = 10000;

    // Read lines until EOF or maximum input size is reached
    while (std::getline(std::cin, line) && input.str().size() + line.size() + 1 /* Account for newline character */ < maxInputSize) {
        input << line << '\n';
    }

    // Validate input data format
    if (!isCSVFormat(input.str())) {
        printStars();
        std::cerr << "Error: Input data is not in CSV format.\n";
        printStars();
        return 1; // Return error code
    }

    // Parse the CSV data into a vector of string vectors
    std::vector<std::vector<std::string>> records;
    std::istringstream iss(input.str());

    while (std::getline(iss, line)) {
        std::vector<std::string> record;
        std::istringstream recordStream(line);
        std::string token;

        while (std::getline(recordStream, token, ',')) {
            // Optional: Trim whitespace from start and end of token here if needed
            record.push_back(token);
        }
        records.push_back(record);
    }

    // Print the formatted CSV data
    printStars();
    std::cout << "You entered these:\n";
     
    // Vector to store float data extracted from records
    std::vector<float> data;

    // Convert string records to float and print them
    for (const auto& record : records) {
        for (size_t i = 0; i < record.size(); ++i) {
            // Convert each string in the record to float and add it to the data vector
            data.push_back(std::stof(record[i]));
            std::cout << record[i];
            if (i < record.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
    printStars();

    // Preprocess the data
    auto processed_records = preprocess_data(records, records.size());
    printStars();

    // Flatten the processed records into a single vector
    std::vector<float> flattened_data;
    for(const auto& row : processed_records){
        flattened_data.insert(flattened_data.end(), row.begin(), row.end());
    }

    // Extract features from the flattened data
    float** features = extract_features(flattened_data.data(), flattened_data.size());
    
    // Detect and print anomalies
    auto anomalies = print_anomalies(flattened_data.data(), flattened_data.size());

    printStars();

    // Free allocated memory for features
    for (size_t i = 0; i < flattened_data.size(); ++i) {
        free(features[i]);
    }
    free(features);

    return 0; // Return 0 to indicate successful execution
}

/*
 __   __                      _____                    __   __                         
 \ \ / /   _ _ __  _   _ ___ | ____|_ __ ___  _ __ ___ \ \ / /   _ _ __ __ _ _   _ _ __  
  \ V / | | | '_ \| | | / __||  _| | '_ ` _ \| '__/ _ \ \ V / | | | '__/ _` | | | | '_ \ 
   | || |_| | | | | |_| \__ \| |___| | | | | | | |  __/  | || |_| | | | (_| | |_| | | | |
   |_| \__,_|_| |_|\__,_|___/|_____|_| |_| |_|_|  \___|  |_| \__,_|_|  \__, |\__,_|_| |_|
                                                                       |___/             
*/

