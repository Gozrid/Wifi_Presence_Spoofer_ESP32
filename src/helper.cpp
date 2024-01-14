#include "headers/helper.h"

void SetBAR(uint8_t Value, Adafruit_MCP23017 io2)
{
    uint16_t temp = io2.readGPIOAB();
    temp = temp & 0xFF80;
    temp = temp | Value;
    io2.writeGPIOAB(temp);
}

void fillBarTo(int size, int LEDS[], Adafruit_MCP23017 io2)
{
    for (int i = 0; i < size; i++)
    {
        io2.digitalWrite(LEDS[i], HIGH);
    }
    for (int i = size; i < 10; i++)
    {
        io2.digitalWrite(LEDS[i], LOW);
    }
}

void showOnRSSIOnBar(int rssi, int LEDS[], Adafruit_MCP23017 io2)
{
    if (rssi < -90)
    {
        fillBarTo(1, LEDS, io2);
    }
    else if (rssi < -80)
    {
        fillBarTo(2, LEDS, io2);
    }
    else if (rssi < -70)
    {
        fillBarTo(3, LEDS, io2);
    }
    else if (rssi < -67)
    {
        fillBarTo(4, LEDS, io2);
    }
    else if (rssi < -55)
    {
        fillBarTo(5, LEDS, io2);
    }
    else if (rssi < -30)
    {
        fillBarTo(6, LEDS, io2);
    }
    else
    {
        fillBarTo(10, LEDS, io2);
    }
}

void checkConnection(bool* connectedToSta, LiquidCrystal_I2C lcd)
{
    if (!WiFi.isConnected() && *connectedToSta == true)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Disconnected!");
        lcd.setCursor(0, 1);
        lcd.print("Connecting!");
        *connectedToSta = false;
    }
    else if (WiFi.isConnected() && *connectedToSta == false)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Connected!   IP:");
        lcd.setCursor(0, 1);
        lcd.print(WiFi.localIP());
        *connectedToSta = true;
    }
}