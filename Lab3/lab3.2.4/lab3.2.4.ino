/*-------------------------------------------------------------------------------

2.4 Using the program skeleton below, propose your own concept for a great 
	project using the learned electronic components.

String command;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  if (Serial.available()) { 
    command = Serial.readStringUntil('\n');

    if (command.equals("init")) {
      initialize();
    } 
    else if (command.equals("send")) {
      send_message();
    } 
    else if (command.equals("data")) {
      get_data();
    } 
    else if (command.equals("result")) {
      show_result();
    } 
    else {
      Serial.println("Invalid command");
    }
  }
}

-------------------------------------------------------------------------------*/

#include <Bounce2.h>

/* ---------------- BOARD ELEMENTS ---------------- */

// Potentiometer
#define POTENTIOMETER_PIN A0

// LEDs
#define LED_1_PIN 9
#define LED_2_PIN 8
#define LED_3_PIN 7
#define LED_4_PIN 6
#define LED_5_PIN 5
#define LED_6_PIN 4

byte leds_pins[6] = {
  LED_1_PIN,
  LED_2_PIN,
  LED_3_PIN,
  LED_4_PIN,
  LED_5_PIN,
  LED_6_PIN
};

// Next and confirm buttons
#define NEXT_BUTTON_PIN    3
#define CONFIRM_BUTTON_PIN 2

Bounce2::Button next_button    = Bounce2::Button();
Bounce2::Button confirm_button = Bounce2::Button();


/* ---------------- FUNCTIONS ---------------- */

void startNewGame();                  // start new game
void nextRound();                     // go to the next level after correct answer
void continuePlaying();               // continue playing after wrong answer
void showResult();                    // end game and show result
void checkSequence(byte level);       // check answer count correct answers or mistakes
void generateNewSequence(byte level); // generate new sequence
void showSequence(byte level);        // show sequence using LEDs
bool isSequenceCorrect(byte level);   // check if entered sequence is correct


/* ---------------- GLOBAL VARIABLES ---------------- */

// Game varaibles
String command;
bool game_over = false;
int mistakes = 0;
int correct = 0;

int pot_value = 500;
byte level = 0;

byte sequence[100];
byte entered_sequence[100];
byte index = 0;
byte selected_digit = 0;


/* ---------------- MAIN FUNCTIONS ---------------- */

void setup () {
  randomSeed(analogRead(A3));

  while (!Serial);
  Serial.begin(9600);
  Serial.println("Memory game.");
  Serial.println("Use potentiometer to set leds blinking time.");
  Serial.println("Type 'start' to start the game.");
  Serial.println("");

  // set pins
  pinMode(POTENTIOMETER_PIN, INPUT);
  for (byte i = 0; i < 6; i++) pinMode(leds_pins[i], OUTPUT);

  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
  next_button.attach(NEXT_BUTTON_PIN);
  next_button.interval(5);

  pinMode(CONFIRM_BUTTON_PIN, INPUT_PULLUP);
  confirm_button.attach(CONFIRM_BUTTON_PIN);
  confirm_button.interval(5);
}

void loop () {
  pot_value = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 50, 1000);

  // react to commands
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    Serial.print("Command: '");
    Serial.print(command);
    Serial.println("'");

    if (command == "start") startNewGame();
    else if (command == "next") nextRound();
    else if (command == "continue") continuePlaying();
    else if (command == "result") showResult();
    else Serial.println("Invalid command");
  }

  // react to buttons
  if (!game_over && level > 0) {
    next_button.update();
    confirm_button.update();

    if (confirm_button.pressed()) {
      entered_sequence[index++] = selected_digit;

      digitalWrite(leds_pins[selected_digit - 1], LOW);
      selected_digit = 0;

      if (index >= level) checkSequence(level);
    }

    if (next_button.pressed()) {
      if (selected_digit > 0) digitalWrite(leds_pins[selected_digit - 1], LOW);
      selected_digit = (selected_digit + 1) % 7;
      if (selected_digit > 0) digitalWrite(leds_pins[selected_digit - 1], HIGH);
    }
  }

  delay(1);
}


/* ---------------- GAME FUNCTIONS ---------------- */

void startNewGame() {
  // turn off all LEDs
  for (byte i = 0; i < 6; i++) digitalWrite(leds_pins[i], LOW);

  //reset values
  level = 1;
  game_over = false;
  mistakes = 0;
  correct = 0;

  generateNewSequence(100);
  showSequence(level);

  Serial.println("Input sequence using left button to select led and right to confirm.");
  Serial.println("");
}

void nextRound() {
  if (game_over && level > 0) return;

  level++;

  /// generateNewSequence(level);
  showSequence(level);
}

void continuePlaying() {
  if (level <= 0) return;

  game_over = false;
  level--;

  // generateNewSequence(level);
  showSequence(level);
}

void showResult() {
  for (byte i = 0; i < 6; i++) digitalWrite(leds_pins[i], HIGH);

  Serial.print("You have reached level: ");
  Serial.print(level);
  Serial.print(" with ");
  Serial.print(mistakes);
  Serial.print(" mistakes and ");
  Serial.print(correct);
  Serial.println(" correct answers.");

  game_over = true;
  level = 0;

  Serial.println("Use 'start' command to start new game.");
  Serial.println();
}

void checkSequence(byte level) {
  if (isSequenceCorrect(level)) {
    correct++;
    Serial.println("Correct.");
    Serial.println("Use 'next' command to start next level.");
    Serial.println("Use 'result' command to end game and see your result.");
    Serial.println();
  } else {
    mistakes++;
    game_over = true;
    Serial.println("Inorrect.");
    Serial.println("Use 'continue' command to continue playing.");
    Serial.println("Use 'result' command to end game and see your result.");
    Serial.println();
  }

  index = 0;
  selected_digit = 0;
}

void generateNewSequence(byte level) {
  // clear sequence and entered sequence
  for (byte i = 0; i < 100; i++) {
    sequence[i] = 0;
    entered_sequence[i] = 0;
  }

  // set new sequence
  for (byte i = 0; i < level; i++) sequence[i] = random(1, 7);
}

void showSequence(byte level) {
  // turn off all leds and wait 500ms
  for (byte i = 0; i < 6; i++) digitalWrite(leds_pins[i], LOW);
  delay(500);

  // blink sequence LEDs
  for (byte i = 0; i < level; i++) {
    digitalWrite(leds_pins[sequence[i] - 1], HIGH);
    delay(pot_value);
    digitalWrite(leds_pins[sequence[i] - 1], LOW);
    delay(pot_value / 2);
  }
}

bool isSequenceCorrect(byte level) {
  for (byte i = 0; i < level; i++) {
    if (sequence[i] != entered_sequence[i]) return false;
  }

  return true;
}
