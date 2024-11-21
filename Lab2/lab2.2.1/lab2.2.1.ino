/*-------------------------------------------------------------------------------

2.1 Modify the program so that the LED turns on after a start signal, which is 
    pressing the button, and turns off after pressing the button again, and so 
    on (a general example below for further development). Use the Bounce library 
    for proper handling of the micro switch. 

#include <Bounce2.h>

#define BUTTON PIN 2
#define LED PIN 13

// Inicjalizacja obiektu Bounce
Bounce debouncer = Bounce();

void setup () {
  // Konfiguracja pinu przycisku
  // i aktywowanie rezystora podciągającego:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // ustawienie działania funkcji Bounce
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5); // interwał w ms

  //Konfiguracja pinu diody LED
  pinMode(LED_PIN, OUTPUT);
}

void loop () {
  // Aktualizacja funkcji Bounce
  debouncer.update();

  // Odczyt zaktualizowanej wartości (value)
  int value = debouncer.read();

  // W zależności od stanu włączenie lub wyłączenie diody LED
  if ( ) {

  else {
    
  }
}

-------------------------------------------------------------------------------*/

#include <Bounce2.h>

#define BUTTON_PIN 7
#define LED_PIN 8

// Initialize the Bounce object
Bounce debouncer = Bounce();
bool state = 0;
bool pressed = 0;

void setup() {
  // Configure the button pin and enable the pull-up resistor:
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Set up the Bounce functionality
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5); // interval in ms

  // Configure the LED pin
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Update the Bounce functionality
  debouncer.update();

  // Read the updated value
  int value = debouncer.read();

  // Depending on the state, turn the LED on or off
  if (value == LOW && pressed == 0) {
    pressed = 1;
  }

  if (value == HIGH && pressed == 1) {
    pressed = 0;
    state = !state;
  }

  digitalWrite(8, state);
}
