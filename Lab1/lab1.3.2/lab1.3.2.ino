/*-------------------------------------------------------------------------------

3.2 Using program 3.1 divide the LEDs into pairs by adding a fourth one, then 
	write a program that will make each pair blink twice with a set frequency 
	and duty cycle.  

-------------------------------------------------------------------------------*/

int red = 9;
int yellow = 10;
int green = 11;
int blue = 12;

void setup () {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT) ;
  pinMode(green, OUTPUT) ;
  pinMode(blue, OUTPUT) ;

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}

void loop() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(green, HIGH);
    digitalWrite(red, HIGH);
    delay(500);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    delay(500);
  }

  for (int i = 0; i < 2; i++) {
    digitalWrite(blue, HIGH);
    digitalWrite(yellow, HIGH);
    delay(500);
    digitalWrite(blue, LOW);
    digitalWrite(yellow, LOW);
    delay(500);
  }

  delay(2000);
}
