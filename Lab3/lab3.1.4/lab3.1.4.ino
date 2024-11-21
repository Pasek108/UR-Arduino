/*-------------------------------------------------------------------------------

1.4 Modify program 1.3 and write the following program: if the button is not 
    pressed, the PWM duty cycle will increase by 5 units, but if the button is 
    pressed, the PWM will increase by 10 units (twice as fast). Observe the 
    effect using an LED.

-------------------------------------------------------------------------------*/

#include <Bounce2.h>

int ledPin = 10;
int buttonPin = 9;

Bounce debouncer = Bounce();
int value = 0;

void setup () {
  pinMode(ledPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  debouncer.attach(buttonPin);
  debouncer.interval(5);
}

void loop () {
  debouncer.update();

  value += (debouncer.read() == HIGH) ? 5 : 10;
  if (value > 15000) value = 0;

  analogWrite(ledPin, map(value, 0, 15000, 0, 255));

  delay(1);
}
