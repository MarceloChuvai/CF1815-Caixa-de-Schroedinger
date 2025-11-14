#include <Adafruit_NeoPixel.h>

#define LED_PIN    6        // pino de dados do NeoPixel
#define NUM_PIXELS 1        // quantidade de LEDs
#define BUTTON_PIN 3        // botão para 5V com pull-down externo

Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();            // inicializa apagado
  pinMode(BUTTON_PIN, INPUT);   // botão vai para 5V, com pull-down para GND
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // LED brilha em branco
    strip.setPixelColor(0, strip.Color(255, 255, 255));
    strip.show();
  } else {
    // LED apagado
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
  }
}
  // Preenche o anel com AZUL
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  delay(500);
  
  // Apaga todos os LEDs
  colorWipe(strip.Color(0, 0, 0), 50); // Off
  delay(1000);
}

// Função auxiliar para o efeito de preenchimento (Color Wipe)
// Recebe uma cor (no formato 32-bit) e um tempo de espera
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) { // Para cada pixel...
    strip.setPixelColor(i, color);         // Define a cor do pixel
    strip.show();                          // Envia os dados para o anel
    delay(wait);                           // Espera
  }
}  }
}
