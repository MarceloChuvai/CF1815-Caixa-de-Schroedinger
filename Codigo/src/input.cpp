#include "input.h"

void initInputPin(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
}

bool isButtonPressed(uint8_t pin) {
  return digitalRead(pin) == LOW; // ativo em LOW
}
