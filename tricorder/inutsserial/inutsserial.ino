int sensorPin = A0; // The input port
int sensorValue; // Current reading
int outputValue; // The reported reading
int lastValues[3] = {0,0,0}; // The last 3 readings

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // Initialise variables for checks
  int i;
  int updateOutput = 1;
  // Loop through previous readings
  for( i = 0 ; i<3 ; i++ ){
    // If this historic value doesn't match the current reading,
    // we will not update the output value
    if( lastValues[i] != sensorValue ){
      updateOutput = 0;
    }
    // Shift the array elements to make room for new value
    if( i>0 ){
      lastValues[(i-1)] = lastValues[i];
    }
  }
  // Update if needed
  if( updateOutput == 1 ){
    outputValue = sensorValue;
  }
  // Append the new value
  lastValues[2] = sensorValue;
  // Debugging output
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(outputValue);
}
