# Build Instructions

## Prerequisites

This project requires:
- C compiler (gcc or clang) with C11 support
- C++ compiler (g++ or clang++) with C++17 support
- GNU Make

## Installation on Different Systems

### Amazon Linux 2023 / RHEL / Fedora
```bash
sudo dnf install -y gcc gcc-c++ make
```

### Ubuntu / Debian
```bash
sudo apt-get update
sudo apt-get install -y build-essential
```

### macOS
```bash
# Install Xcode Command Line Tools
xcode-select --install
```

## Building the Project

### Quick Build
```bash
make clean
make
```

### Manual Build (if make is not available)
```bash
# Create directories
mkdir -p obj bin

# Compile C files
gcc -Wall -Wextra -std=c11 -O2 -Iinclude -c src/detect_anomalies.c -o obj/detect_anomalies.o
gcc -Wall -Wextra -std=c11 -O2 -Iinclude -c src/extract_features.c -o obj/extract_features.o

# Compile C++ files
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/main.cpp -o obj/main.o
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/preprocess_data.cpp -o obj/preprocess_data.o
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/print_anomalies.cpp -o obj/print_anomalies.o
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/cli_parser.cpp -o obj/cli_parser.o
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/csv_parser.cpp -o obj/csv_parser.o
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/statistics.cpp -o obj/statistics.o
g++ -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/output_formatter.cpp -o obj/output_formatter.o

# Link
g++ -Wall -Wextra -std=c++17 -O2 obj/*.o -o bin/anomaly_detection -lm
```

## Running the Application

### Basic Usage
```bash
./bin/anomaly_detection -i examples/sample_data.csv -v
```

### Help
```bash
./bin/anomaly_detection --help
```

## Testing

```bash
make test
```

Or manually:
```bash
# Test 1: stdin input
echo "1,2,3,4,5,100" | ./bin/anomaly_detection

# Test 2: file input
./bin/anomaly_detection -i examples/sample_data.csv -v

# Test 3: different methods
./bin/anomaly_detection -i examples/sample_data.csv -m iqr
./bin/anomaly_detection -i examples/sample_data.csv -m mad

# Test 4: JSON output
./bin/anomaly_detection -i examples/sample_data.csv -f json
```
