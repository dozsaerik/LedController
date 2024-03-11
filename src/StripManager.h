#ifndef StripManager_H
#define StripManager_H

#include <stdint.h>
#include <FastLED.h>
#include <ArduinoJson.h>

class StripManager
{

public:
    CRGB *strip;

    StripManager(uint8_t ledModulesCount);
    ~StripManager();

    void setPixel(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
    void setPixelFromTo(uint8_t from, uint8_t to, uint8_t red, uint8_t green, uint8_t blue);
    void setSection(JsonArray section);
};

#endif