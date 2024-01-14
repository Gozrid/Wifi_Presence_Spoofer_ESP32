#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "defines.h"

void SetBAR(uint8_t Value, Adafruit_MCP23017 io2);
void showOnRSSIOnBar(int rssi, int LEDS[], Adafruit_MCP23017 io2);
void checkConnection(bool* connectedToSta, LiquidCrystal_I2C lcd);
void fillBarTo(int size, int LEDS[], Adafruit_MCP23017 io2);