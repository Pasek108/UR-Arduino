/*-------------------------------------------------------------------------------

1.1 Write and run the following sketch to control an RGB LED.

To display red light on the RGB LED, call the setColor(...) function and set the 
value of the redValue argument to 255, while the other two parameters are set 
to 0. Similarly, follow this approach for the other two primary colors: green 
and blue.

To create other colors, combine the argument values. For example:

Setting all three LEDs to maximum brightness will produce white.
Setting the following values: redValue = 170, greenValue = 0, blueValue = 255 
will produce purple.

-----------

int redPin = ?;
int greenPin = ?; // ? - adjust to the circuit
int bluePin = ?;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  setColor(255, 0, 0); // Red Color
  delay(1000);
  setColor(0, 255, 0); // Green Color
  delay(1000);
  setColor(0, 0, 255); // Blue Color
  delay(1000);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

-------------------------------------------------------------------------------*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup () {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop () {
  setColor(0, 255, 255); // Red Color
  delay(1000);
  setColor(255, 0, 255); // Green Color
  delay(1000);
  setColor(255, 255, 0); // Blue Color
  delay(1000);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
