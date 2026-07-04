#pragma once

// Pin assignment - single source of truth, keep in sync with
// hardware/schematics/wiring.md when the dev board variant changes.

// CC1101 (sub-GHz) - SPI
#define PIN_CC1101_CS    10
#define PIN_CC1101_GDO0  4
#define PIN_CC1101_GDO2  5

// PN532 (NFC/RFID) - I2C
#define PIN_I2C_SDA      8
#define PIN_I2C_SCL      9

// IR
#define PIN_IR_TX        17
#define PIN_IR_RX        18

// Module UI (OLED)
#define OLED_ADDR        0x3C
#define OLED_WIDTH       128
#define OLED_HEIGHT      64

// Serial link to NUC (native USB CDC, no extra pins required)
#define HOST_BAUD        115200
