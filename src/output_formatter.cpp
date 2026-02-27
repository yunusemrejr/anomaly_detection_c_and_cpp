#include "output_formatter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

std::string OutputFormatter::colorize(const std::string& text, const std::string& color) {
    return color + text + Colors::RESET;
}

std::string OutputFormatter::escapeJSON(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default: oss << c; break;
        }
    }
    return oss.str();
}

void OutputFormatter::printTerminal(const std::vector<double>& data,
                                   const std::vector<AnomalyResult>& anomalies,
                                   const Statistics& stats,
                                   bool verbose) {
    std::cout << "\n";
    std::cout << colorize("╔═══════════════════════════════════════════════════════════════════════════╗", Colors::CYAN) << "\n";
    std::cout << colorize("║                      ANOMALY DETECTION RESULTS                            ║", Colors::CYAN) << "\n";
    std::cout << colorize("╚═══════════════════════════════════════════════════════════════════════════╝", Colors::CYAN) << "\n\n";
    
    // Count anomalies
    int anomaly_count = 0;
    for (const auto& result : anomalies) {
        if (result.is_anomaly) {
            anomaly_count++;
        }
    }
    
    // Summary
    std::cout << colorize("📊 SUMMARY", Colors::BOLD + Colors::BLUE) << "\n";
    std::cout << "   Total data points: " << colorize(std::to_string(data.size()), Colors::GREEN) << "\n";
    std::cout << "   Anomalies detected: " << colorize(std::to_string(anomaly_count), Colors::RED) << "\n";
    std::cout << "   Normal data points: " << colorize(std::to_string(data.size() - anomaly_count), Colors::GREEN) << "\n";
    
    if (data.size() > 0) {
        double anomaly_rate = (100.0 * anomaly_count) / data.size();
        std::cout << "   Anomaly rate: " << colorize(std::to_string(anomaly_rate) + "%", 
                                                     anomaly_rate > 10 ? Colors::RED : Colors::YELLOW) << "\n";
    }
    
    // Statistics
    if (verbose) {
        std::cout << "\n" << colorize("📈 STATISTICS", Colors::BOLD + Colors::BLUE) << "\n";
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "   Mean:              " << stats.mean << "\n";
        std::cout << "   Median:            " << stats.median << "\n";
        std::cout << "   Std Deviation:     " << stats.std_dev << "\n";
        std::cout << "   Min:               " << stats.min << "\n";
        std::cout << "   Max:               " << stats.max << "\n";
        std::cout << "   Q1 (25%):          " << stats.q1 << "\n";
        std::cout << "   Q3 (75%):          " << stats.q3 << "\n";
        std::cout << "   IQR:               " << stats.iqr << "\n";
        std::cout << "   MAD:               " << stats.mad << "\n";
    }
    
    // Anomalies
    if (anomaly_count > 0) {
        std::cout << "\n" << colorize("🚨 DETECTED ANOMALIES", Colors::BOLD + Colors::RED) << "\n";
        std::cout << std::fixed << std::setprecision(4);
        
        int displayed = 0;
        for (const auto& result : anomalies) {
            if (result.is_anomaly) {
                std::cout << "   [" << colorize(std::to_string(result.index), Colors::YELLOW) << "] ";
                std::cout << "Value: " << colorize(std::to_string(result.value), Colors::RED);
                std::cout << " | Score: " << std::to_string(result.score);
                
                if (verbose) {
                    std::cout << " | " << result.reason;
                }
                std::cout << "\n";
                
                displayed++;
                if (!verbose && displayed >= 10 && anomaly_count > 10) {
                    std::cout << "   ... and " << (anomaly_count - 10) << " more anomalies\n";
                    std::cout << "   (use -v flag to see all)\n";
                    break;
                }
            }
        }
    } else {
        std::cout << "\n" << colorize("✓ No anomalies detected!", Colors::BOLD + Colors::GREEN) << "\n";
    }
    
    std::cout << "\n";
}

std::string OutputFormatter::toJSON(const std::vector<double>& data,
                                   const std::vector<AnomalyResult>& anomalies,
                                   const Statistics& stats) {
    std::ostringstream json;
    json << std::fixed << std::setprecision(6);
    
    json << "{\n";
    json << "  \"summary\": {\n";
    json << "    \"total_points\": " << data.size() << ",\n";
    
    int anomaly_count = 0;
    for (const auto& result : anomalies) {
        if (result.is_anomaly) anomaly_count++;
    }
    
    json << "    \"anomaly_count\": " << anomaly_count << ",\n";
    json << "    \"normal_count\": " << (data.size() - anomaly_count) << ",\n";
    
    if (data.size() > 0) {
        json << "    \"anomaly_rate\": " << (100.0 * anomaly_count / data.size()) << "\n";
    } else {
        json << "    \"anomaly_rate\": 0\n";
    }
    
    json << "  },\n";
    
    json << "  \"statistics\": {\n";
    json << "    \"mean\": " << stats.mean << ",\n";
    json << "    \"median\": " << stats.median << ",\n";
    json << "    \"std_dev\": " << stats.std_dev << ",\n";
    json << "    \"min\": " << stats.min << ",\n";
    json << "    \"max\": " << stats.max << ",\n";
    json << "    \"q1\": " << stats.q1 << ",\n";
    json << "    \"q3\": " << stats.q3 << ",\n";
    json << "    \"iqr\": " << stats.iqr << ",\n";
    json << "    \"mad\": " << stats.mad << ",\n";
    json << "    \"count\": " << stats.count << "\n";
    json << "  },\n";
    
    json << "  \"anomalies\": [\n";
    bool first = true;
    for (const auto& result : anomalies) {
        if (result.is_anomaly) {
            if (!first) json << ",\n";
            first = false;
            
            json << "    {\n";
            json << "      \"index\": " << result.index << ",\n";
            json << "      \"value\": " << result.value << ",\n";
            json << "      \"score\": " << result.score << ",\n";
            json << "      \"reason\": \"" << escapeJSON(result.reason) << "\"\n";
            json << "    }";
        }
    }
    json << "\n  ],\n";
    
    json << "  \"data\": [\n";
    for (size_t i = 0; i < data.size(); ++i) {
        json << "    " << data[i];
        if (i < data.size() - 1) json << ",";
        json << "\n";
    }
    json << "  ]\n";
    
    json << "}\n";
    
    return json.str();
}

std::string OutputFormatter::toCSV(const std::vector<double>& data,
                                  const std::vector<AnomalyResult>& anomalies) {
    std::ostringstream csv;
    csv << std::fixed << std::setprecision(6);
    
    csv << "index,value,is_anomaly,score,reason\n";
    
    for (const auto& result : anomalies) {
        csv << result.index << ",";
        csv << result.value << ",";
        csv << (result.is_anomaly ? "1" : "0") << ",";
        csv << result.score << ",";
        csv << "\"" << result.reason << "\"\n";
    }
    
    return csv.str();
}

void OutputFormatter::saveToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + filename);
    }
    
    file << content;
    file.close();
    
    std::cout << colorize("✓ Results saved to: " + filename, Colors::GREEN) << "\n";
}
