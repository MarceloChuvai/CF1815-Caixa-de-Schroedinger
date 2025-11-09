#include <Arduino.h>
#include "random_bit_generator.h"
#include "led_controller.h"
#include "button_handler.h"

#define BUTTON_PIN 3
#define ACTIVE_LED 0  // LED que representa o bit atual

int lastBit = 0;

void setup() {
  initLEDs();
  initButton(BUTTON_PIN);
  initRandomSeed();
}

void loop() {
  bool pressed = isButtonPressed(BUTTON_PIN);

  if (pressed) {
    // Enquanto o botão estiver pressionado, mostra cor fixa
    if (lastBit == 0)
      showColor(ACTIVE_LED, 255, 0, 0);  // Vermelho
    else
      showColor(ACTIVE_LED, 0, 255, 0);  // Verde
  } else {
    // Geração de bit e piscar branco
    lastBit = generateRandomBit();
    blinkWhite(ACTIVE_LED, 200);
  }
}

