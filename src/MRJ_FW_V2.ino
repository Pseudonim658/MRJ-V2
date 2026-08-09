#include "config.h"
#include "hardware_pinout.h"
#include "display.h"
#include "buzzer.h"
#include "sd_card.h"
#include "logger.h"
#include "web_server.h"
#include "wifi_deauth.h"
#include "nethercap_core.h"
#include "ble_module.h"
#include "subghz.h"
#include "nfc_module.h"
#include "rfid_module.h"
#include "rfid_125khz.h"
#include "ibutton.h"
#include "ir_remote.h"
#include "ir_decoder.h"
#include "badusb.h"
#include "gpio_control.h"
#include "touch_driver.h"
#include "ota_update.h"
#include "eeprom_manager.h"
#include "reserved_pins.h"
#include "menu.h"

void setup() {
    Serial.begin(115200);
    Serial.println("\n=== MRJ V2 - ST7735 TFT ===");

    if (!validateHardwarePinout()) {
        Serial.println("[ERROR] Hardware pinout conflict!");
        while (1) delay(100);
    }

    eeprom.init();
    logger.init();
    display.begin();
    display.showSplash();

    buzzer.init();
    buzzer.beep(1000, 100);

    sdCard.init();

    // ========== CORE MODULES (always active) ==========
    wifiDeauth.init();
    nethercap.init();
    bleModule.init();
    gpioControl.init();
    ota.init();
    menu.init();

    // ========== DEFAULT ACTIVE: IR Receiver only ==========
    irRemote.init();  // IR Receiver always ON by default

    // ========== OPTIONAL MODULES (EEPROM controlled) ==========
    if (eeprom.isModuleEnabled(EE_MODULE_IR_SEND)) {
        irRemote.enableTx();
    }
    if (eeprom.isModuleEnabled(EE_MODULE_NFC)) {
        nfcModule.init();      // Team B
    }
    if (eeprom.isModuleEnabled(EE_MODULE_IBUTTON)) {
        ibutton.init();
    }
    if (eeprom.isModuleEnabled(EE_MODULE_CC1101)) {
        subGHz.init();         // Team A
    }
    if (eeprom.isModuleEnabled(EE_MODULE_RFID)) {
        rfidModule.init();     // Team B
        rfid125.init();        // Team B (125kHz)
    }
    if (eeprom.isModuleEnabled(EE_MODULE_BADUSB)) {
        badUSB.init();         // Team A
    }
    if (eeprom.isModuleEnabled(EE_MODULE_TOUCH)) {
        touch.init();
    }

    webServer.init();
    webServer.startAP();
    webServer.startServer();

    display.showIP(webServer.getIP().c_str());

    logger.log(LOG_INFO, "SYS", "Boot complete");
    buzzer.success();
}

void loop() {
    buzzer.update();
    wifiDeauth.update();
    nethercap.update();
    subGHz.update();
    irRemote.update();
    bleModule.update();
    ibutton.update();
    ota.update();
    menu.update();

    delay(10);
}
