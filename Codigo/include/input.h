#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <stdint.h>

void initInputPin(uint8_t pin);
bool isButtonPressed(uint8_t pin);

#endif
