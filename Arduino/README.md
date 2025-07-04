# Arduino Uno - Compile and Upload via Terminal

## What You Need
- Arduino CLI tool (you already have it!)
- USB cable to connect Arduino Uno to your computer
- Your .ino files in VSCode

## Setup Arduino CLI (You Already Have It!)

You already have arduino-cli.exe in your project folder. You can use it directly:

```powershell
# Test if it works
.\arduino-cli-extracted\arduino-cli.exe version
```

## Setup Arduino CLI (First Time Only)

```powershell
# Update the core index
.\arduino-cli-extracted\arduino-cli.exe core update-index

# Install Arduino AVR core (for Uno)
.\arduino-cli-extracted\arduino-cli.exe core install arduino:avr

# List available boards (optional)
.\arduino-cli-extracted\arduino-cli.exe board list
```

## Find Your Arduino Port

```powershell
# List connected devices
.\arduino-cli-extracted\arduino-cli.exe board list
```
Look for your Arduino Uno - note the port (like COM3 on Windows)

## Compile and Upload Your Code

### Basic Commands

```powershell
# Navigate to your Arduino project folder
cd Arduino/04_Interrups

# Compile your sketch
..\..\arduino-cli-extracted\arduino-cli.exe compile --fqbn arduino:avr:uno 04_Interrups.ino

# Upload to Arduino (replace COM3 with your port)
..\..\arduino-cli-extracted\arduino-cli.exe upload -p COM3 --fqbn arduino:avr:uno 04_Interrups.ino

# Compile and upload in one command
..\..\arduino-cli-extracted\arduino-cli.exe compile --upload -p COM3 --fqbn arduino:avr:uno 04_Interrups.ino
```

### What Each Part Means
- `--fqbn arduino:avr:uno` = Board type (Arduino Uno)
- `-p COM3` = Port where Arduino is connected
- `04_Interrups.ino` = Your sketch file name

## Quick Reference

```powershell
# Check if Arduino CLI is working
.\arduino-cli\arduino-cli.exe version

# Find your Arduino
.\arduino-cli\arduino-cli.exe board list

# Compile only
.\arduino-cli\arduino-cli.exe compile --fqbn arduino:avr:uno your_sketch.ino

# Upload only (after compiling)
.\arduino-cli\arduino-cli.exe upload -p YOUR_PORT --fqbn arduino:avr:uno your_sketch.ino

# Compile and upload together
.\arduino-cli\arduino-cli.exe compile --upload -p YOUR_PORT --fqbn arduino:avr:uno your_sketch.ino
```

## Common Issues

**"Port not found"**: Check USB connection and try different ports
**"Permission denied"**: On Linux, add yourself to dialout group: `sudo usermod -a -G dialout $USER`
**"Board not found"**: Make sure you installed the AVR core: `arduino-cli core install arduino:avr`

## Example Workflow

1. Write your code in VSCode (.ino file)
2. Open terminal in your project folder
3. Run: `arduino-cli compile --upload -p COM3 --fqbn arduino:avr:uno your_sketch.ino`
4. Watch your Arduino run the code!