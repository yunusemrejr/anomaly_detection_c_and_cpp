# Feature Overview - Anomaly Detection Software v2.0

## 🎯 Core Features

### 1. Multiple Detection Algorithms

#### Z-Score Method (Statistical)
- **Use Case**: Normally distributed data
- **Strength**: Fast, well-understood, widely used
- **Formula**: Flags values where `|x - μ| > threshold × σ`
- **Best For**: General-purpose anomaly detection
- **Example**: Detecting unusual sensor readings

```bash
./bin/anomaly_detection -i data.csv -m zscore -t 2.0
```

#### IQR Method (Quartile-Based)
- **Use Case**: Non-normal distributions, skewed data
- **Strength**: Robust to outliers, doesn't assume normality
- **Formula**: Flags values outside `[Q1 - k×IQR, Q3 + k×IQR]`
- **Best For**: Financial data, real-world datasets
- **Example**: Detecting unusual transaction amounts

```bash
./bin/anomaly_detection -i data.csv -m iqr -t 1.5
```

#### MAD Method (Median-Based)
- **Use Case**: Data with extreme outliers
- **Strength**: Highly robust, resistant to outliers
- **Formula**: Uses median absolute deviation instead of standard deviation
- **Best For**: Contaminated data, robust detection
- **Example**: Network traffic analysis with noise

```bash
./bin/anomaly_detection -i data.csv -m mad -t 3.5
```

#### Modified Z-Score Method
- **Use Case**: Similar to MAD, enhanced robustness
- **Strength**: Combines benefits of Z-score and MAD
- **Formula**: Modified Z-score using MAD
- **Best For**: Scientific data, quality control
- **Example**: Manufacturing defect detection

```bash
./bin/anomaly_detection -i data.csv -m modified-zscore
```

---

### 2. Flexible Input/Output

#### Input Options
- **File Input**: Read from CSV files
- **Stdin Input**: Pipe data from other commands
- **Column Selection**: Analyze specific columns
- **Header Support**: Skip header rows automatically

```bash
# File input
./bin/anomaly_detection -i sensor_data.csv

# Stdin input
cat data.csv | ./bin/anomaly_detection

# Specific columns
./bin/anomaly_detection -i data.csv -c 0,2,5 --header

# Pipeline
generate_data.sh | ./bin/anomaly_detection -m iqr
```

#### Output Options
- **Terminal**: Beautiful, colorized output
- **JSON**: Machine-readable format
- **CSV**: Spreadsheet-compatible format
- **File Output**: Save results to disk

```bash
# Terminal output (default)
./bin/anomaly_detection -i data.csv

# JSON output
./bin/anomaly_detection -i data.csv -f json

# Save to file
./bin/anomaly_detection -i data.csv -f json -o results.json

# CSV export
./bin/anomaly_detection -i data.csv -f csv -o results.csv
```

---

### 3. Comprehensive Statistics

Every analysis includes:

- **Central Tendency**: Mean, Median
- **Dispersion**: Standard Deviation, IQR, MAD
- **Range**: Min, Max
- **Quartiles**: Q1 (25%), Q3 (75%)
- **Anomaly Metrics**: Count, Rate, Scores
- **Detailed Reasoning**: Why each point is flagged

```bash
# Verbose output with all statistics
./bin/anomaly_detection -i data.csv -v
```

**Example Output:**
```
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
```

---

### 4. Professional CLI Interface

#### Help System
```bash
./bin/anomaly_detection --help
```

Displays:
- Usage syntax
- All available options
- Detection method descriptions
- Output format options
- Examples
- Author information

#### Version Information
```bash
./bin/anomaly_detection --version
```

#### Verbose Mode
```bash
./bin/anomaly_detection -i data.csv -v
```

Shows:
- Detailed statistics
- All anomalies (not just first 10)
- Processing information
- Reasoning for each detection

---

### 5. Advanced Data Handling

#### Multi-Column Support
Analyze datasets with multiple features:

```csv
timestamp,temperature,humidity,pressure
1,22.5,45.2,1013.2
2,23.1,46.8,1012.8
3,95.5,46.2,1013.0  # Anomaly in temperature
```

```bash
# Analyze all columns
./bin/anomaly_detection -i data.csv --header

# Analyze only temperature (column 1)
./bin/anomaly_detection -i data.csv -c 1 --header

# Analyze temperature and pressure (columns 1 and 3)
./bin/anomaly_detection -i data.csv -c 1,3 --header
```

#### Robust CSV Parsing
- Handles quoted fields: `"value with, comma"`
- Trims whitespace automatically
- Skips invalid values gracefully
- Supports various CSV formats

---

### 6. Configurable Sensitivity

Adjust detection sensitivity with custom thresholds:

```bash
# More sensitive (lower threshold)
./bin/anomaly_detection -i data.csv -t 1.5

# Less sensitive (higher threshold)
./bin/anomaly_detection -i data.csv -t 3.0

# Method-specific defaults
./bin/anomaly_detection -i data.csv -m zscore    # default: 2.0
./bin/anomaly_detection -i data.csv -m iqr       # default: 1.5
./bin/anomaly_detection -i data.csv -m mad       # default: 3.5
```

---

### 7. Beautiful Terminal Output

#### Color-Coded Results
- 🟢 **Green**: Normal data, success messages
- 🔴 **Red**: Anomalies, errors
- 🟡 **Yellow**: Warnings, indices
- 🔵 **Blue**: Headers, information
- 🟣 **Magenta**: Highlights

#### Unicode Box Drawing
```
╔═══════════════════════════════════════════════════════════════════════════╗
║                      ANOMALY DETECTION RESULTS                            ║
╚═══════════════════════════════════════════════════════════════════════════╝
```

#### Emoji Indicators
- 📊 Summary section
- 📈 Statistics section
- 🚨 Anomalies section
- ✓ Success indicators

---

### 8. Export & Integration

#### JSON Export
Perfect for:
- Further processing with Python/R
- Integration with web applications
- Storage in databases
- API responses

```json
{
  "summary": {
    "total_points": 60,
    "anomaly_count": 2,
    "anomaly_rate": 3.33
  },
  "statistics": { ... },
  "anomalies": [ ... ],
  "data": [ ... ]
}
```

#### CSV Export
Perfect for:
- Excel/Google Sheets import
- Database import
- Further analysis
- Reporting

```csv
index,value,is_anomaly,score,reason
0,22.5,0,0.123,"Normal"
15,95.5,1,4.659,"Z-score exceeds threshold"
```

---

### 9. Sample Datasets

Three ready-to-use datasets included:

#### 1. Sensor Data (`sample_data.csv`)
- Temperature, humidity, pressure readings
- Contains temperature anomalies
- Demonstrates multi-column analysis

#### 2. Simple Data (`simple_data.csv`)
- Basic numerical data
- Clear anomalies for testing
- Good for learning

#### 3. Network Traffic (`network_traffic.csv`)
- Bytes sent/received, latency
- Network spike anomalies
- Real-world use case

---

### 10. Backward Compatibility

All original functionality preserved:

```bash
# Original stdin method still works
echo "1,2,3,4,5,100" | ./bin/anomaly_detection

# Legacy output format available
./bin/anomaly_detection -i data.csv  # (without -v)
```

---

## 🎓 Usage Patterns

### Pattern 1: Quick Analysis
```bash
./bin/anomaly_detection -i data.csv
```

### Pattern 2: Detailed Investigation
```bash
./bin/anomaly_detection -i data.csv -v
```

### Pattern 3: Method Comparison
```bash
./bin/anomaly_detection -i data.csv -m zscore > zscore.txt
./bin/anomaly_detection -i data.csv -m iqr > iqr.txt
./bin/anomaly_detection -i data.csv -m mad > mad.txt
diff zscore.txt iqr.txt
```

### Pattern 4: Automated Processing
```bash
for file in data/*.csv; do
    ./bin/anomaly_detection -i "$file" -f json -o "results/$(basename $file .csv).json"
done
```

### Pattern 5: Pipeline Integration
```bash
curl https://api.example.com/data | \
    jq -r '.values[]' | \
    ./bin/anomaly_detection -m mad | \
    grep "Anomaly"
```

---

## 🔧 Technical Specifications

- **Language**: C11 + C++17
- **Compilers**: GCC, Clang
- **Build System**: Make / Shell script
- **Dependencies**: Standard library only (no external deps)
- **Performance**: O(n log n) time, O(n) space
- **Platforms**: Linux, macOS, Unix-like systems
- **License**: MIT

---

## 📊 Performance Characteristics

| Dataset Size | Processing Time | Memory Usage |
|--------------|-----------------|--------------|
| 100 points   | < 1ms          | < 1MB        |
| 1,000 points | < 10ms         | < 2MB        |
| 10,000 points| < 100ms        | < 10MB       |
| 100,000 points| < 1s          | < 50MB       |

*Benchmarks on typical modern hardware*

---

## 🎯 Real-World Applications

1. **IoT Sensor Monitoring**: Detect faulty sensors
2. **Network Security**: Identify unusual traffic patterns
3. **Financial Analysis**: Flag suspicious transactions
4. **Quality Control**: Detect manufacturing defects
5. **System Monitoring**: Identify performance issues
6. **Scientific Research**: Clean experimental data
7. **Business Intelligence**: Spot unusual trends
8. **Healthcare**: Monitor patient vitals

---

## 🚀 Getting Started

1. **Build**: `make` or `./build.sh`
2. **Test**: `./bin/anomaly_detection -i examples/sample_data.csv -v`
3. **Learn**: `./bin/anomaly_detection --help`
4. **Explore**: Try different methods and options
5. **Integrate**: Use in your workflows

---

*For complete documentation, see README.md*
