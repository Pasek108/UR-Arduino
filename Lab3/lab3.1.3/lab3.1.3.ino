/*-------------------------------------------------------------------------------

1.3 Build an application where the brightness of an LED is controlled by 
    adjusting a potentiometer knob. When the potentiometer knob is turned, the 
    Arduino ADC will read the analog signal and then generate a PWM signal 
    proportional to the analog signal.

-------------------------------------------------------------------------------*/

int ledPin = 10;
int analogPin = A0;
int value = 0;

void setup () {
  pinMode(ledPin, OUTPUT);
}

void loop () {
  value = analogRead(analogPin);
  analogWrite(ledPin, value / 4);

  delay(1);
}
