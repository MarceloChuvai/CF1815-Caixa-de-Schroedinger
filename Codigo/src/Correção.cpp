#include <Adafruit_NeoPixel.h>

#define LED_PIN     6     // Pino de dados do NeoPixel
#define BUTTON_PIN  3     // Botão ligado ao 5V (com pull-down de 10k)
#define NUM_PIXELS  1     // Número de LEDs NeoPixel

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();      
  strip.show();        // Inicializa o LED apagado
  pinMode(BUTTON_PIN, INPUT);   // Botão para 5V com resistor de pull-down
}

void loop() {
  int pressed = digitalRead(BUTTON_PIN);

  if (pressed == HIGH) {
    // Botão apertado → LED branco
    strip.setPixelColor(0, strip.Color(255, 255, 255));
  } else {
    // Botão solto → LED apagado
    strip.setPixelColor(0, 0, 0, 0);
  }

  strip.show();
}
