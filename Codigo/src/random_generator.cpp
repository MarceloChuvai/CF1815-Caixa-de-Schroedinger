#include <Arduino.h>
#include "random_generator.h"

// -------- configuração do teste --------
#define BUF_SIZE 128
#define MAX_LAG 16
#define PRINT_INTERVAL 200
#define MAX_BITS 10000

// -------- variáveis de análise --------
unsigned long zeros = 0;
unsigned long ones  = 0;
unsigned long total = 0;
unsigned long totalBits = 0;

int8_t buf[BUF_SIZE];   // +1 / -1
int bufPos = 0;

// ---------- função de autocorrelação ----------
void printAutocorrelation(int validSamples) {
  Serial.print("R(k) lag 1-"); Serial.println(MAX_LAG);
  
  for (int k = 1; k <= MAX_LAG; k++) {
    long acc = 0;

    for (int i = 0; i < validSamples; i++) {
      int j = (i + k) % validSamples;
      acc += (long)buf[i] * (long)buf[j];
    }

    float R = (float)acc / (float)validSamples;
    Serial.print(R, 2);
    Serial.print(" ");
  }

  Serial.println();
  Serial.println("------------------------");
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);
  delay(2000);

  initRNG();   // <- vem do seu primeiro código

  Serial.println("==================================");
  Serial.println(" TRNG + Von Neumann - TESTE ");
  Serial.println(" Viés e Autocorrelação ");
  Serial.println("==================================");
  Serial.println("Total   | 0s     | 1s     | % de 1");

  // inicializa buffer
  for (int i = 0; i < BUF_SIZE; i++) {
    buf[i] = 0;
  }
}

// ---------------- Loop ----------------
void loop() {

  if (totalBits >= MAX_BITS) {
    Serial.println(">> TESTE FINALIZADO <<");
    while (true);  // trava
  }

  updateRNG();              // atualiza internamente
  int bit = getLastBit();    // pega o bit

  int8_t x = (bit == 1) ? 1 : -1;

  // atualiza buffer circular
  buf[bufPos] = x;
  bufPos = (bufPos + 1) % BUF_SIZE;

  // contagem de viés
  if (bit == 0) zeros++;
  else ones++;

  total++;
  totalBits++;

  // imprime a cada 100 bits
  if (total % 100 == 0) {
    float percentOnes = (ones * 100.0) / total;

    Serial.print(total);
    Serial.print(" | ");
    Serial.print(zeros);
    Serial.print(" | ");
    Serial.print(ones);
    Serial.print(" | ");
    Serial.print(percentOnes, 2);
    Serial.println(" %");
  }

  // imprime autocorrelação
  if (totalBits % PRINT_INTERVAL == 0) {
    int validSamples = (totalBits < BUF_SIZE) ? totalBits : BUF_SIZE;
    printAutocorrelation(validSamples);
  }
}
