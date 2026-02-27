#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

struct Statistics {
    double mean;
    double median;
    double std_dev;
    double min;
    double max;
    double q1;
    double q3;
    double iqr;
    double mad;
    int count;
};

struct AnomalyResult {
    int index;
    double value;
    double score;
    bool is_anomaly;
    std::string reason;
};

class StatisticalAnalyzer {
public:
    static Statistics calculateStatistics(const std::vector<double>& data);
    static std::vector<AnomalyResult> detectZScore(const std::vector<double>& data, double threshold);
    static std::vector<AnomalyResult> detectIQR(const std::vector<double>& data, double multiplier = 1.5);
    static std::vector<AnomalyResult> detectMAD(const std::vector<double>& data, double threshold = 3.5);
    static std::vector<AnomalyResult> detectModifiedZScore(const std::vector<double>& data, double threshold = 3.5);
    
private:
    static double calculateMean(const std::vector<double>& data);
    static double calculateMedian(std::vector<double> data);
    static double calculateStdDev(const std::vector<double>& data, double mean);
    static double calculateMAD(const std::vector<double>& data, double median);
};

#endif // STATISTICS_H
