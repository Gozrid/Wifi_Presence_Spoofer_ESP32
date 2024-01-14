#include "headers/events.h"

void disconnected(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info)
{
  Serial.print("DISCONNECTED!");
  Serial.println(" Trying to connect!");
}

void connected(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info)
{
  Serial.print("CONNECTED! IP:");
  Serial.println(WiFi.localIP());
}