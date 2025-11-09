#include "led_control.h"
#include <Adafruit_NeoPixel.h>

static Adafruit_NeoPixel* strip = nullptr;
static unsigned long lastBlink = 0;
static bool blinkState = false;

void initLED(int pin, int numPixels) {
  if (strip) return; // evita reinicializar
  strip = new Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
  strip->begin();
  strip->show(); // tudo apagado
}

void showColor(uint8_t r, uint8_t g, uint8_t b) {
  if (!strip) return;
  for (uint16_t i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, strip->Color(r, g, b));
  }
  strip->show();
}

void showBlink(uint8_t r, uint8_t g, uint8_t b, int delayTime) {
  if (!strip) return;
  unsigned long now = millis();
  if (now - lastBlink >= (unsigned long)delayTime) {
    lastBlink = now;
    blinkState = !blinkState;
    if (blinkState) {
      showColor(r, g, b);   // liga
    } else {
      showColor(0, 0, 0);   // apaga
    }
  }
}
