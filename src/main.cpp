#include <WiFi.h>
#include <WebServer.h>
#include "StripManager.h"
#include "ApiManager.h"

#define LED_MODULES_COUNT 128

StripManager stripManager(LED_MODULES_COUNT);
ApiManager apiManager;

DynamicJsonDocument jsonDocument(512);

const char *SSID = "DecoM4R";
const char *PWD = "936211dozsa";
const uint16_t PORT = 80;

void post_strip()
{
  apiManager.getResponseJson(jsonDocument);

  JsonArray section = jsonDocument["section"];
  stripManager.setSection(section);

  jsonDocument.clear();
  jsonDocument["status"] = "ok";
  apiManager.sendResponseJson(200, jsonDocument);
}

void setup()
{
  Serial.begin(115200);
  stripManager.setPixelFromTo(0, LED_MODULES_COUNT - 1, 255, 0, 0);
  apiManager.init(SSID, PWD, PORT);
  apiManager.setRootPath("/api/v1");
  apiManager.addRoute("/strip", HTTP_POST, post_strip);
}

void loop()
{
  apiManager.handleClient();
}