#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

void initLED(int pin, int numPixels);
void showBlink(uint8_t r, uint8_t g, uint8_t b, int delayTime);
void showColor(uint8_t r, uint8_t g, uint8_t b);

#endif
