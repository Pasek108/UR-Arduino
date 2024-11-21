/*-------------------------------------------------------------------------------

1.3 Build and program a 4-bit counter, where the value is displayed on four LEDs
    placed on a breadboard. The counter should operate in the program’s main loop
    and count numbers from 0 to 15. The counting speed should be adjustable using
    the potentiometer.

  The task requires the conversion of a variable of type byte (integer variable)
  into an appropriate binary number. In the Arduino system’s C language, byte
  variables are stored as 8-bit binary numbers.

-------------------------------------------------------------------------------*/

int leds[4] = {9, 10, 11, 12};
int potPin = 0;

int num = 0;
int mask = 1;

void setup () {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop () {
  int wait = map(analogRead(potPin), 0, 1023, 50, 3000);
  delay(wait);

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], num & mask);
    mask <<= 1;
  }

  mask = 1;
  if (++num > 15) num = 0;
}
