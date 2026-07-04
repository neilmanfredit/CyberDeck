# Architecture

## Case

Clamshell, single hinge (piano-style, printed or salvaged laptop hinge bar).

- **Lower half:** NUC bay, keyboard bay (60–65% compact board), embedded security module bay with front-facing sensor cutouts, USB-C PD input, port breakout (USB-A x2, USB-C x1, HDMI/DP passthrough)
- **Upper half:** two small display panels side by side, bezel routed for USB-C video/power ribbon back to the hinge
- **Hinge:** carries video (2x USB-C or 1x USB-C DP-alt + 1x HDMI mini) and power from lower to upper half
- Spare internal depth in the keyboard bay for a stowed portable mouse when travelling; keyboard is removable to fit a full-size external board when docked

## Compute

GMKtec NucBox G3 (Intel N100), barebone, own RAM/NVMe fitted, Kali installed. Board is 115x108x44mm - fits the case NUC bay as specced. Takes 12V/3A DC, not native USB-C PD, so it sits behind a PD trigger board in the power tree (see below). External RF adapters (Wi-Fi/Bluetooth) connect via a short internal USB-C hub rather than the NUC's onboard chipset — onboard Wi-Fi/BT rarely support monitor mode/injection.

## Embedded security module

LilyGO T-Embed CC1101 — prebuilt ESP32-S3 board with CC1101 (sub-GHz), PN532 (NFC/RFID), 1.9" IPS TFT (320x170), IR TX/RX, rotary encoder and its own battery, mounted as a self-contained carrier in the module bay rather than wired from discrete chips. Runs CapibaraZero (open-source, Flipper-alternative firmware covering WiFi, BLE, BadUSB, NFC, sub-GHz, IR). Connects to the NUC over USB serial (native USB, appears as `/dev/ttyACM0`) when docked; works standalone off its own battery when pulled from the bay.

Module bay cutout needs to match the T-Embed's screen/button footprint rather than the generic dimensions in the current `case.scad` skeleton — update once the board's in hand.

## Power

Single USB-C PD input feeds a PD trigger/splitter board inside the lower case: one leg to a 12V trigger board matched to the NUC's DC input rating, one leg to the hinge feed for both screens, one leg to a 5V buck for spare peripherals (T-Embed charges over its own USB-C when docked, so no extra buck needed for it). An internal battery (slim 2S 18650/21700 USB-C PD board kit, ~10,000mAh) sits inline on the PD input so the deck runs untethered; external 100W PD bank tops it up.

## Docs to add as the build progresses

- `docs/BOM.md` — full parts list with UK suppliers
- `hardware/schematics/` — wiring diagrams (module + power tree)
