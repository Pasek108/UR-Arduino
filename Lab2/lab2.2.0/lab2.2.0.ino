/*-------------------------------------------------------------------------------

2.0 Run and test example program 

-------------------------------------------------------------------------------*/

void setup () {
  pinMode(8, OUTPUT);       // LED as output
  pinMode(7, INPUT_PULLUP); // Button as input
  digitalWrite(8, LOW);     // Turn off the LED
}

void loop () {
  if (digitalRead(7) == LOW) {  // If the button is pressed
    digitalWrite (8, HIGH);     // Turn on the LED
  } else {                      // If the button is not pressed
    digitalWrite(8, LOW);       // Turn off the LED
  }
}
