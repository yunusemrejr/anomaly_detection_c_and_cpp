#!/bin/bash

# Build script for Anomaly Detection Software
# This script provides an alternative to make for systems where make is not available

set -e  # Exit on error

echo "╔═══════════════════════════════════════════════════════════════════════════╗"
echo "║              Anomaly Detection Software - Build Script                   ║"
echo "╚═══════════════════════════════════════════════════════════════════════════╝"
echo ""

# Check for compilers
if ! command -v gcc &> /dev/null && ! command -v clang &> /dev/null; then
    echo "Error: No C compiler found. Please install gcc or clang."
    exit 1
fi

if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "Error: No C++ compiler found. Please install g++ or clang++."
    exit 1
fi

# Determine which compiler to use
if command -v clang &> /dev/null; then
    CC=clang
    CXX=clang++
else
    CC=gcc
    CXX=g++
fi

echo "Using compilers: $CC and $CXX"
echo ""

# Create directories
echo "Creating build directories..."
mkdir -p obj bin

# Compile C files
echo "Compiling C source files..."
$CC -Wall -Wextra -std=c11 -O2 -Iinclude -c src/detect_anomalies.c -o obj/detect_anomalies.o
echo "  ✓ detect_anomalies.c"

$CC -Wall -Wextra -std=c11 -O2 -Iinclude -c src/extract_features.c -o obj/extract_features.o
echo "  ✓ extract_features.c"

# Compile C++ files
echo ""
echo "Compiling C++ source files..."
$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/main.cpp -o obj/main.o
echo "  ✓ main.cpp"

$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/preprocess_data.cpp -o obj/preprocess_data.o
echo "  ✓ preprocess_data.cpp"

$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/print_anomalies.cpp -o obj/print_anomalies.o
echo "  ✓ print_anomalies.cpp"

$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/cli_parser.cpp -o obj/cli_parser.o
echo "  ✓ cli_parser.cpp"

$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/csv_parser.cpp -o obj/csv_parser.o
echo "  ✓ csv_parser.cpp"

$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/statistics.cpp -o obj/statistics.o
echo "  ✓ statistics.cpp"

$CXX -Wall -Wextra -std=c++17 -O2 -Iinclude -c src/output_formatter.cpp -o obj/output_formatter.o
echo "  ✓ output_formatter.cpp"

# Link
echo ""
echo "Linking executable..."
$CXX -Wall -Wextra -std=c++17 -O2 obj/*.o -o bin/anomaly_detection -lm
echo "  ✓ bin/anomaly_detection"

echo ""
echo "╔═══════════════════════════════════════════════════════════════════════════╗"
echo "║                        Build Successful!                                  ║"
echo "╚═══════════════════════════════════════════════════════════════════════════╝"
echo ""
echo "Run the application:"
echo "  ./bin/anomaly_detection --help"
echo "  ./bin/anomaly_detection -i examples/sample_data.csv -v"
echo ""
