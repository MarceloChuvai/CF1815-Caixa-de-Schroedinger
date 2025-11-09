#ifndef RNG_H
#define RNG_H

#include <Arduino.h>

void initRNG();
int getVonNeumannBit();
void updateRNG();
int getLastBit();

#endif
