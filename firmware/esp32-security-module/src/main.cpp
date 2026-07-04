// Cyberdeck Fieldkit - embedded security module
// CC BY-NC-SA 4.0 - Neil Manfred
//
// Skeleton firmware: brings up each peripheral, self-tests it, and
// exposes a serial menu for standalone (undocked) or host-connected use.
// Capture/replay/attack logic is deliberately left as TODOs pointing at
// the relevant library docs - fill in per engagement scope and only
// against systems you're authorised to test.

#include <Arduino.h>
#include <Wire.h>
#include <RadioLib.h>
#include <Adafruit_PN532.h>
#include <Adafruit_SSD1306.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include "config.h"

Module radioModule(PIN_CC1101_CS, PIN_CC1101_GDO0, RADIOLIB_NC, PIN_CC1101_GDO2);
CC1101 radio(&radioModule);

Adafruit_PN532 nfc(PIN_I2C_SDA, PIN_I2C_SCL);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
IRsend irsend(PIN_IR_TX);
IRrecv irrecv(PIN_IR_RX);

bool subghz_ok = false;
bool nfc_ok    = false;
bool oled_ok   = false;

void initSubGhz() {
    int state = radio.begin(433.92);
    subghz_ok = (state == RADIOLIB_ERR_NONE);
    Serial.printf("[CC1101] init %s\n", subghz_ok ? "OK" : "FAIL");
}

void initNfc() {
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    nfc_ok = (versiondata != 0);
    Serial.printf("[PN532] init %s\n", nfc_ok ? "OK" : "FAIL");
}

void initOled() {
    oled_ok = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    if (oled_ok) {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Fieldkit module");
        display.println("ready");
        display.display();
    }
    Serial.printf("[OLED] init %s\n", oled_ok ? "OK" : "FAIL");
}

void initIr() {
    irsend.begin();
    irrecv.enableIRIn();
    Serial.println("[IR] init OK");
}

void printMenu() {
    Serial.println();
    Serial.println("== Fieldkit module ==");
    Serial.println("1) Sub-GHz status");
    Serial.println("2) NFC/RFID scan  (TODO: implement read routine, see Adafruit_PN532 examples)");
    Serial.println("3) IR receive     (TODO: implement capture/decode, see IRremoteESP8266 examples)");
    Serial.println("4) IR transmit    (TODO: implement send-from-capture)");
    Serial.println("5) BadUSB payload (TODO: implement USB HID payload, see USBHIDKeyboard examples)");
    Serial.println("6) Self-test all peripherals");
    Serial.print("> ");
}

void selfTest() {
    Serial.println("--- self test ---");
    Serial.printf("Sub-GHz: %s\n", subghz_ok ? "OK" : "FAIL");
    Serial.printf("NFC/RFID: %s\n", nfc_ok ? "OK" : "FAIL");
    Serial.printf("OLED: %s\n", oled_ok ? "OK" : "FAIL");
}

void setup() {
    Serial.begin(HOST_BAUD);
    delay(1000);
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

    Serial.println("Cyberdeck Fieldkit module booting...");
    initSubGhz();
    initNfc();
    initOled();
    initIr();

    printMenu();
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case '1':
                Serial.printf("Sub-GHz: %s\n", subghz_ok ? "ready" : "not detected");
                break;
            case '2':
                Serial.println("NFC scan not yet implemented - see TODO in this file");
                break;
            case '3':
                Serial.println("IR receive not yet implemented - see TODO in this file");
                break;
            case '4':
                Serial.println("IR transmit not yet implemented - see TODO in this file");
                break;
            case '5':
                Serial.println("BadUSB payload not yet implemented - see TODO in this file");
                break;
            case '6':
                selfTest();
                break;
            default:
                break;
        }
        printMenu();
    }
}
