#include "headers/main.h"
#include "headers/defines.h"
#include "headers/variables.h"
#include "headers/helper.h"
#include "headers/events.h"
#include "config.h"

unsigned long currentMillis;
unsigned long previousMillis;

void setup() {
    SetBAR(1 << 10, io2);
    Serial.begin(115200);
    delay(1000);
    Serial.println("ESP32 Board Wifi Presence Spoofer");

    lcd.init();
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("Wifi Presence-");
    lcd.setCursor(4, 1);
    lcd.print("-Spoofer");
    delay(1000);

    io2.begin(2);
    for (int i = 0; i <= 9; i++) {
        io2.pinMode(LEDS[i], OUTPUT);
        io2.digitalWrite(LEDS[i], 0);
    }

    for (int i = 0; i <= 2; i++) {
        io2.pinMode(KEYS[i], INPUT);
        io2.pullUp(KEYS[i], HIGH);
    }

    WiFi.mode(WIFI_STA);
    WiFi.onEvent(connected, ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(disconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

#if defined(WPA2_ENTERPRISE)
    WiFi.begin(SSID, WPA2_AUTH_PEAP, "", USERNAME, PASSWORD);
#else
    WiFi.begin(SSID, PASSWORD);
#endif
    connectedToSta = true;
    previousMillis = millis();
}

void loop() {
    currentMillis = millis();
    if (currentMillis - previousMillis >= ENERGY_TIMEOUT) {
        lcd.noBacklight();
        lcd.noDisplay();
        fillBarTo(0, LEDS, io2);
    } else {
        lcd.backlight();
        lcd.display();
        showOnRSSIOnBar(WiFi.RSSI(), LEDS, io2);
    }
    if (io2.digitalRead(KEY1) == LOW
        || io2.digitalRead(KEY2) == LOW
        || io2.digitalRead(KEY3) == LOW) {
        previousMillis = currentMillis;
    }
    checkConnection(&connectedToSta, lcd);
    delay(150);
}
