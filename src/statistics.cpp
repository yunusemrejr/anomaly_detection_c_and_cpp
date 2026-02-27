#include "statistics.h"
#include <algorithm>
#include <cmath>
#include <numeric>

double StatisticalAnalyzer::calculateMean(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double StatisticalAnalyzer::calculateMedian(std::vector<double> data) {
    if (data.empty()) return 0.0;
    
    std::sort(data.begin(), data.end());
    size_t n = data.size();
    
    if (n % 2 == 0) {
        return (data[n/2 - 1] + data[n/2]) / 2.0;
    } else {
        return data[n/2];
    }
}

double StatisticalAnalyzer::calculateStdDev(const std::vector<double>& data, double mean) {
    if (data.size() <= 1) return 0.0;
    
    double sum_sq = 0.0;
    for (double val : data) {
        double diff = val - mean;
        sum_sq += diff * diff;
    }
    
    return std::sqrt(sum_sq / data.size());
}

double StatisticalAnalyzer::calculateMAD(const std::vector<double>& data, double median) {
    if (data.empty()) return 0.0;
    
    std::vector<double> deviations;
    deviations.reserve(data.size());
    
    for (double val : data) {
        deviations.push_back(std::abs(val - median));
    }
    
    return calculateMedian(deviations);
}

Statistics StatisticalAnalyzer::calculateStatistics(const std::vector<double>& data) {
    Statistics stats;
    
    if (data.empty()) {
        stats.mean = stats.median = stats.std_dev = 0.0;
        stats.min = stats.max = stats.q1 = stats.q3 = stats.iqr = stats.mad = 0.0;
        stats.count = 0;
        return stats;
    }
    
    stats.count = data.size();
    stats.mean = calculateMean(data);
    
    std::vector<double> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());
    
    stats.min = sorted_data.front();
    stats.max = sorted_data.back();
    stats.median = calculateMedian(sorted_data);
    stats.std_dev = calculateStdDev(data, stats.mean);
    
    // Calculate quartiles
    size_t n = sorted_data.size();
    if (n >= 4) {
        size_t q1_idx = n / 4;
        size_t q3_idx = 3 * n / 4;
        stats.q1 = sorted_data[q1_idx];
        stats.q3 = sorted_data[q3_idx];
        stats.iqr = stats.q3 - stats.q1;
    } else {
        stats.q1 = stats.min;
        stats.q3 = stats.max;
        stats.iqr = stats.max - stats.min;
    }
    
    stats.mad = calculateMAD(data, stats.median);
    
    return stats;
}

std::vector<AnomalyResult> StatisticalAnalyzer::detectZScore(const std::vector<double>& data, double threshold) {
    std::vector<AnomalyResult> results;
    
    if (data.empty()) return results;
    
    double mean = calculateMean(data);
    double std_dev = calculateStdDev(data, mean);
    
    if (std_dev == 0.0) {
        // All values are the same, no anomalies
        for (size_t i = 0; i < data.size(); ++i) {
            results.push_back({static_cast<int>(i), data[i], 0.0, false, "No variation in data"});
        }
        return results;
    }
    
    for (size_t i = 0; i < data.size(); ++i) {
        double z_score = std::abs((data[i] - mean) / std_dev);
        bool is_anomaly = z_score > threshold;
        
        std::string reason = is_anomaly ? 
            "Z-score " + std::to_string(z_score) + " exceeds threshold " + std::to_string(threshold) :
            "Normal";
        
        results.push_back({static_cast<int>(i), data[i], z_score, is_anomaly, reason});
    }
    
    return results;
}

std::vector<AnomalyResult> StatisticalAnalyzer::detectIQR(const std::vector<double>& data, double multiplier) {
    std::vector<AnomalyResult> results;
    
    if (data.empty()) return results;
    
    Statistics stats = calculateStatistics(data);
    
    double lower_bound = stats.q1 - multiplier * stats.iqr;
    double upper_bound = stats.q3 + multiplier * stats.iqr;
    
    for (size_t i = 0; i < data.size(); ++i) {
        bool is_anomaly = data[i] < lower_bound || data[i] > upper_bound;
        double score = 0.0;
        
        if (data[i] < lower_bound) {
            score = (lower_bound - data[i]) / stats.iqr;
        } else if (data[i] > upper_bound) {
            score = (data[i] - upper_bound) / stats.iqr;
        }
        
        std::string reason = is_anomaly ?
            "Outside IQR bounds [" + std::to_string(lower_bound) + ", " + std::to_string(upper_bound) + "]" :
            "Normal";
        
        results.push_back({static_cast<int>(i), data[i], score, is_anomaly, reason});
    }
    
    return results;
}

std::vector<AnomalyResult> StatisticalAnalyzer::detectMAD(const std::vector<double>& data, double threshold) {
    std::vector<AnomalyResult> results;
    
    if (data.empty()) return results;
    
    double median = calculateMedian(std::vector<double>(data));
    double mad = calculateMAD(data, median);
    
    if (mad == 0.0) {
        // All values are the same, no anomalies
        for (size_t i = 0; i < data.size(); ++i) {
            results.push_back({static_cast<int>(i), data[i], 0.0, false, "No variation in data"});
        }
        return results;
    }
    
    const double consistency_constant = 1.4826; // For normal distribution
    
    for (size_t i = 0; i < data.size(); ++i) {
        double modified_z = consistency_constant * std::abs(data[i] - median) / mad;
        bool is_anomaly = modified_z > threshold;
        
        std::string reason = is_anomaly ?
            "MAD score " + std::to_string(modified_z) + " exceeds threshold " + std::to_string(threshold) :
            "Normal";
        
        results.push_back({static_cast<int>(i), data[i], modified_z, is_anomaly, reason});
    }
    
    return results;
}

std::vector<AnomalyResult> StatisticalAnalyzer::detectModifiedZScore(const std::vector<double>& data, double threshold) {
    // Modified Z-score is similar to MAD method
    return detectMAD(data, threshold);
}
