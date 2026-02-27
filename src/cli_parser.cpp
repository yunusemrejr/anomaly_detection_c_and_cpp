#include "cli_parser.h"
#include <iostream>
#include <algorithm>

void CLIParser::printHelp() {
    std::cout << R"(
╔═══════════════════════════════════════════════════════════════════════════╗
║                    Anomaly Detection Tool v2.0                            ║
║                  Advanced Statistical Anomaly Detection                   ║
╚═══════════════════════════════════════════════════════════════════════════╝

USAGE:
    anomaly_detection [OPTIONS]

OPTIONS:
    -i, --input <file>       Input CSV file (if not specified, reads from stdin)
    -o, --output <file>      Output file (if not specified, prints to stdout)
    -m, --method <method>    Detection method (default: zscore)
                             Available: zscore, iqr, mad, modified-zscore
    -f, --format <format>    Output format (default: terminal)
                             Available: terminal, json, csv
    -t, --threshold <value>  Threshold value (default: 2.0 for zscore/mad, 1.5 for iqr)
    -c, --columns <cols>     Comma-separated column indices to analyze (0-based)
                             Example: -c 0,2,3
    --header                 First row is header (skip it)
    -v, --verbose            Verbose output with statistics
    -h, --help               Show this help message
    --version                Show version information

DETECTION METHODS:
    zscore           Standard Z-score method (mean ± threshold × std_dev)
    iqr              Interquartile Range method (Q1 - 1.5×IQR, Q3 + 1.5×IQR)
    mad              Median Absolute Deviation (robust to outliers)
    modified-zscore  Modified Z-score using MAD (similar to mad)

OUTPUT FORMATS:
    terminal         Colorized terminal output with summary
    json             JSON format with detailed statistics
    csv              CSV format with anomaly flags

EXAMPLES:
    # Read from stdin with default settings
    echo "1,2,3,4,100" | anomaly_detection

    # Analyze CSV file with IQR method
    anomaly_detection -i data.csv -m iqr

    # Output to JSON file with verbose statistics
    anomaly_detection -i data.csv -f json -o results.json -v

    # Analyze specific columns with custom threshold
    anomaly_detection -i data.csv -c 0,2 -t 3.0 --header

AUTHOR:
    Enhanced by Blackbox AI - Statistical Analysis Suite

)" << std::endl;
}

void CLIParser::printVersion() {
    std::cout << R"(
Anomaly Detection Tool v2.0.0
Build: 2026-02-27
C++17 | Statistical Analysis | Multi-Method Detection
)" << std::endl;
}

DetectionMethod CLIParser::parseMethod(const std::string& method) {
    std::string lower = method;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    if (lower == "zscore" || lower == "z-score") {
        return DetectionMethod::ZSCORE;
    } else if (lower == "iqr") {
        return DetectionMethod::IQR;
    } else if (lower == "mad") {
        return DetectionMethod::MAD;
    } else if (lower == "modified-zscore" || lower == "modified_zscore") {
        return DetectionMethod::MODIFIED_ZSCORE;
    } else {
        std::cerr << "Warning: Unknown method '" << method << "', using zscore" << std::endl;
        return DetectionMethod::ZSCORE;
    }
}

OutputFormat CLIParser::parseFormat(const std::string& format) {
    std::string lower = format;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    if (lower == "terminal" || lower == "console") {
        return OutputFormat::TERMINAL;
    } else if (lower == "json") {
        return OutputFormat::JSON;
    } else if (lower == "csv") {
        return OutputFormat::CSV;
    } else {
        std::cerr << "Warning: Unknown format '" << format << "', using terminal" << std::endl;
        return OutputFormat::TERMINAL;
    }
}

CLIOptions CLIParser::parse(int argc, char* argv[]) {
    CLIOptions options;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            options.show_help = true;
            return options;
        } else if (arg == "--version") {
            options.show_version = true;
            return options;
        } else if (arg == "-i" || arg == "--input") {
            if (i + 1 < argc) {
                options.input_file = argv[++i];
                options.use_stdin = false;
            } else {
                std::cerr << "Error: " << arg << " requires a filename" << std::endl;
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                options.output_file = argv[++i];
            } else {
                std::cerr << "Error: " << arg << " requires a filename" << std::endl;
            }
        } else if (arg == "-m" || arg == "--method") {
            if (i + 1 < argc) {
                options.method = parseMethod(argv[++i]);
            } else {
                std::cerr << "Error: " << arg << " requires a method name" << std::endl;
            }
        } else if (arg == "-f" || arg == "--format") {
            if (i + 1 < argc) {
                options.format = parseFormat(argv[++i]);
            } else {
                std::cerr << "Error: " << arg << " requires a format name" << std::endl;
            }
        } else if (arg == "-t" || arg == "--threshold") {
            if (i + 1 < argc) {
                try {
                    options.threshold = std::stod(argv[++i]);
                } catch (...) {
                    std::cerr << "Error: Invalid threshold value" << std::endl;
                }
            } else {
                std::cerr << "Error: " << arg << " requires a numeric value" << std::endl;
            }
        } else if (arg == "-c" || arg == "--columns") {
            if (i + 1 < argc) {
                std::string cols = argv[++i];
                std::string token;
                for (char c : cols) {
                    if (c == ',') {
                        if (!token.empty()) {
                            try {
                                options.columns.push_back(std::stoi(token));
                            } catch (...) {
                                std::cerr << "Warning: Invalid column index '" << token << "'" << std::endl;
                            }
                            token.clear();
                        }
                    } else {
                        token += c;
                    }
                }
                if (!token.empty()) {
                    try {
                        options.columns.push_back(std::stoi(token));
                    } catch (...) {
                        std::cerr << "Warning: Invalid column index '" << token << "'" << std::endl;
                    }
                }
            } else {
                std::cerr << "Error: " << arg << " requires column indices" << std::endl;
            }
        } else if (arg == "--header") {
            options.has_header = true;
        } else if (arg == "-v" || arg == "--verbose") {
            options.verbose = true;
        } else {
            std::cerr << "Warning: Unknown option '" << arg << "'" << std::endl;
        }
    }
    
    // Adjust default threshold for IQR method
    if (options.method == DetectionMethod::IQR && options.threshold == 2.0) {
        options.threshold = 1.5;
    }
    
    return options;
}
