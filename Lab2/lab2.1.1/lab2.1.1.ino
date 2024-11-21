/*-------------------------------------------------------------------------------

1.1 Run the prepared sketch and analyze its detailed parameters.

-------------------------------------------------------------------------------*/

int diodaPin = 13;
int potPin = 0;
int pot;     // variable to store the potentiometer "value"
int przerwa; // variable to store the blinking speed

void setup () {
  pinMode(diodaPin, OUTPUT);
}

void loop () {
  pot = analogRead(potPin); // read A0 and store the value in the variable "pot"

  /*
    The map() function used below is used to convert one range of numbers
    to another. In our case, it converts numbers from the range 0 to 1023
    (value read from A0) to the range 50 to 3000 (interval between turning
    the LED on and off). The converted range of numbers will be stored in
    the variable "przerwa."
  */

  przerwa = map (pot, 0, 1023, 50, 3000);

  digitalWrite(diodaPin, HIGH);
  delay(przerwa);            // delay dependent on the potentiometer position
  digitalWrite(diodaPin, LOW);
  delay(przerwa);            // delay dependent on the potentiometer position
}
