#include "StripManager.h"

#define DATA_PIN 15
#define CHIP_TYPE WS2811Controller800Khz
#define COLOR_ORDER GRB

StripManager::StripManager(uint8_t ledModulesCount)
{
    strip = (CRGB *)calloc(ledModulesCount, sizeof(CRGB));
    FastLED.addLeds<CHIP_TYPE, DATA_PIN, COLOR_ORDER>(strip, ledModulesCount).setCorrection(TypicalLEDStrip);
}

StripManager::~StripManager()
{
    free(strip);
    strip = nullptr;
}

void StripManager::setPixel(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    strip[index] = CRGB(red, green, blue);
}

void StripManager::setPixelFromTo(uint8_t from, uint8_t to, uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint8_t i = from; i <= to; i++)
    {
        setPixel(i, red, green, blue);
    }
}

void StripManager::setSection(JsonArray section)
{
    for (uint16_t i = 0; i < section.size(); i++)
    {
        JsonArray current = section[i];
        uint16_t from = current[0];
        uint16_t to = current[1];
        uint16_t red = current[2];
        uint16_t green = current[3];
        uint16_t blue = current[4];

        setPixelFromTo(from, to, red, green, blue);
        FastLED.show();
    }
}