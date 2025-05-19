#!/bin/bash

# Compile the timer program
echo "Compiling interruptTimer.c..."
gcc -o interruptTimer interruptTimer.c -Wall

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Running the program with current parameters:"
    echo "- Period between interrupts: ${DT_PERIOD_S}s ${DT_PERIOD_US}us (currently 0s 100000us = 100ms)"
    echo "- Wait until first interrupt: ${DT_WAIT_S}s ${DT_WAIT_US}us (currently 0s 500000us = 500ms)"
    echo "- Number of interrupts: ${NUM_SLICES} (currently 100)"
    echo "-------------------------------------------------"
    ./interruptTimer
else
    echo "Compilation failed."
fi