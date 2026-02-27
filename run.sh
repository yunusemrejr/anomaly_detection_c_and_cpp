#!/bin/bash

# Enhanced run script for Anomaly Detection Software v2.0

echo "╔═══════════════════════════════════════════════════════════════════════════╗"
echo "║              Anomaly Detection Software - Demo Script                    ║"
echo "╚═══════════════════════════════════════════════════════════════════════════╝"
echo ""

# Check if binary exists
if [ ! -f "./bin/anomaly_detection" ]; then
    echo "Binary not found. Building the application..."
    echo ""
    
    # Try to build
    if command -v make &> /dev/null; then
        make clean
        make
    else
        ./build.sh
    fi
    
    if [ $? -ne 0 ]; then
        echo "Build failed. Please check BUILD_INSTRUCTIONS.md"
        exit 1
    fi
    echo ""
fi

# Demo 1: Help
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 1: Display Help"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection --help
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 2: Basic file analysis
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 2: Analyze Sample Data (Z-Score Method)"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/sample_data.csv -v
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 3: IQR method
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 3: IQR Method on Network Traffic Data"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/network_traffic.csv -m iqr -v
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 4: MAD method
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 4: MAD Method (Robust Detection)"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/simple_data.csv -m mad -v
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 5: JSON output
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 5: JSON Output Format"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/simple_data.csv -f json
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 6: CSV output
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 6: CSV Output Format"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/simple_data.csv -f csv
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 7: Column selection
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 7: Analyze Specific Column (Temperature only)"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/sample_data.csv -c 0 --header -v
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 8: Stdin input (backward compatibility)
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 8: Stdin Input (Backward Compatibility)"
echo "═══════════════════════════════════════════════════════════════════════════"
echo "1,2,3,4,5,100,7,8,9,10" | ./bin/anomaly_detection
echo ""
read -p "Press Enter to continue..."
echo ""

# Demo 9: Save to file
echo "═══════════════════════════════════════════════════════════════════════════"
echo "Demo 9: Save Results to JSON File"
echo "═══════════════════════════════════════════════════════════════════════════"
./bin/anomaly_detection -i examples/sample_data.csv -f json -o demo_results.json -v
echo ""
if [ -f "demo_results.json" ]; then
    echo "File contents (first 20 lines):"
    head -20 demo_results.json
    echo "..."
fi
echo ""

echo "╔═══════════════════════════════════════════════════════════════════════════╗"
echo "║                          Demo Complete!                                   ║"
echo "╚═══════════════════════════════════════════════════════════════════════════╝"
echo ""
echo "Try your own commands:"
echo "  ./bin/anomaly_detection -i your_data.csv -m iqr -v"
echo "  ./bin/anomaly_detection --help"
echo ""
