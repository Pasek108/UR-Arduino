/*-------------------------------------------------------------------------------

3.1 Write a program that sorts LEDs based on their brightness. In an 
    eight-element array, assign random values to each cell. The index of the 
    cell in the array will correspond to the number of the LED. Then implement 
    a sorting algorithm of your choice (e.g., bubble sort) and demonstrate its 
    operation using LEDs.

The randomSeed() function initializes the pseudorandom number generator.
e.g. 
    randomSeed(analogRead(0));

The random() function generates a pseudorandom number within the specified range
e.g. 
    random(x);       // range 0 to (x-1)
    random(a, b);    // range a to (b-1)

-------------------------------------------------------------------------------*/

const byte LED_PINS[6] = {11, 10, 9, 6, 5, 3};
byte LED_BRIGHTNESS[6] = { 0,  0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  for (int i = 0; i < 6; i++) pinMode(LED_PINS[i], OUTPUT);
}

void loop() {
  randomizeBrightnes();
  delay(2000);
  sortBrightnes();
}

void randomizeBrightnes() {
  for (int i = 0; i < 6; i++) {
    LED_BRIGHTNESS[i] = random(256);
    analogWrite(LED_PINS[i], LED_BRIGHTNESS[i]);
  }
}

void sortBrightnes() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6 - i - 1; j++) {
      if (LED_BRIGHTNESS[j] > LED_BRIGHTNESS[j + 1]) {
        byte temp = LED_BRIGHTNESS[j];
        LED_BRIGHTNESS[j] = LED_BRIGHTNESS[j + 1];
        LED_BRIGHTNESS[j + 1] = temp;

        analogWrite(LED_PINS[j], LED_BRIGHTNESS[j]);
        analogWrite(LED_PINS[j + 1], LED_BRIGHTNESS[j + 1]);
        delay(500);
      }
    }
  }
}
