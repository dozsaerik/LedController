#ifndef ApiManager_H
#define ApiManager_H

#include <stdint.h>
#include <string.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>

class ApiManager
{
public:
    WebServer server;
    String root_path = "";

    ApiManager();

    void init(const char *ssid, const char *pwd, uint16_t port);
    void setRootPath(String rootPath);
    void addRoute(String path, HTTPMethod method, WebServer::THandlerFunction fn);
    void getResponseJson(JsonDocument &jsonDocument);
    void sendResponseJson(int code, JsonDocument &jsonDocument);
    void handleClient();
};

#endif