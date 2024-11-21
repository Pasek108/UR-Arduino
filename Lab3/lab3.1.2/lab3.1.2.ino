/*-------------------------------------------------------------------------------

1.2 Redesign program 1.1 for controlling the RGB LED and write a program such 
    that each successive press of the micro switch changes the LED's color to 
    one of 7 digitally configurable colors (3 primary + 4 mixed - as shown in 
    the diagram below).

-----------------------------------
|        Colour Truth Table       |
|---------------------------------|
|  red  | green | blue  | result  |
|---------------------------------|
|  ON   |  ON   |  OFF  | yellow  |
|  OFF  |  ON   |  ON   | cyan    |
|  ON   |  OFF  |  ON   | magenta |
|  ON   |  ON   |  ON   | white   |
-----------------------------------
 
-------------------------------------------------------------------------------*/

#include <Bounce2.h>

int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int buttonPin = 8;

Bounce debouncer = Bounce();
int count = 0;

void setup () {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
  debouncer.attach(buttonPin);
  debouncer.interval(5);
}

void loop () {
  debouncer.update();

  if (debouncer.fell()) {
    switch (count) {
      case 0: setColor(  0, 255, 255); break;
      case 1: setColor(255,   0, 255); break;
      case 2: setColor(255, 255,   0); break;
      case 3: setColor(  0,   0, 255); break;
      case 4: setColor(255,   0,   0); break;
      case 5: setColor(  0, 255,   0); break;
      case 6: setColor(  0,   0,   0); break;
    }

    count = (count + 1) % 7;
  }

  delay(1);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
