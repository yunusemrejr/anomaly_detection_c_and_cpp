#ifndef OUTPUT_FORMATTER_H
#define OUTPUT_FORMATTER_H

#include <string>
#include <vector>
#include "statistics.h"

class OutputFormatter {
public:
    static void printTerminal(const std::vector<double>& data, 
                             const std::vector<AnomalyResult>& anomalies,
                             const Statistics& stats,
                             bool verbose = false);
    
    static std::string toJSON(const std::vector<double>& data,
                             const std::vector<AnomalyResult>& anomalies,
                             const Statistics& stats);
    
    static std::string toCSV(const std::vector<double>& data,
                            const std::vector<AnomalyResult>& anomalies);
    
    static void saveToFile(const std::string& filename, const std::string& content);
    
private:
    static std::string colorize(const std::string& text, const std::string& color);
    static std::string escapeJSON(const std::string& str);
};

// ANSI color codes
namespace Colors {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string BOLD = "\033[1m";
}

#endif // OUTPUT_FORMATTER_H
