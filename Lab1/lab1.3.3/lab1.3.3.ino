/*-------------------------------------------------------------------------------

3.3 Propose a program that simulates a running light in one direction three 
    times, then changes direction, and so on.

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
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(blue - j, HIGH);
      delay(250);
      digitalWrite(blue - j, LOW);
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(red + j, HIGH);
      delay(250);
      digitalWrite(red + j, LOW);
    }
  }

  delay(2000);
}
