/*-------------------------------------------------------------------------------

3.1 Prepare the circuit from task_circuit.png to simulate the operation of real 
    traffic lights

-------------------------------------------------------------------------------*/

int red = 9;
int yellow = 10;
int green = 11;

void setup () {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT) ;
  pinMode(green, OUTPUT) ;

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}

void loop() {
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  delay(2000);

  digitalWrite(yellow, HIGH);
  digitalWrite(green, LOW);
  delay(2000);

  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  delay(2000);
}
