/*-------------------------------------------------------------------------------

2.2 Modify task 2.1, choose a free pin and connect a second LED (green) to it.
    Write a program that makes:

    - the red LED light up 3 times, followed by the green LED lighting up 3 times
    - after a 2-second pause, the red LED lights up 2 times, followed by the green
      LED lighting up 2 times.
    - after another 2-second pause, the red LED lights up 1 time, followed by the
      green LED lighting up 1 time.
    - then the sequence repeats from the beginning.

-------------------------------------------------------------------------------*/

int red = 9;
int green = 10;

void setup () {
  pinMode(red, OUTPUT);
  pinMode (green, OUTPUT) ;
}

void loop() {
  for (int i = 3; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      digitalWrite(red, HIGH);
      delay(400);
      digitalWrite(red, LOW);
      delay(400);
    }

    for (int j = 0; j < i; j++) {
      digitalWrite(green, HIGH);
      delay(400);
      digitalWrite(green, LOW);
      delay(400);
    }

    delay(2000);
  }
}
