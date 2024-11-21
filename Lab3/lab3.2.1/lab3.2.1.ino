/*-------------------------------------------------------------------------------

2.1 Run the following sketch to control an LED through serial communication.

char c = ' ';
byte LED = 2;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '0') { digitalWrite(LED, LOW); }
    if (c == '1') { digitalWrite(LED, HIGH); }
    Serial.println(c);
  }
}

-------------------------------------------------------------------------------*/

char c = ' ';
byte LED = 2;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '0') { digitalWrite(LED, LOW); }
    if (c == '1') { digitalWrite(LED, HIGH); }
    Serial.println(c);
  }
}
