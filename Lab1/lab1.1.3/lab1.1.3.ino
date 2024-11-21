/*-------------------------------------------------------------------------------

1.3 Modify the Blink example from the Arduino IDE so that the built-in LED (D13)
    lights up 3 times, then after a 2-second pause, lights up 5 times, and so on

-------------------------------------------------------------------------------*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a 0.5 second
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(500);                      // wait for a 0.5 second
  }

  delay(2000);                       // wait for 2 seconds

  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a 0.5 second
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(500);                      // wait for a 0.5 second
  }

  delay(2000);                       // wait for 2 seconds
}
