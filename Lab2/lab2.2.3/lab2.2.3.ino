/*-------------------------------------------------------------------------------

2.3 A simple reflex game: built with two components (2 micro switches) to test 
    the players' reactions and three indicators (3 LEDs): two to show who pressed 
    the button first and one to inform players when they can start competing 
    (Start/Stop). Assumptions for the game operation:

    - The start signal lights up for a random duration (green LED).
    - The signal turns off, activating the reflex-testing components.
    - Players' reflexes are tested (who presses their button first).
    - The indicator for the faster player lights up (red LED).
    - The game returns to step one.

-------------------------------------------------------------------------------*/

#include <Bounce2.h>

#define P1_BUTTON_PIN 3
#define P1_LED_PIN 4
#define P2_LED_PIN 5
#define P2_BUTTON_PIN 6
#define START_LED_PIN 7

Bounce P1_debouncer = Bounce();
Bounce P2_debouncer = Bounce();

unsigned long start_led_time;
long random_time;

void setup() {
  randomSeed(analogRead(0));

  pinMode(P1_LED_PIN, OUTPUT);
  pinMode(P2_LED_PIN, OUTPUT);
  pinMode(START_LED_PIN, OUTPUT);

  pinMode(P1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(P2_BUTTON_PIN, INPUT_PULLUP);

  P1_debouncer.attach(P1_BUTTON_PIN);
  P1_debouncer.interval(5);

  P2_debouncer.attach(P2_BUTTON_PIN);
  P2_debouncer.interval(5);

  start_led_time = millis();
  random_time = random(50, 3000);
  digitalWrite(START_LED_PIN, HIGH);
}

void loop() {
  P1_debouncer.update();
  P2_debouncer.update();

  unsigned long time_passed = millis() - start_led_time;

  if (time_passed > random_time) {
    digitalWrite(START_LED_PIN, LOW);
    int winner = 0; // 0 - NONE, 1 - P1, 2 - P2, 3 - DRAW

    if (P1_debouncer.fell()) winner += 1;
    if (P2_debouncer.fell()) winner += 2;

    switch (winner) {
      case 1: P1Win(); break;
      case 2: P2Win(); break;
      case 3: Draw(); break;
    }
  }
}

void P1Win() {
  digitalWrite(P1_LED_PIN, HIGH);
  delay(3000);
  digitalWrite(P1_LED_PIN, LOW);

  startAgain();
}

void P2Win() {
  digitalWrite(P2_LED_PIN, HIGH);
  delay(3000);
  digitalWrite(P2_LED_PIN, LOW);

  startAgain();
}

void Draw() {
  digitalWrite(P1_LED_PIN, HIGH);
  digitalWrite(P2_LED_PIN, HIGH);
  delay(3000);
  digitalWrite(P1_LED_PIN, LOW);
  digitalWrite(P2_LED_PIN, LOW);

  startAgain();
}

void startAgain() {
  random_time = random(50, 3000);
  start_led_time = millis();
  digitalWrite(START_LED_PIN, HIGH);
}
