#include "ApiManager.h"

ApiManager::ApiManager() {}

void ApiManager::init(const char *ssid, const char *pwd, uint16_t port)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pwd);

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }


    // OTA BEGIN

    ArduinoOTA.setPort(3232);

    ArduinoOTA
        .onStart([]()
                 {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
        .onEnd([]()
               { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
        .onError([](ota_error_t error)
                 {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });

    ArduinoOTA.begin();

    // OTA END

    Serial.println();
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());

    server.begin(port);
}

void ApiManager::setRootPath(String rootPath)
{
    root_path = rootPath;
}

void ApiManager::addRoute(String path, HTTPMethod method, WebServer::THandlerFunction fn)
{
    server.on(root_path + path, method, fn);
}

void ApiManager::getResponseJson(JsonDocument &jsonDocument)
{
    String body = server.arg("plain");
    deserializeJson(jsonDocument, body);
}

void ApiManager::sendResponseJson(int code, JsonDocument &jsonDocument)
{
    char buffer[sizeof(jsonDocument)];
    serializeJson(jsonDocument, buffer);
    server.send(code, "application/json", buffer);
}

void ApiManager::handleClient()
{
    ArduinoOTA.handle();
    server.handleClient();
}