# Wiring Notes

## Embedded security module (ESP32-S3)

| Peripheral | Pin (ESP32-S3 side) | Notes |
|---|---|---|
| CC1101 (SPI) | SCK/MOSI/MISO/CS as per RadioLib pinout | confirm free GPIOs against dev board silkscreen |
| PN532 (I2C) | SDA/SCL | address 0x24 default |
| IR TX | GPIO -> IR LED via transistor driver | 38kHz carrier |
| IR RX | TSOP38238 -> GPIO | direct, no driver needed |
| OLED/TFT (module UI) | I2C or SPI, shared bus with PN532 if I2C | check address conflicts |
| USB | native USB (HID + serial) | serial to NUC, HID for BadUSB function |

Finalise exact GPIO assignment once the dev board variant is chosen (DevKitC-1 vs S3-Zero have different broken-out pins) - update `firmware/esp32-security-module/include/config.h` to match, single source of truth.

## Power tree

```
USB-C PD in (case edge)
  -> PD trigger board (negotiate NUC voltage)
       -> NUC DC input
  -> hinge feed (USB-C passthrough)
       -> Screen 1
       -> Screen 2
  -> 5V buck
       -> ESP32-S3 module (5V pin)
  -> internal battery (10,000mAh, USB-C PD passthrough, sits inline)
```

Internal battery sits inline on the PD input so the deck keeps running on battery when unplugged, and recharges when the external bank is connected. Confirm the PD trigger board's negotiated voltage matches the NUC board's DC input rating before wiring - check the sourced board's spec sheet.
