#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

Adafruit_MCP23017 io2;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int LEDS[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
int KEYS[] = {10, 11, 12};
bool connectedToSta;