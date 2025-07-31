# ESP32-S3-Touch-AMOLED-1.8 Compatibility & Configuration Memory

## Hardware Specifications

### ESP32-S3-DevKitM-1 Board
- **Microcontroller**: ESP32S3 
- **Frequency**: 240MHz
- **Flash**: 8MB
- **RAM**: 320KB 
- **PSRAM**: Available (must be properly configured)
- **Vendor**: Espressif

### Waveshare ESP32-S3-Touch-AMOLED-1.8 Specific Hardware
- **Display**: SH8601 AMOLED, 368×448 resolution
- **Touch Controller**: FT3168 capacitive touch
- **Power Management**: AXP2101 PMU
- **Audio Codec**: ES8311 with speaker and microphone
- **Sensors**: QMI8658 IMU, PCF85063 RTC
- **I/O Expander**: TCA9554
- **Interface**: QSPI for display, I2C for peripherals
- **Battery**: 350mAh (recommended 3.85*24*28 400mAh)
- **Maximum Brightness**: 350nit

## PlatformIO Configuration Requirements

### Essential Board Configuration
```ini
[env:esp32-s3-devkitm-1]
platform = espressif32
board = esp32-s3-devkitm-1
framework = arduino
```

### CRITICAL Build Flags (MUST INCLUDE ALL)
```ini
build_flags = 
    -D LV_LVGL_H_INCLUDE_SIMPLE
    -D LV_CONF_INCLUDE_SIMPLE
    -D BOARD_HAS_PSRAM
    -D LCD_WIDTH=368 
    -D LCD_HEIGHT=448
```

### PSRAM Configuration
- **IMPORTANT**: The board HAS PSRAM but requires explicit enabling
- **DO NOT** use `-D BOARD_HAS_PSRAM = true` (WRONG SYNTAX)
- **CORRECT**: Use `-D BOARD_HAS_PSRAM` (without value)
- PSRAM enables allocation of large buffers using `ps_malloc()`

### Library Dependencies (Exact Versions)
```ini
lib_deps = 
    lvgl/lvgl@^8.3.11          ; Core LVGL graphics library
    lewisxhe/XPowersLib@^0.2.1 ; AXP2101 Power Management
```

## LVGL Configuration Critical Points

### lv_conf.h Requirements
1. **MUST** change `#if 0` to `#if 1` at top of file to enable configuration
2. **Color Settings**: 
   - `LV_COLOR_DEPTH 16` (RGB565)
   - `LV_COLOR_16_SWAP 0` for Arduino_GFX, `1` for ESP-IDF

### Build Flag Explanation
- `-D LV_LVGL_H_INCLUDE_SIMPLE`: Allows direct `#include <lvgl.h>`
- `-D LV_CONF_INCLUDE_SIMPLE`: Allows simple `#include "lv_conf.h"` instead of relative paths
- Without these flags, LVGL looks for config files in wrong directory structure

## Hardware Communication Protocols

### Display (SH8601)
- **Interface**: QSPI (Quad SPI)
- **Pins**: LCD_CS, LCD_SCLK, LCD_SDIO0-3
- **Driver**: Arduino_SH8601 class
- **Brightness Control**: Write 0x00-0xFF to register 0x51 via QSPI

### Touch Controller (FT3168)
- **Interface**: I2C
- **Pins**: IIC_SDA, IIC_SCL
- **Interrupt**: GPIO pin for touch detection
- **Power Mode**: Must set to TOUCH_POWER_MONITOR for low power

### Power Management (AXP2101)
- **Interface**: I2C
- **Slave Address**: AXP2101_SLAVE_ADDRESS
- **Features**: Battery monitoring, voltage measurement, charging control
- **Critical**: PMU failure halts system - check initialization

## Development Environment Compatibility

### Arduino IDE Requirements
- **ESP32 Board Package**: ≥3.0.6 by Espressif Systems
- **Partition Scheme**: 16M Flash (3MB APP/9.9MB FATFS) for image-heavy projects
- **USB CDC**: Enable "USB CDC On Boot" for Serial output

### PlatformIO Configuration
- **Platform**: espressif32
- **Framework**: arduino
- **lib_ldf_mode**: deep+ (recommended for dependency resolution)
- **monitor_speed**: 115200 (must match Serial.begin() in code)

## Memory and Performance Optimizations

### PSRAM Usage
- Enable with `-D BOARD_HAS_PSRAM` build flag
- Use `ps_malloc()` for large allocations (display buffers, images)
- Essential for LVGL applications with large UI assets

### Display Performance
- **Arduino GFX**: Basic performance, suitable for simple graphics
- **ESP-IDF with double buffering**: 200-300 FPS, optimal performance
- **LVGL Widgets**: 50-60 FPS achievable with optimization

## Power Management
- **Battery Life**: ~1 hour full brightness, 3-4 hours backlight off, 6 hours low-power mode
- **Power Control**: PWR button (6s hold to power off, click to power on)
- **Charging**: Via USB-C, managed by AXP2101

## Common Configuration Errors & Solutions

### LVGL Configuration Issues
- **Error**: `fatal error: ../../lv_conf.h: No such file or directory`
- **Solution**: Add `-D LV_CONF_INCLUDE_SIMPLE` to build_flags AND change `#if 0` to `#if 1` in lv_conf.h

### Class/Function Not Found Errors
- **XPowersPMU undefined**: Use `XPowersAXP2101` class name
- **setBrightness not found**: Use `Arduino_SH8601*` type, not `Arduino_GFX*`
- **ui_init undefined**: Wrap `#include "ui.h"` in `extern "C" { }` block

### PSRAM Configuration
- **Incorrect**: `-D BOARD_HAS_PSRAM = true`
- **Correct**: `-D BOARD_HAS_PSRAM`
- The flag is a preprocessor definition, not a key-value pair

## Library Installation Requirements

### Arduino IDE Libraries (Install Order)
1. Arduino_DriveBus (offline install)
2. GFX_Library_for_Arduino v1.4.9 (offline install)
3. ESP32_IO_Expander v0.0.3 (online/offline)
4. lvgl v8.4.0 (offline recommended)
5. SensorLib v0.2.1 (online/offline)
6. XPowersLib v0.2.6 (online/offline)

### Critical Files (Must Include)
- pin_config.h (hardware pin definitions)
- lv_conf.h (LVGL configuration)
- ui.h/ui.c (SquareLine Studio generated UI)

## Debugging and Upload Settings

### Upload Protocols Supported
- esptool (default)
- esp-builtin, esp-bridge, esp-prog
- JTAG options: jlink, cmsis-dap

### Serial Debug Configuration
- **Monitor Speed**: 115200 baud
- **USB CDC**: Must enable for Serial.print() output
- **Reset Method**: Hold BOOT + power on for download mode if needed

## Version Compatibility Matrix

| Component | Arduino IDE | ESP-IDF | PlatformIO |
|-----------|-------------|---------|------------|
| ESP32 Core | ≥3.0.6 | v5.1.4+ | Latest |
| LVGL | 8.3.11-8.4.0 | 8.3.11-8.4.0 | 8.3.11+ |
| Arduino_GFX | v1.4.9 | Custom | v1.4.9 |
| XPowersLib | v0.2.6 | Port required | v0.2.1+ |

## Performance Expectations

### Frame Rates by Configuration
- **Arduino GFX Basic**: 10-20 FPS
- **Arduino GFX Optimized**: 30-40 FPS  
- **ESP-IDF + Double Buffer**: 200-300 FPS
- **LVGL Widgets (Arduino)**: 50-60 FPS
- **LVGL Widgets (ESP-IDF)**: 200+ FPS

## Flash Partition Requirements

### Standard Projects
- Default partition scheme sufficient for basic applications
- Monitor code size vs. available flash

### Image-Heavy Projects
- **Required**: 16M Flash (3MB APP/9.9MB FATFS)
- **Location**: Tools → Partition Scheme in Arduino IDE
- **Reason**: Large image assets exceed default APP partition size

## Critical Success Factors

1. **PSRAM**: Must enable with correct build flag syntax
2. **LVGL Config**: Must activate lv_conf.h with `#if 1` AND include flags
3. **C/C++ Mixing**: Use `extern "C"` for C libraries in C++ projects
4. **Class Types**: Use derived classes (Arduino_SH8601) not base classes
5. **Power Management**: Always check PMU initialization before proceeding
6. **Partition Scheme**: Use large partition for projects with images/assets

This configuration has been validated against official documentation and working examples.
