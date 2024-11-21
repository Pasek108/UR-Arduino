/*-------------------------------------------------------------------------------

1.2 Modify the Blink example from the Arduino IDE so that turning the built-in
    LED (D13) on and off occurs at different time intervals

-------------------------------------------------------------------------------*/

#include <time.h>
#include <stdlib.h>

int r;

// the setup function runs once when you press reset or power the board
void setup() {
  srand(time(NULL));
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(rand() % 1000);             // wait for a random time
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(rand() % 1000);             // wait for a random time
}
