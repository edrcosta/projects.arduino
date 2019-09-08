int analogPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int lightLevel = analogRead(analogPin);
    Serial.println(lightLevel);
delay(500);
}
