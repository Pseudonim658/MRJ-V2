#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "display.h"
#include "hardware_pinout.h"
#include "buzzer.h"
#include "config.h"

enum MenuState {
    MENU_MAIN,
    MENU_NETHERCAP,
    MENU_DEAUTH,
    MENU_WIFI,
    MENU_BLE,
    MENU_SUBGHZ,
    MENU_RFID,
    MENU_NFC,
    MENU_IBUTTON,
    MENU_IR,
    MENU_BADUSB,
    MENU_GPIO,
    MENU_SETTINGS,
    MENU_WEB,
    MENU_SDCARD,
    MENU_ACTION,
    MENU_CONFIG
};

struct MenuItem {
    const char* label;
    void (*action)();
    MenuState submenu;
    bool hasSubmenu;
};

class MenuModule {
public:
    void init();
    void update();
    void draw();
    void setItems(MenuItem* items, int count, const char* title);
    void goBack();
    void setActionScreen(const char* title, const char* status);
    MenuState getState();
    void setState(MenuState state);

private:
    MenuItem items[20];
    int itemCount = 0;
    int selectedIdx = 0;
    int scrollOffset = 0;
    const char* menuTitle = "";
    MenuState currentState = MENU_MAIN;
    MenuState prevState = MENU_MAIN;

    bool btnUpPressed = false;
    bool btnDownPressed = false;
    bool btnSelectPressed = false;
    bool btnBackPressed = false;
    unsigned long lastInput = 0;

    const char* actionTitle = "";
    const char* actionStatus = "";

    void readButtons();
    void handleInput();
    void drawMenu();
    void drawAction();
};

extern MenuModule menu;

#endif