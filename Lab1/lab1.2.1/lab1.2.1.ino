/*-------------------------------------------------------------------------------

2.1 Modify the program so that, in correlation with the built-in LED in the 
    system, the LEDs alternate their lighting

int red = 9;
int green = 10;

void setup () {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop () {

  .............
}

-------------------------------------------------------------------------------*/

int red = LED_BUILTIN;
int green = 10;

void setup () {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT) ;
}

void loop() { 
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  delay(500); 
  
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  delay(500);  
}
