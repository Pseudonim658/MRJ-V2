#include "menu.h"
#include "nethercap_core.h"
#include "wifi_deauth.h"
#include "eeprom_manager.h"
#include "web_server.h"

MenuModule menu;

void actionNethercapMenu();
void actionDeauthMenu();
void actionNethercapStart();
void actionNethercapStop();
void actionDeauthStart();
void actionDeauthStop();
void actionBeaconSpamStart();
void actionBeaconSpamStop();
void actionConfigMenu();

MenuItem mainMenuItems[] = {
    {"Nethercap", actionNethercapMenu, MENU_NETHERCAP, true},
    {"WiFi Deauth", actionDeauthMenu, MENU_DEAUTH, true},
    {"BLE Tools", nullptr, MENU_BLE, true},
    {"Sub-GHz", nullptr, MENU_SUBGHZ, true},
    {"RFID", nullptr, MENU_RFID, true},
    {"NFC", nullptr, MENU_NFC, true},
    {"iButton", nullptr, MENU_IBUTTON, true},
    {"IR Remote", nullptr, MENU_IR, true},
    {"BadUSB", nullptr, MENU_BADUSB, true},
    {"GPIO Control", nullptr, MENU_GPIO, true},
    {"Web Server", nullptr, MENU_WEB, true},
    {"SD Card", nullptr, MENU_SDCARD, true},
    {"Settings", actionConfigMenu, MENU_CONFIG, true},
};

MenuItem nethercapMenuItems[] = {
    {"Start Portal", actionNethercapStart, MENU_NETHERCAP, false},
    {"Stop Portal", actionNethercapStop, MENU_NETHERCAP, false},
    {"Start Deauth", actionDeauthStart, MENU_NETHERCAP, false},
    {"Stop Deauth", actionDeauthStop, MENU_NETHERCAP, false},
    {"Beacon Spam On", actionBeaconSpamStart, MENU_NETHERCAP, false},
    {"Beacon Spam Off", actionBeaconSpamStop, MENU_NETHERCAP, false},
};

MenuItem deauthMenuItems[] = {
    {"Scan Networks", nullptr, MENU_DEAUTH, false},
    {"Start Deauth", actionDeauthStart, MENU_DEAUTH, false},
    {"Stop Deauth", actionDeauthStop, MENU_DEAUTH, false},
};

void actionSetWebUser();
void actionSetWebPass();
void actionSetApSsid();
void actionSetApPass();
void actionSetNethercapSsid();
void actionResetDefaults();

MenuItem configMenuItems[] = {
    {"Set Web User", actionSetWebUser, MENU_CONFIG, false},
    {"Set Web Pass", actionSetWebPass, MENU_CONFIG, false},
    {"Set AP SSID", actionSetApSsid, MENU_CONFIG, false},
    {"Set AP Pass", actionSetApPass, MENU_CONFIG, false},
    {"Set Nethercap SSID", actionSetNethercapSsid, MENU_CONFIG, false},
    {"Reset to Default", actionResetDefaults, MENU_CONFIG, false},
};

void MenuModule::init() {
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_SELECT, INPUT_PULLUP);
    pinMode(BTN_BACK, INPUT_PULLUP);
    currentState = MENU_MAIN;
    selectedIdx = 0;
    scrollOffset = 0;
    setItems(mainMenuItems, sizeof(mainMenuItems)/sizeof(MenuItem), "mrj v2");
}

void MenuModule::update() {
    readButtons();
    handleInput();
}

void MenuModule::draw() {
    if (currentState == MENU_ACTION) {
        drawAction();
    } else {
        drawMenu();
    }
}

void MenuModule::setItems(MenuItem* newItems, int count, const char* title) {
    itemCount = min(count, 20);
    for (int i = 0; i < itemCount; i++) {
        items[i] = newItems[i];
    }
    menuTitle = title;
    selectedIdx = 0;
    scrollOffset = 0;
}

void MenuModule::goBack() {
    currentState = prevState;
    selectedIdx = 0;
    scrollOffset = 0;
}

void MenuModule::setActionScreen(const char* title, const char* status) {
    prevState = currentState;
    currentState = MENU_ACTION;
    actionTitle = title;
    actionStatus = status;
}

MenuState MenuModule::getState() { return currentState; }
void MenuModule::setState(MenuState state) {
    prevState = currentState;
    currentState = state;
    selectedIdx = 0;
    scrollOffset = 0;
}

void MenuModule::readButtons() {
    btnUpPressed = false;
    btnDownPressed = false;
    btnSelectPressed = false;
    btnBackPressed = false;

    if (millis() - lastInput < MENU_SCROLL_DELAY) return;

    if (digitalRead(BTN_UP) == LOW) { btnUpPressed = true; lastInput = millis(); }
    if (digitalRead(BTN_DOWN) == LOW) { btnDownPressed = true; lastInput = millis(); }
    if (digitalRead(BTN_SELECT) == LOW) { btnSelectPressed = true; lastInput = millis(); }
    if (digitalRead(BTN_BACK) == LOW) { btnBackPressed = true; lastInput = millis(); }
}

void MenuModule::handleInput() {
    if (btnUpPressed && selectedIdx > 0) {
        selectedIdx--;
        if (selectedIdx < scrollOffset) scrollOffset = selectedIdx;
        buzzer.click();
    }
    if (btnDownPressed && selectedIdx < itemCount - 1) {
        selectedIdx++;
        if (selectedIdx >= scrollOffset + 3) scrollOffset = selectedIdx - 2;
        buzzer.click();
    }
    if (btnSelectPressed && itemCount > 0) {
        buzzer.click();
        if (items[selectedIdx].hasSubmenu) {
            prevState = currentState;
            currentState = items[selectedIdx].submenu;
            selectedIdx = 0;
            scrollOffset = 0;
        } else if (items[selectedIdx].action != nullptr) {
            items[selectedIdx].action();
        }
    }
    if (btnBackPressed) {
        buzzer.click();
        if (currentState != MENU_MAIN) {
            currentState = MENU_MAIN;
            selectedIdx = 0;
            scrollOffset = 0;
        }
    }
}

void MenuModule::drawMenu() {
    display.clear();
    display.drawString(2, 6, menuTitle, THEME_TEXT);
    display.drawLine(0, 10, display.getWidth(), 10, THEME_TEXT);

    int startY = 14;
    for (int i = 0; i < 3 && (i + scrollOffset) < itemCount; i++) {
        int idx = i + scrollOffset;
        int y = startY + i * 12;
        if (idx == selectedIdx) {
            display.fillRect(0, y - 4, display.getWidth(), 12, THEME_TEXT);
            display.drawString(4, y, items[idx].label, THEME_BG);
        } else {
            display.drawString(4, y, items[idx].label, THEME_TEXT);
        }
    }
    display.update();
}

void MenuModule::drawAction() {
    display.clear();
    display.drawStringCenter(10, actionTitle, THEME_TEXT);
    display.drawStringCenter(24, actionStatus, THEME_TEXT);
    display.update();
}

void actionNethercapMenu() {
    menu.setItems(nethercapMenuItems, 6, "Nethercap");
    menu.setState(MENU_NETHERCAP);
}

void actionDeauthMenu() {
    menu.setItems(deauthMenuItems, 3, "WiFi Deauth");
    menu.setState(MENU_DEAUTH);
}

void actionNethercapStart() {
    nethercap.start();
    menu.setActionScreen("Nethercap", "Portal Started");
}

void actionNethercapStop() {
    nethercap.stop();
    menu.setActionScreen("Nethercap", "Stopped");
}

void actionDeauthStart() {
    nethercap.startDeauthSelected();
    menu.setActionScreen("Deauth", "Running...");
}

void actionDeauthStop() {
    nethercap.stopDeauth();
    menu.setActionScreen("Deauth", "Stopped");
}

void actionBeaconSpamStart() {
    nethercap.startBeaconSpam();
    menu.setActionScreen("Beacon Spam", "Active");
}

void actionBeaconSpamStop() {
    nethercap.stopBeaconSpam();
    menu.setActionScreen("Beacon Spam", "Stopped");
}

void actionConfigMenu() {
    menu.setItems(configMenuItems, 6, "Settings");
    menu.setState(MENU_CONFIG);
}
// ============================================================
// Settings actions (simple presets - full keyboard input limited on device)
// ============================================================
void actionSetWebUser() {
    eeprom.setWebUser("admin");
    menu.setActionScreen("Web User", "Set to: admin");
}

void actionSetWebPass() {
    // Cycle between common defaults
    static int idx = 0;
    const char* passes[] = {"mrj12345", "admin123", "password", "12345678"};
    idx = (idx + 1) % 4;
    eeprom.setWebPass(passes[idx]);
    menu.setActionScreen("Web Pass", passes[idx]);
}

void actionSetApSsid() {
    eeprom.setApSsid("MRJ_AP");
    menu.setActionScreen("AP SSID", "Set to: MRJ_AP");
}

void actionSetApPass() {
    static int idx = 0;
    const char* passes[] = {"", "mrj12345", "admin123", "12345678"};
    idx = (idx + 1) % 4;
    eeprom.setApPass(passes[idx]);
    if (strlen(passes[idx]) == 0) {
        menu.setActionScreen("AP Pass", "OPEN (no pass)");
    } else {
        menu.setActionScreen("AP Pass", passes[idx]);
    }
}

void actionSetNethercapSsid() {
    eeprom.setNethercapSsid("MRJ_FreeWiFi");
    menu.setActionScreen("Nethercap", "MRJ_FreeWiFi");
}

void actionResetDefaults() {
    eeprom.resetToDefaults();
    menu.setActionScreen("Reset", "Defaults restored");
}
