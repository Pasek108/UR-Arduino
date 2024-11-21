/*-------------------------------------------------------------------------------

1.2 Propose a modification to program 1.1 so that the position of the 
    potentiometer can be determined using three LEDs. Use three LEDs to 
    visualize the voltage value of the analog input. 
    
    The LEDs should indicate three states of the potentiometer position:
    - 0% to 33%,
    - 34% to 66%,
    - 67% to 100%.

-------------------------------------------------------------------------------*/

int green = 12;
int yellow = 11;
int red = 10;

int potPin = 0;

void setup () {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop () {
  int pot = map(analogRead(potPin), 0, 1023, 0, 100);

  if (pot >= 0 && pot <= 33) {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  } else if (pot >= 34 && pot <= 66) {
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
  } else if (pot >= 67 && pot <= 100) {
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }

  delay(1);
}
