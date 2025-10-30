#include <Arduino.h>

int analog_pin = A0; // Pino analógico usado como fonte de entropia

int32_t last_value = 1;
long random_a = 0;
long random_c = 0;
long random_m = 0;

int contador = 0;

// Descarte inicial para estabilizar leitura analógica
void discardInitialRead() {
  analogRead(analog_pin);
  delay(5);
}

// Inicializa o LCG com entropia das leituras analógicas
void initLCG() {
  long r1 = analogRead(analog_pin); delay(5);
  long r2 = analogRead(analog_pin); delay(5);
  long r3 = analogRead(analog_pin); delay(5);

  random_m = ((r1 << 10) | r2) & 0x7FFFFFFF;
  random_a = ((r2 << 10) | r3) & 0x7FFFFFFF;
  random_c = (r3 ^ micros()) & 0x7FFF; // mistura com tempo

  if (random_a == 0) random_a = 1;
  if (random_m == 0) random_m = 1;
  if (random_c == 0) random_c = 1;
  if (random_m <= random_a) random_m = random_a + 1;

  last_value = ((r1 << 2) ^ r2 ^ r3) & 0x7FFFFFFF;
  if (last_value == 0) last_value = 1;
}

// Gera número híbrido LCG + múltiplas leituras analógicas
int32_t true_random_hybrid() {
  int32_t x = (last_value * random_a + random_c) % random_m;

  int32_t analog_noise = analogRead(analog_pin);
  analog_noise ^= analogRead(analog_pin) << 10;
  analog_noise ^= analogRead(analog_pin) << 20;

  x ^= analog_noise;

  return (last_value = x);
}

// Mistura todos os bits para reduzir viés
int mixed_bit_full(int32_t n) {
  n ^= n >> 16;
  n ^= n >> 8;
  n ^= n >> 4;
  n ^= n >> 2;
  n ^= n >> 1;
  return n & 1;
}

// Extração de Von Neumann para eliminar viés
int vonNeumannBit(int32_t &state) {
  int b1, b2;
  while (true) {
    int r = true_random_hybrid();
    b1 = mixed_bit_full(r);
    r = true_random_hybrid();
    b2 = mixed_bit_full(r);

    if (b1 != b2) return b1;
  }
}

void setup() {
  Serial.begin(9600);
  discardInitialRead();
  initLCG();
}

void loop() {
  if (contador < 10000) {
    int bit = vonNeumannBit(last_value);
    Serial.println(bit);
    contador++;
    delay(10);
  } else {
    while (true) {
      delay(1000); // mantém o loop vivo sem travar
    }
  }
}
