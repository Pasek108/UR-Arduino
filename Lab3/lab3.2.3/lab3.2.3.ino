/*-------------------------------------------------------------------------------

2.3 After starting the program, turn the potentiometer to a random position 
    (within a known range) and press the button. Arduino should then display the 
    following message on the PC console:

    "Enter a number:"

    If the number sent to the Arduino matches the ADC reading with an accuracy 
    of +/- 10%, the player wins, and the green LED lights up. Otherwise, the blue 
    LED turns on, and the player has 2 more attempts. If the player enters the 
    wrong number on all attempts and the round ends, the red LED lights up. If 
    the player guesses correctly, all LEDs blink.

-------------------------------------------------------------------------------*/

#define green_led_pin 10
#define blue_led_pin 9
#define red_led_pin 8
#define pot_pin 8

String command;
int pot_value = 0;
int tries_counter = 3;

void setup() {
  while (!Serial);
  Serial.begin(9600);
  Serial.println("Use 'init' command to start.");

  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(pot_pin, INPUT);
}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');

    if (command.equals("init")) initialize();
    else if (command.toInt() > 0) checkAnswer((int)command.toInt());
    else Serial.println("Invalid");
  }
}

void initialize() {
  tries_counter = 3;

  digitalWrite(green_led_pin, LOW);
  digitalWrite(blue_led_pin, LOW);
  digitalWrite(red_led_pin, LOW);

  pot_value = map(analogRead(pot_pin), 0, 1023, 1, 1000);
  Serial.println("Podaj liczbę (1-1000):");
}

void checkAnswer(int number) {
  if (tries_counter <= 0) return;

  Serial.println(number);

  if (abs(pot_value - number) < 100) {
    digitalWrite(green_led_pin, HIGH);
    delay(1000);

    for (int i = 0; i < 6; i++) {
      digitalWrite(green_led_pin, HIGH);
      digitalWrite(blue_led_pin, HIGH);
      digitalWrite(red_led_pin, HIGH);
      delay(500);
      digitalWrite(green_led_pin, LOW);
      digitalWrite(blue_led_pin, LOW);
      digitalWrite(red_led_pin, LOW);
      delay(500);
    }
  } else {
    tries_counter--;

    if (tries_counter > 0) {
      digitalWrite(blue_led_pin, HIGH);
      delay(1500);
      digitalWrite(blue_led_pin, LOW);
    } else {
      digitalWrite(red_led_pin, HIGH);
    }
  }
}
