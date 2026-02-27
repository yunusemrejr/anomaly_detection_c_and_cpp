# 📊 Anomaly Detection Software v2.0

<div align="center">

**Advanced Statistical Anomaly Detection Tool**

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

*A modern, professional C/C++ tool for detecting anomalies in numerical datasets using multiple statistical methods.*

</div>

---

## ✨ What's New in v2.0

🎯 **Multiple Detection Algorithms** - Choose from Z-score, IQR, MAD, and Modified Z-score methods  
🎨 **Beautiful Terminal Output** - Colorized, formatted results with comprehensive statistics  
📊 **Multiple Output Formats** - Terminal, JSON, and CSV export options  
⚙️ **Flexible CLI Interface** - Modern command-line arguments with extensive options  
📁 **File & Stream Support** - Read from files or stdin for pipeline integration  
🔧 **Configurable Thresholds** - Customize sensitivity for your use case  
📈 **Enhanced Statistics** - Mean, median, quartiles, IQR, MAD, and more  
🎯 **Column Selection** - Analyze specific columns from multi-column datasets  

---

## 🚀 Quick Start

### Build the Project

```bash
make clean
make
```

### Run with Sample Data

```bash
# Using file input
./bin/anomaly_detection -i examples/sample_data.csv -v

# Using stdin (backward compatible)
echo "1,2,3,4,5,100" | ./bin/anomaly_detection

# With specific detection method
./bin/anomaly_detection -i examples/sample_data.csv -m iqr

# Export to JSON
./bin/anomaly_detection -i examples/sample_data.csv -f json -o results.json
```

---

## 📖 Usage

### Command-Line Options

```
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
    -h, --help               Show help message
    --version                Show version information
```

### Detection Methods

#### 1. **Z-Score Method** (default)
- **Best for**: Normally distributed data
- **How it works**: Flags values more than `threshold` standard deviations from the mean
- **Formula**: `|value - mean| > threshold × std_dev`
- **Default threshold**: 2.0

```bash
./bin/anomaly_detection -i data.csv -m zscore -t 2.0
```

#### 2. **IQR (Interquartile Range) Method**
- **Best for**: Data with outliers, non-normal distributions
- **How it works**: Uses quartiles to define normal range
- **Formula**: `value < Q1 - 1.5×IQR` or `value > Q3 + 1.5×IQR`
- **Default threshold**: 1.5

```bash
./bin/anomaly_detection -i data.csv -m iqr -t 1.5
```

#### 3. **MAD (Median Absolute Deviation) Method**
- **Best for**: Robust detection, resistant to outliers
- **How it works**: Uses median instead of mean for robustness
- **Formula**: `1.4826 × |value - median| / MAD > threshold`
- **Default threshold**: 3.5

```bash
./bin/anomaly_detection -i data.csv -m mad -t 3.5
```

#### 4. **Modified Z-Score Method**
- **Best for**: Similar to MAD, robust outlier detection
- **How it works**: Modified version of Z-score using MAD
- **Default threshold**: 3.5

```bash
./bin/anomaly_detection -i data.csv -m modified-zscore
```

---

## 📊 Examples

### Example 1: Basic Analysis

```bash
./bin/anomaly_detection -i examples/sample_data.csv -v
```

**Output:**
```
╔═══════════════════════════════════════════════════════════════════════════╗
║                      ANOMALY DETECTION RESULTS                            ║
╚═══════════════════════════════════════════════════════════════════════════╝

📊 SUMMARY
   Total data points: 60
   Anomalies detected: 2
   Normal data points: 58
   Anomaly rate: 3.33%

📈 STATISTICS
   Mean:              24.5167
   Median:            23.0500
   Std Deviation:     15.2341
   Min:               -15.2000
   Max:               95.5000
   Q1 (25%):          22.7000
   Q3 (75%):          46.1000
   IQR:               23.4000
   MAD:               1.4500

🚨 DETECTED ANOMALIES
   [15] Value: 95.5000 | Score: 4.6589
   [35] Value: -15.2000 | Score: 2.6123
```

### Example 2: Analyze Specific Columns

```bash
# Analyze only the first column (temperature)
./bin/anomaly_detection -i examples/sample_data.csv -c 0 --header -v
```

### Example 3: Export to JSON

```bash
./bin/anomaly_detection -i examples/sample_data.csv -f json -o results.json
```

**results.json:**
```json
{
  "summary": {
    "total_points": 60,
    "anomaly_count": 2,
    "normal_count": 58,
    "anomaly_rate": 3.333333
  },
  "statistics": {
    "mean": 24.516667,
    "median": 23.050000,
    "std_dev": 15.234100,
    ...
  },
  "anomalies": [
    {
      "index": 15,
      "value": 95.500000,
      "score": 4.658900,
      "reason": "Z-score 4.658900 exceeds threshold 2.000000"
    }
  ]
}
```

### Example 4: Pipeline Integration

```bash
# Generate data and pipe to anomaly detector
cat sensor_data.csv | ./bin/anomaly_detection -m iqr

# Chain with other tools
./bin/anomaly_detection -i data.csv -f csv | grep "1" | wc -l
```

---

## 🏗️ Architecture

### Project Structure

```
anomaly_detection/
├── bin/                    # Compiled binaries
├── obj/                    # Object files
├── include/                # Header files
│   ├── anomaly_detection.h # Core detection (legacy)
│   ├── cli_parser.h        # Command-line parsing
│   ├── csv_parser.h        # CSV file parsing
│   ├── statistics.h        # Statistical algorithms
│   └── output_formatter.h  # Output formatting
├── src/                    # Source files
│   ├── main.cpp            # Main entry point
│   ├── cli_parser.cpp      # CLI implementation
│   ├── csv_parser.cpp      # CSV parsing
│   ├── statistics.cpp      # Statistical methods
│   ├── output_formatter.cpp# Output formatting
│   ├── detect_anomalies.c  # Core detection (C)
│   ├── extract_features.c  # Feature extraction
│   ├── preprocess_data.cpp # Data preprocessing
│   └── print_anomalies.cpp # Legacy output
├── examples/               # Sample datasets
│   ├── sample_data.csv
│   ├── simple_data.csv
│   └── network_traffic.csv
├── Makefile               # Build configuration
├── README.md              # This file
└── LICENSE                # MIT License
```

### Core Components

1. **CLI Parser** - Modern argument parsing with validation
2. **CSV Parser** - Robust CSV reading with error handling
3. **Statistical Analyzer** - Multiple detection algorithms
4. **Output Formatter** - Beautiful terminal, JSON, and CSV output
5. **Legacy Components** - Backward compatibility with v1.0

---

## 🔬 How It Works

### Statistical Methods Explained

#### Z-Score Detection
1. Calculate mean (μ) and standard deviation (σ)
2. For each value x: `z = |x - μ| / σ`
3. Flag as anomaly if `z > threshold`

#### IQR Detection
1. Calculate Q1 (25th percentile) and Q3 (75th percentile)
2. Calculate IQR = Q3 - Q1
3. Define bounds: `[Q1 - k×IQR, Q3 + k×IQR]`
4. Flag values outside bounds

#### MAD Detection
1. Calculate median (M)
2. Calculate MAD = median(|x - M|)
3. Modified Z-score: `Zi = 0.6745 × |xi - M| / MAD`
4. Flag if modified Z-score > threshold

---

## 🛠️ Development

### Build System

```bash
# Clean build
make clean

# Build with all warnings
make

# Run with sample data
make run

# Run test suite
make test

# Show help
make help
```

### Compiler Requirements

- **C Compiler**: clang or gcc with C11 support
- **C++ Compiler**: clang++ or g++ with C++17 support
- **Make**: GNU Make or compatible

### Adding New Detection Methods

1. Add method to `DetectionMethod` enum in `cli_parser.h`
2. Implement algorithm in `statistics.cpp`
3. Add case in `main.cpp` switch statement
4. Update help text in `cli_parser.cpp`

---

## 📚 Use Cases

### 1. **Sensor Data Monitoring**
Detect faulty sensor readings in IoT devices
```bash
./bin/anomaly_detection -i sensor_logs.csv -c 2 --header -m mad
```

### 2. **Network Traffic Analysis**
Identify unusual network patterns
```bash
./bin/anomaly_detection -i network_traffic.csv -m iqr -v
```

### 3. **Financial Data**
Detect unusual transactions or market movements
```bash
./bin/anomaly_detection -i stock_prices.csv -m zscore -t 3.0
```

### 4. **Quality Control**
Monitor manufacturing processes for defects
```bash
./bin/anomaly_detection -i measurements.csv -m mad --header
```

---

## 🎯 Performance

- **Time Complexity**: O(n log n) for sorting-based methods (IQR, MAD)
- **Space Complexity**: O(n) for data storage
- **Memory Efficient**: Processes data in single pass where possible
- **Fast**: Optimized C/C++ implementation with -O2 optimization

---

## 🤝 Contributing

Contributions are welcome! Areas for improvement:

- [ ] Additional detection algorithms (Isolation Forest, LOF, etc.)
- [ ] Multi-threaded processing for large datasets
- [ ] Real-time streaming data support
- [ ] Machine learning-based methods
- [ ] Visualization output (plots, charts)
- [ ] Configuration file support
- [ ] Unit tests and benchmarks

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- Statistical methods based on established research in outlier detection
- Inspired by modern data science tools and practices
- Built with performance and usability in mind

---

## 📞 Support

For issues, questions, or suggestions:
- Open an issue on the repository
- Check the `--help` command for usage information
- Review the examples in the `examples/` directory

---

<div align="center">

**Made with ❤️ for data scientists, engineers, and analysts**

*Detect anomalies. Gain insights. Make better decisions.*

</div>
