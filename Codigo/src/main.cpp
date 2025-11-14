#include <Arduino.h>
#include "led_control.h"
#include "random_generator.h"
#include "input.h"

#define LED_PIN 6
#define BUTTON_PIN 3
#define NUM_PIXELS 8

void setup() {
  initLED(LED_PIN, NUM_PIXELS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool isPressed() {
  return digitalRead(BUTTON_PIN) == LOW;
}

void loop() {
  static bool buttonHeld = false;
  updateRNG();

  if (isButtonPressed(BUTTON_PIN)) {

    // BOTÃO APERTADO
    buttonHeld = true;
    showBlink(255, 255, 255, 150);

  } else {

    // BOTÃO SOLTO
    if (buttonHeld) {
      buttonHeld = false;

      int bit = getLastBit();
      if (bit == 1)
        showColor(0, 255, 0);   // verde
      else
        showColor(255, 0, 0);   // vermelho
    }
  }
}
