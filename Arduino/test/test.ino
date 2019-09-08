
void setup() {

  pinMode(PB0, OUTPUT);
}
void loop() {
  digitalWrite(PB0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(PB0, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
}
