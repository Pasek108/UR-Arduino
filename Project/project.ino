/*-------------------------------------------------------------------------------

Project

Using the program skeleton below, propose your own concept for a great project 
using the learned electronic components.

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

/*-------------------------------------------------------------------------------

How to play

Your task is to defuse the bomb before it explodes.

1. Start the game using the 'init' command. You will receive an RGB code (values)
   needed to access the bomb.

2. Gain access to the bomb by setting the RGB color values:  
   - Use the potentiometers to set the color values (left: R, middle: G, 
     right: B).  
   - The margin of error is approximately 3.9% (values between 0 and 255, ±10).  
   - Check if the RGB code is correct using the 'send' command.  
   - The first mistake starts a 1m 30s timer; subsequent mistakes reduce the 
     timer by 30s each.

3. Defuse the bomb using the password before it explodes (if the timer is 
   running):  
   - Obtain the password using the 'data' command.  
   - Remember the password displayed as LEDs blinking in a specific order.  
   - A new password is generated each time.  
   - You will have ONLY ONE attempt.  
   - Input the password by selecting LEDs in the correct order:  
     - Use the 'next' button to select an LED.  
     - Use the 'confirm' button to accept.  
   - If you are confident the password is correct, defuse the bomb with the 
     'result' command.

4. The game ends when:  
   - You win:  
     - All LEDs turn on.  
     - The RGB LED turns green.  
   - You lose (either due to an incorrect password or the timer expiring):  
     - The LEDs will blink.  
     - The RGB LED turns red.

5. To start a new game, return to step 1 and use the 'init' command.

-------------------------------------------------------------------------------*/

#include <Bounce2.h>

/* ---------------- BOARD ELEMENTS ---------------- */

// Potentiometers for RGB LED
#define POTENTIOMETER_R_PIN A0
#define POTENTIOMETER_G_PIN A1
#define POTENTIOMETER_B_PIN A2

byte potentiometers_pins[3] = {
  POTENTIOMETER_R_PIN,
  POTENTIOMETER_G_PIN,
  POTENTIOMETER_B_PIN
};

// RGB LED
#define RGB_LED_R_PIN 11
#define RGB_LED_G_PIN 10
#define RGB_LED_B_PIN 9

byte rgb_led_pins[3] = {
  RGB_LED_R_PIN,
  RGB_LED_G_PIN,
  RGB_LED_B_PIN
};

// Timer LEDs
#define TIMER_LED_1_PIN 3
#define TIMER_LED_2_PIN 5
#define TIMER_LED_3_PIN 6

byte timer_leds_pins[3] = {
  TIMER_LED_1_PIN,
  TIMER_LED_2_PIN,
  TIMER_LED_3_PIN
};

// Password LEDs
#define PASSWORD_LED_1_PIN 13
#define PASSWORD_LED_2_PIN 12
#define PASSWORD_LED_3_PIN 8
#define PASSWORD_LED_4_PIN 7
#define PASSWORD_LED_5_PIN 4
#define PASSWORD_LED_6_PIN 2

byte password_leds_pins[6] = {
  PASSWORD_LED_1_PIN,
  PASSWORD_LED_2_PIN,
  PASSWORD_LED_3_PIN,
  PASSWORD_LED_4_PIN,
  PASSWORD_LED_5_PIN,
  PASSWORD_LED_6_PIN
};

// Next and confirm buttons
#define NEXT_BUTTON_PIN    A5
#define CONFIRM_BUTTON_PIN A4

Bounce2::Button next_button    = Bounce2::Button();
Bounce2::Button confirm_button = Bounce2::Button();


/* ---------------- FUNCTIONS ---------------- */

void initialize();   // initialize game and generate RGB access code
void send_message(); // check set RGB values and continue or punish the player (timer)
void get_data();     // generate new password and display it
void show_result();  // check if the password is correct

void generateRGBCode();  // generate RGB access codecand disply it
bool isRGBCodeCorrect(); // check if entered RGB access code is correct (+- 10)

void generatePassword();  // generate password (random order of 10 leds)
void showPassword();      // turn on password leds in correct order
bool isPasswordCorrect(); // check if entered password is correct

void showTimer(long timer_left); // set timer LEDs brightness by timer value
void gameLost(byte reason);      // turn on all leds, set RGB led red, print loss message
void gameWon();                  // turn off all leds, set RGB led green, print win message


/* ---------------- GLOBAL VARIABLES ---------------- */

// Game varaibles
String command;
bool game_over = false;

byte rgb_code[3];
bool rgb_code_correct = false;

byte password[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte entered_password[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte password_index = 0;
byte selected_digit = 0;
bool password_too_long = false;

long timer_started = 0;
long timer_limit = 90000; // 01:30


/* ---------------- MAIN FUNCTIONS ---------------- */

void setup () {
  randomSeed(analogRead(A3));

  while (!Serial);
  Serial.begin(9600);
  Serial.println("Your task is to defuse the bomb (use 'init' to start).");
  Serial.println("");

  // set pins
  for (byte i = 0; i < 3; i++) pinMode(potentiometers_pins[i], INPUT);
  for (byte i = 0; i < 3; i++) pinMode(rgb_led_pins[i], OUTPUT);
  for (byte i = 0; i < 3; i++) pinMode(timer_leds_pins[i], OUTPUT);
  for (byte i = 0; i < 6; i++) pinMode(password_leds_pins[i], OUTPUT);

  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
  next_button.attach(NEXT_BUTTON_PIN);
  next_button.interval(5);

  pinMode(CONFIRM_BUTTON_PIN, INPUT_PULLUP);
  confirm_button.attach(CONFIRM_BUTTON_PIN);
  confirm_button.interval(5);
}

void loop () {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    Serial.print("Command: '");
    Serial.print(command);
    Serial.println("'");

    if (command == "init") initialize();
    else if (command == "send") send_message();
    else if (command == "data") get_data();
    else if (command == "result") show_result();
    else Serial.println("Invalid command");
  }

  if (!game_over && !rgb_code_correct) {
    for (byte i = 0; i < 3; i++) {
      int value = map(analogRead(potentiometers_pins[i]), 0, 1023, 0, 255);
      analogWrite(rgb_led_pins[i], 255 - value);
    }
  }

  if (!game_over && rgb_code_correct) {
    next_button.update();
    confirm_button.update();

    if (confirm_button.pressed()) {
      if (selected_digit > 0 && password_index >= 10) password_too_long = true;
      else entered_password[password_index++] = selected_digit;

      digitalWrite(password_leds_pins[selected_digit - 1], LOW);
      selected_digit = 0;
    }

    if (next_button.pressed()) {
      for (byte i = 0; i < 6; i++) pinMode(password_leds_pins[i], OUTPUT);

      if (selected_digit > 0) digitalWrite(password_leds_pins[selected_digit - 1], LOW);
      selected_digit = (selected_digit + 1) % 7;
      if (selected_digit > 0) digitalWrite(password_leds_pins[selected_digit - 1], HIGH);
    }
  }

  if (!game_over && timer_started) {
    long timer = (long)millis() - (long)timer_started;
    long timer_left = timer_limit - timer;

    if (timer_left > 0) showTimer(timer_left);
    else gameLost(1);
  }

  delay(1);
}


/* ---------------- GAME FUNCTIONS ---------------- */

void initialize() {
  for (byte i = 0; i < 10; i++) {
    password[i] = 0;
    entered_password[i] = 0;
  }

  game_over = false;
  rgb_code_correct = false;

  password_index = 0;
  selected_digit = 0;
  password_too_long = false;

  timer_started = 0;
  timer_limit = 90000;

  // turn off all LEDs
  for (byte i = 0; i < 3; i++) analogWrite(rgb_led_pins[i], 255);
  for (byte i = 0; i < 3; i++) digitalWrite(timer_leds_pins[i], LOW);
  for (byte i = 0; i < 6; i++) digitalWrite(password_leds_pins[i], LOW);

  // create new RGB code
  generateRGBCode();
}

void send_message() {
  if (game_over) return;
  rgb_code_correct = isRGBCodeCorrect();

  if (!rgb_code_correct) {
    // first mistake starts timer, next ones takes 30s
    if (timer_started == 0) {
      timer_started = (long)millis();
      Serial.println("Wrong code. Timer activated.");
      Serial.println("");
    } else {
      timer_limit -= 30000; // -00:30
      Serial.println("Wrong code. Timer reduced.");
      Serial.println("");
    }
  } else {
    Serial.println("Access granted. Get password using 'data' command.");
    Serial.println("");
  }
}

void get_data() {
  if (game_over) return;
  if (!rgb_code_correct) return;

  generatePassword();

  Serial.println("Displaying password.");
  Serial.println("");
  delay(500);

  showPassword();

  Serial.println("Input password using left button to select led and right to confirm.");
  Serial.println("If you are sure the password is correct use 'result' command.");
  Serial.println("If not, use 'data' command again to generate new password.");
  Serial.println("");
}

void show_result() {
  if (game_over) return;

  // bomb not unlocked
  if (!rgb_code_correct) {
    gameLost(0);
    return;
  }

  // bad password length or wrong password
  if (password_too_long || password_index < 10 || !isPasswordCorrect()) {
    gameLost(2);
    return;
  }

  gameWon();
}

/* ---------------- HELPER FUNCTIONS ---------------- */

void generateRGBCode() {
  for (byte i = 0; i < 3; i++) rgb_code[i] = random(256);

  Serial.print("The code for unlocking the bomb is: ");
  Serial.print(rgb_code[0]); Serial.print(", ");
  Serial.print(rgb_code[1]); Serial.print(", ");
  Serial.print(rgb_code[2]); Serial.println("");
  Serial.println("Set values using potentiometers and use 'send' command to confirm.");
}

bool isRGBCodeCorrect() {
  for (byte i = 0; i < 3; i++) {
    byte value = map(analogRead(potentiometers_pins[i]), 0, 1023, 0, 255);
    if (abs(rgb_code[i] - value) > 10) return false;
  }

  return true;
}

void generatePassword() {
  for (byte i = 0; i < 10; i++) password[i] = random(1, 7);
}

void showPassword() {
  for (byte i = 0; i < 6; i++) digitalWrite(password_leds_pins[i], LOW);

  for (byte i = 0; i < 10; i++) {
    digitalWrite(password_leds_pins[password[i] - 1], HIGH);
    delay(500);
    digitalWrite(password_leds_pins[password[i] - 1], LOW);
    delay(500);
  }
}

bool isPasswordCorrect() {
  for (byte i = 0; i < 10; i++) {
    if (password[i] != entered_password[i]) return false;
  }

  return true;
}

void showTimer(long timer_left) {
  if (timer_left > 60000) {
    int value = map(timer_left - 60000, 0, 30000, 0, 255);
    analogWrite(timer_leds_pins[0], value);
    analogWrite(timer_leds_pins[1], 255);
    analogWrite(timer_leds_pins[2], 255);
  }
  else if (timer_left > 30000) {
    int value = map(timer_left - 30000, 0, 30000, 0, 255);
    analogWrite(timer_leds_pins[1], value);
    analogWrite(timer_leds_pins[0], 0);
    analogWrite(timer_leds_pins[2], 255);
  }
  else {
    int value = map(timer_left, 0, 30000, 0, 255);
    analogWrite(timer_leds_pins[2], value);
    analogWrite(timer_leds_pins[0], 0);
    analogWrite(timer_leds_pins[1], 0);
  }
}

void gameLost(byte reason) {
  game_over = true;

  // turn on all LEDs
  for (byte i = 0; i < 3; i++) digitalWrite(timer_leds_pins[i], HIGH);
  for (byte i = 0; i < 6; i++) digitalWrite(password_leds_pins[i], HIGH);

  // set RGB led red
  analogWrite(rgb_led_pins[0], 0);
  analogWrite(rgb_led_pins[1], 255);
  analogWrite(rgb_led_pins[2], 255);

  Serial.print("You failed. ");
  switch (reason) {
    case 0: Serial.println("You didn't have access."); break;
    case 1: Serial.println("You didn't make it in time."); break;
    case 2: Serial.println("The password was incorrect."); break;
  }
  Serial.println("");
}

void gameWon() {
  game_over = true;

  // turn off all LEDs
  for (byte i = 0; i < 3; i++) digitalWrite(timer_leds_pins[i], LOW);
  for (byte i = 0; i < 6; i++) digitalWrite(password_leds_pins[i], LOW);

  // set RGB led green
  analogWrite(rgb_led_pins[0], 255);
  analogWrite(rgb_led_pins[1], 0);
  analogWrite(rgb_led_pins[2], 255);

  Serial.println("You defused the bomb successfully.");
  Serial.println("");
}
