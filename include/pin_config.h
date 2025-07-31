#pragma once // Prevents the file from being included multiple times

// --- DISPLAY ---
// Screen Resolution (matches platformio.ini build flags)
#ifndef LCD_WIDTH
#define LCD_WIDTH 368  // The width of your SH8601 display (from build flags)
#endif
#ifndef LCD_HEIGHT
#define LCD_HEIGHT 448 // The height of your SH8601 display (from build flags)
#endif

// QSPI Bus Pins for the Display
#define LCD_SCLK 40    // [cite: 5]
#define LCD_SDIO0 41   // [cite: 5]
#define LCD_SDIO1 42   // [cite: 5]
#define LCD_SDIO2 39   // [cite: 5]
#define LCD_SDIO3 38   // [cite: 5]
#define LCD_CS 8       // [cite: 5]

// --- I2C BUS ---
// Pins for PMU and Touch Controller
#define IIC_SDA 18     // [cite: 17, 18]
#define IIC_SCL 17     // [cite: 17, 18]

// --- PERIPHERALS ---
// Power Amplifier Pin
#define PA 46          // [cite: 16]

// Touchscreen Interrupt Pin
#define TP_INT 7       // [cite: 7]

// I2C Device Addresses
#ifndef AXP2101_SLAVE_ADDRESS
#define AXP2101_SLAVE_ADDRESS 0x34    // PMU address
#endif
#define FT3168_DEVICE_ADDRESS 0x38    // Touch controller address