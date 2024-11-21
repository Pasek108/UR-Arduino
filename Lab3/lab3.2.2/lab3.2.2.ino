/*-------------------------------------------------------------------------------

2.2 Based on program 2.1, write and run a program to control an RGB LED through
    serial communication as follows:

    - Pressing the letter g - the green LED lights up.
    - Pressing the letter r - the red LED lights up.
    - Pressing the letter b - the blue LED lights up.
    - Pressing the letter y - the yellow LED lights up.
    - Pressing the letter c - cyan.
    - Pressing the letter m - magenta.
    - Any other key - turns off the LED.

-------------------------------------------------------------------------------*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

char c[1] = {' '};

void setup () {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  Serial.println("START");

  setColor(255, 255, 255);
}

void loop () {
  if (Serial.available()) {
    Serial.readBytesUntil('\n', c, 1);

    switch (c[0]) {
      case 'r': setColor(  0, 255, 255); break;
      case 'g': setColor(255,   0, 255); break;
      case 'b': setColor(255, 255,   0); break;
      case 'y': setColor(  0,   0, 255); break;
      case 'c': setColor(255,   0,   0); break;
      case 'm': setColor(  0, 255,   0); break;
      default:  setColor(255, 255, 255); break;
    }

    Serial.println(c[0]);
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
