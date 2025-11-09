#include "random_generator.h"

const int waitTime = 16;

static byte leftStack = 0;
static byte rightStack = 0;
static byte lastByte = 0;
static int lastBit = 0;
static unsigned long lastGenTime = 0;

byte rotate(byte b, int r) {
  return (b << r) | (b >> (8 - r));
}

void pushLeftStack(byte bitToPush) {
  leftStack = (leftStack << 1) ^ bitToPush ^ leftStack;
}

void pushRightStackRight(byte bitToPush) {
  rightStack = (rightStack >> 1) ^ (bitToPush << 7) ^ rightStack;
}

byte getTrueRotateRandomByte() {
  byte finalByte = 0;
  byte lastStack = leftStack ^ rightStack;

  for (int i = 0; i < 4; i++) {
    delayMicroseconds(waitTime);
    int leftBits = analogRead(A0);

    delayMicroseconds(waitTime);
    int rightBits = analogRead(A1);

    finalByte ^= rotate(leftBits, i);
    finalByte ^= rotate(rightBits, 7 - i);

    for (int j = 0; j < 8; j++) {
      byte leftBit = (leftBits >> j) & 1;
      byte rightBit = (rightBits >> j) & 1;

      if (leftBit != rightBit) {
        if (lastStack % 2 == 0)
          pushLeftStack(leftBit);
        else
          pushRightStackRight(leftBit);
      }
    }
  }

  lastByte ^= (lastByte >> 3) ^ (lastByte << 5) ^ (lastByte >> 4);
  lastByte ^= finalByte;

  return lastByte ^ leftStack ^ rightStack;
}

// Correção de Von Neumann
int getVonNeumannBit() {
  while (true) {
    byte b1 = getTrueRotateRandomByte();
    byte b2 = getTrueRotateRandomByte();

    if (b1 != b2) {
      return (b1 > b2) ? 1 : 0;
    }
  }
}

void updateRNG() {
  if (millis() - lastGenTime > 5) {
    lastGenTime = millis();
    lastBit = getVonNeumannBit();
  }
}

int getLastBit() {
  return lastBit;
}

void initRNG() {
  analogReference(DEFAULT);
}
