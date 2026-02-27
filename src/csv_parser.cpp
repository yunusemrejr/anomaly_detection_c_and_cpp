#include "csv_parser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

std::vector<std::string> CSVParser::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        
        if (c == '"') {
            in_quotes = !in_quotes;
        } else if (c == delimiter && !in_quotes) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    
    tokens.push_back(token);
    return tokens;
}

double CSVParser::parseDouble(const std::string& str, bool& success) {
    success = true;
    
    // Trim whitespace
    std::string trimmed = str;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);
    
    if (trimmed.empty()) {
        success = false;
        return 0.0;
    }
    
    try {
        size_t pos;
        double value = std::stod(trimmed, &pos);
        
        // Check if entire string was consumed
        if (pos != trimmed.length()) {
            success = false;
            return 0.0;
        }
        
        return value;
    } catch (...) {
        success = false;
        return 0.0;
    }
}

std::vector<double> CSVParser::selectColumns(const std::vector<double>& row, 
                                            const std::vector<int>& columns) {
    if (columns.empty()) {
        return row;
    }
    
    std::vector<double> selected;
    for (int col : columns) {
        if (col >= 0 && static_cast<size_t>(col) < row.size()) {
            selected.push_back(row[col]);
        }
    }
    
    return selected;
}

std::vector<std::vector<double>> CSVParser::parseStream(std::istream& stream,
                                                        bool has_header,
                                                        const std::vector<int>& columns) {
    std::vector<std::vector<double>> data;
    std::string line;
    bool first_line = true;
    
    while (std::getline(stream, line)) {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }
        
        // Skip header if specified
        if (first_line && has_header) {
            first_line = false;
            continue;
        }
        first_line = false;
        
        std::vector<std::string> tokens = splitLine(line);
        std::vector<double> row;
        
        for (const auto& token : tokens) {
            bool success;
            double value = parseDouble(token, success);
            
            if (success) {
                row.push_back(value);
            }
            // Skip invalid values silently
        }
        
        if (!row.empty()) {
            std::vector<double> selected = selectColumns(row, columns);
            if (!selected.empty()) {
                data.push_back(selected);
            }
        }
    }
    
    return data;
}

std::vector<std::vector<double>> CSVParser::parseFile(const std::string& filename,
                                                      bool has_header,
                                                      const std::vector<int>& columns) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    
    auto data = parseStream(file, has_header, columns);
    file.close();
    
    return data;
}

std::vector<double> CSVParser::flatten(const std::vector<std::vector<double>>& data) {
    std::vector<double> flattened;
    
    for (const auto& row : data) {
        flattened.insert(flattened.end(), row.begin(), row.end());
    }
    
    return flattened;
}
