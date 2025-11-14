#include <Adafruit_NeoPixel.h>

// --- Configurações que você DEVE alterar ---

// 1. Qual pino do ESP32 está conectado ao pino D1 (DIN) do anel?
#define LED_PIN   32  // Use um pino GPIO válido, como 15, 4, 5, etc.

// 2. Quantos LEDs o seu anel possui?
#define LED_COUNT 8

// -------------------------------------------

// Inicializa o objeto NeoPixel
// Parâmetros: (Número de LEDs, Pino de dados, Tipo do LED)
// NEO_GRB + NEO_KHZ800 é o tipo mais comum para WS2812B
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200); // Inicia o monitor serial (para debug)
  
  strip.begin();           // Inicializa a biblioteca NeoPixel
  strip.show();            // Apaga todos os pixels (estado inicial)
  
  // Ajuste o brilho para um valor seguro (0-255)
  // NUNCA comece com 255, especialmente se estiver alimentando pela USB!
  strip.setBrightness(50);
}

void loop() {
  // Preenche o anel com VERMELHO
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  delay(500);

  // Preenche o anel com VERDE
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  delay(500);

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
