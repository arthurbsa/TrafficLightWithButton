/*
 * Projeto: Semáforo com Modo Noturno e Controle por Botão
 * Autor: Jackson Sá
 * Data: Junho de 2025
 * Plataforma: Arduino (compatível com Uno, Nano, etc.)
 *
 * Descrição:
 * - Controla três LEDs simulando um semáforo.
 * - Modo normal: alterna entre vermelho, verde e amarelo com tempos definidos.
 * - Modo noturno: pisca o LED amarelo a cada 500 ms.
 * - Um botão alterna entre o modo normal e o noturno.
 *
 * Recursos:
 * - Debounce de botão implementado.
 * - Logs via Serial para depuração e monitoramento.
 */

const uint8_t PIN_LED_RED = 11;
const uint8_t PIN_LED_YELLOW = 5;
const uint8_t PIN_LED_GREEN = 8;
const uint8_t PIN_BUTTON = 2;

// Tempos em milissegundos (modo normal)
const unsigned long TIME_RED = 7000;
const unsigned long TIME_GREEN = 7000;
const unsigned long TIME_YELLOW = 3000;
const unsigned long TIME_BLINK = 500; // Piscar no modo noturno

// Estados do semáforo
enum TrafficLightState {
  RED,
  GREEN,
  YELLOW
};

// Estados do botão
enum ButtonState {
  IDLE,
  PRESSED,
  DEBOUNCING
};

// Variáveis de estado
TrafficLightState trafficState = RED;
ButtonState buttonState = IDLE;
bool nightMode = true; // Começa no modo noturno

// Variáveis de temporização
unsigned long previousMillis = 0;
unsigned long buttonPreviousMillis = 0;

void setup() {
  Serial.begin(9600);
  
  // Configura os pinos
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  // Estado inicial dos LEDs
  allLedsOff();
  
  // Teste inicial dos LEDs
  testLeds();

  logState("Sistema iniciado. Modo noturno ativado.");
}

void loop() {
  unsigned long currentMillis = millis();

  // Atualiza o botão
  updateButtonState(currentMillis);

  // Atualiza o semáforo ou entra no modo noturno
  if (!nightMode) {
    updateTrafficLight(currentMillis);
  } else {
    blinkYellow(currentMillis);
  }
}

// Log padronizado
void logState(const char* message) {
  Serial.println(message);
}

// Atualiza a máquina de estados do botão
void updateButtonState(unsigned long currentMillis) {
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(PIN_BUTTON);

  switch (buttonState) {
    case IDLE:
      if (currentButtonState == LOW && lastButtonState == HIGH) {
        buttonState = DEBOUNCING;
        buttonPreviousMillis = currentMillis;
        logState("Botão pressionado - iniciando debounce...");
      }
      break;

    case DEBOUNCING:
      if (currentMillis - buttonPreviousMillis >= 50) {
        if (digitalRead(PIN_BUTTON) == LOW) {
          buttonState = PRESSED;
        } else {
          buttonState = IDLE;
          logState("Ruído de botão descartado.");
        }
      }
      break;

    case PRESSED:
      nightMode = !nightMode;
      allLedsOff();
      logState(nightMode ? "Modo noturno: ON" : "Modo noturno: OFF");
      buttonState = IDLE;
      break;
  }

  lastButtonState = currentButtonState;
}

// Atualiza o semáforo (modo normal)
void updateTrafficLight(unsigned long currentMillis) {
  switch (trafficState) {
    case RED:
      digitalWrite(PIN_LED_RED, HIGH);
      digitalWrite(PIN_LED_YELLOW, LOW);
      digitalWrite(PIN_LED_GREEN, LOW);
      if (currentMillis - previousMillis >= TIME_RED) {
        trafficState = GREEN;
        previousMillis = currentMillis;
        logState("Transição: VERMELHO → VERDE");
      }
      break;

    case GREEN:
      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_GREEN, HIGH);
      digitalWrite(PIN_LED_YELLOW, LOW);
      if (currentMillis - previousMillis >= TIME_GREEN) {
        trafficState = YELLOW;
        previousMillis = currentMillis;
        logState("Transição: VERDE → AMARELO");
      }
      break;

    case YELLOW:
      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_GREEN, LOW);
      digitalWrite(PIN_LED_YELLOW, HIGH);
      if (currentMillis - previousMillis >= TIME_YELLOW) {
        trafficState = RED;
        previousMillis = currentMillis;
        logState("Transição: AMARELO → VERMELHO");
      }
      break;
  }
}

// Piscar o LED amarelo (modo noturno)
void blinkYellow(unsigned long currentMillis) {
  static bool yellowState = false;
  static unsigned long previousBlinkMillis = 0;

  if (currentMillis - previousBlinkMillis >= TIME_BLINK) {
    yellowState = !yellowState;
    digitalWrite(PIN_LED_YELLOW, yellowState ? HIGH : LOW);
    previousBlinkMillis = currentMillis;
    // logState("Piscar LED AMARELO"); // Descomente se quiser ver cada piscada
  }

  // Garante que os outros LEDs estão apagados
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

// Apaga todos os LEDs
void allLedsOff() {
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

// Teste inicial dos LEDs
void testLeds() {
  digitalWrite(PIN_LED_RED, HIGH);
  delay(500);
  digitalWrite(PIN_LED_RED, LOW);

  digitalWrite(PIN_LED_YELLOW, HIGH);
  delay(500);
  digitalWrite(PIN_LED_YELLOW, LOW);

  digitalWrite(PIN_LED_GREEN, HIGH);
  delay(500);
  digitalWrite(PIN_LED_GREEN, LOW);
}
