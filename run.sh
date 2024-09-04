#!/bin/bash

# Compile the application
echo "Compiling the application..."
make clean
make

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Example data
example_data="1.0,2.0,3.0
4.0,5.0,6.0
7.0,8.0,9.0
10.0,11.0,12.0
-5.0,15.0,20.0"

# Run the application and feed it the example data
echo "Running the application with example data..."
echo "$example_data" | ./bin/anomaly_detection

# Check if the application ran successfully
if [ $? -ne 0 ]; then
    echo "Application execution failed."
    exit 1
fi

echo "Script completed successfully."


