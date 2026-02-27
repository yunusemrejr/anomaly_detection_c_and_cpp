#include "anomaly_detection.h"
#include "cli_parser.h"
#include "csv_parser.h"
#include "statistics.h"
#include "output_formatter.h"
#include <iostream>
#include <sstream>

// Legacy function for backward compatibility
int printMessage(const std::string& message) {
    std::cout << message;
    return 0;
}

// Legacy function for backward compatibility
bool isCSVFormat(const std::string& str) {
    std::istringstream iss(str);
    std::string token;
    int numCommas = 0;
    int numQuotes = 0;

    while (std::getline(iss, token, ',')) {
        numCommas++;
        for (char ch : token) {
            if (ch == '\"') {
                numQuotes++;
            }
        }
    }

    return numCommas > 1 && numQuotes % 2 == 0;
}

// Legacy function for backward compatibility
int printStars() {
    for(int i = 0; i < 5; i++){
        std::cout << "******" << std::endl;
    }
    return 0;
}

// Modern main function with CLI support
int main(int argc, char* argv[]) {
    // Parse command-line arguments
    CLIOptions options = CLIParser::parse(argc, argv);
    
    // Handle help and version
    if (options.show_help) {
        CLIParser::printHelp();
        return 0;
    }
    
    if (options.show_version) {
        CLIParser::printVersion();
        return 0;
    }
    
    try {
        std::vector<double> data;
        
        // Load data from file or stdin
        if (options.use_stdin) {
            // Legacy mode: read from stdin
            std::stringstream input;
            std::string line;
            const size_t maxInputSize = 10000;

            while (std::getline(std::cin, line) && 
                   input.str().size() + line.size() + 1 < maxInputSize) {
                input << line << '\n';
            }

            // Check if input is in CSV format
            if (!isCSVFormat(input.str())) {
                std::cerr << OutputFormatter::colorize("Error: Input data is not in CSV format.", Colors::RED) << std::endl;
                std::cerr << "Use --help for usage information." << std::endl;
                return 1;
            }

            // Parse CSV from stdin
            std::istringstream iss(input.str());
            auto parsed_data = CSVParser::parseStream(iss, options.has_header, options.columns);
            data = CSVParser::flatten(parsed_data);
            
            if (!options.verbose) {
                // Show minimal legacy-style output for stdin mode
                std::cout << "Data points loaded: " << data.size() << std::endl;
            }
        } else {
            // Modern mode: read from file
            auto parsed_data = CSVParser::parseFile(options.input_file, options.has_header, options.columns);
            data = CSVParser::flatten(parsed_data);
            
            if (options.verbose) {
                std::cout << OutputFormatter::colorize("✓ Loaded " + std::to_string(data.size()) + 
                                                      " data points from " + options.input_file, 
                                                      Colors::GREEN) << std::endl;
            }
        }
        
        // Validate data
        if (data.empty()) {
            std::cerr << OutputFormatter::colorize("Error: No valid data found.", Colors::RED) << std::endl;
            return 1;
        }
        
        // Calculate statistics
        Statistics stats = StatisticalAnalyzer::calculateStatistics(data);
        
        // Detect anomalies using selected method
        std::vector<AnomalyResult> anomalies;
        
        switch (options.method) {
            case DetectionMethod::ZSCORE:
                anomalies = StatisticalAnalyzer::detectZScore(data, options.threshold);
                break;
            case DetectionMethod::IQR:
                anomalies = StatisticalAnalyzer::detectIQR(data, options.threshold);
                break;
            case DetectionMethod::MAD:
                anomalies = StatisticalAnalyzer::detectMAD(data, options.threshold);
                break;
            case DetectionMethod::MODIFIED_ZSCORE:
                anomalies = StatisticalAnalyzer::detectModifiedZScore(data, options.threshold);
                break;
        }
        
        // Output results
        if (options.output_file.empty()) {
            // Print to stdout
            switch (options.format) {
                case OutputFormat::TERMINAL:
                    OutputFormatter::printTerminal(data, anomalies, stats, options.verbose);
                    break;
                case OutputFormat::JSON:
                    std::cout << OutputFormatter::toJSON(data, anomalies, stats);
                    break;
                case OutputFormat::CSV:
                    std::cout << OutputFormatter::toCSV(data, anomalies);
                    break;
            }
        } else {
            // Save to file
            std::string content;
            switch (options.format) {
                case OutputFormat::TERMINAL:
                    // For file output, use JSON format even if terminal was specified
                    content = OutputFormatter::toJSON(data, anomalies, stats);
                    break;
                case OutputFormat::JSON:
                    content = OutputFormatter::toJSON(data, anomalies, stats);
                    break;
                case OutputFormat::CSV:
                    content = OutputFormatter::toCSV(data, anomalies);
                    break;
            }
            
            OutputFormatter::saveToFile(options.output_file, content);
            
            // Also print summary to terminal
            if (options.verbose) {
                OutputFormatter::printTerminal(data, anomalies, stats, false);
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << OutputFormatter::colorize("Error: " + std::string(e.what()), Colors::RED) << std::endl;
        return 1;
    }
    
    return 0;
}
