/*-------------------------------------------------------------------------------

2.2 Using solutions from previous tasks, create a project that allows controlling 
    LED signaling in the following way (potentiometer range: 0-1000):

    - The red LED will light up when the air temperature (potentiometer setting) 
      is greater than 500 (arbitrary scale), and a single button press will 
      initiate a circuit test process, keeping the LED on for 3 seconds.
    - The green LED will light up when the air temperature (potentiometer 
      setting) is less than 500 (arbitrary scale), and a double button press will 
      activate the LED for 3 seconds.

-------------------------------------------------------------------------------*/

#include <Bounce2.h>

#define RED_LED_PIN 12
#define GREEN_LED_PIN 11
#define BUTTON_PIN 7
#define POTENTIOMETER_PIN 0


Bounce debouncer = Bounce();
unsigned long last_press_time;

void setup () {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5);

  last_press_time = millis() + 3000;
}

void loop () {
  int temperature = map(analogRead(POTENTIOMETER_PIN), 0, 1023, 0, 1000);
  debouncer.update();

  if (debouncer.fell()) {
    unsigned long time_passed = millis() - last_press_time;
    last_press_time = millis();

    if (temperature > 500) {
      digitalWrite(RED_LED_PIN, HIGH);
      delay(3000);
      digitalWrite(RED_LED_PIN, LOW);
    } else if (time_passed < 3000) {
      digitalWrite(GREEN_LED_PIN, HIGH);
      delay(3000);
      digitalWrite(GREEN_LED_PIN, LOW);
    }
  }
}
