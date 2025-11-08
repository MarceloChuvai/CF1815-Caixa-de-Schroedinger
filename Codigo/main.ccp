# include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// --- Configurações ---
#define LED_PIN      6     // Pino de dados dos LEDs (ex: 6)
#define LED_COUNT    8     // Número de LEDs
#define JUMPER_1_PIN 2     // Primeiro jumper (digital 2)
#define JUMPER_2_PIN 3     // Segundo jumper (digital 3)
#define ANALOG_PIN   A0    // Fonte de entropia

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- Variáveis do gerador de bits ---
int32_t last_value = 1;
long random_a = 0;
long random_c = 0;
long random_m = 0;
int ultimo_bit = 0;

// --- Inicialização do gerador ---
void discardInitialRead() {
  analogRead(ANALOG_PIN);
  delay(5);
}

void initLCG() {
  long r1 = analogRead(ANALOG_PIN); delay(5);
  long r2 = analogRead(ANALOG_PIN); delay(5);
  long r3 = analogRead(ANALOG_PIN); delay(5);

  random_m = ((r1 << 10) | r2)  & 0x7FFFFFFF;
  random_a = ((r2 << 10) | r3) & 0x7FFFFFFF;
  random_c = (r3 ^ micros()) & 0x7FFF;

  if (random_a == 0) random_a = 1;
  if (random_m == 0) random_m = 1;
  if (random_c == 0) random_c = 1;
  if (random_m <= random_a) random_m = random_a + 1;

  last_value = ((r1 << 2) ^ r2 ^ r3) & 0x7FFFFFFF;
  if (last_value == 0) last_value = 1;
}

int32_t true_random_hybrid() {
  int32_t x = (last_value * random_a + random_c) % random_m;
  int32_t analog_noise = analogRead(ANALOG_PIN);
  analog_noise ^= analogRead(ANALOG_PIN) << 10;
  analog_noise ^= analogRead(ANALOG_PIN) << 20;
  x ^= analog_noise;
  return (last_value = x);
}

int mixed_bit_full(int32_t n) {
  n ^= n >> 16;
  n ^= n >> 8;
  n ^= n >> 4;
  n ^= n >> 2;
  n ^= n >> 1;
  return n & 1;
}

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

// --- LEDs ---
void colorAll(uint32_t color) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void setup() {
  Serial.begin(9600);
  pinMode(JUMPER_1_PIN, INPUT_PULLUP);
  pinMode(JUMPER_2_PIN, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  discardInitialRead();
  initLCG();
}

void loop() {
  bool contatoFeito = digitalRead(JUMPER_1_PIN) == LOW && digitalRead(JUMPER_2_PIN) == LOW;

  if (!contatoFeito) {
    // Geração de bits e piscar branco
    ultimo_bit = vonNeumannBit(last_value);
    Serial.println(ultimo_bit);
    colorAll(strip.Color(255, 255, 255)); // Branco
    delay(100);
    colorAll(strip.Color(0, 0, 0));       // Apaga
    delay(100);
  } else {
    // Parar geração e mostrar resultado
    if (ultimo_bit == 0) {
      colorAll(strip.Color(255, 0, 0));   // Vermelho
    } else {
      colorAll(strip.Color(0, 255, 0));   // Verde
    }
    while (true); // trava aqui até reset
  }
}
