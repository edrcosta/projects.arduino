void setup() {

    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);

    Serial.begin(9600);    
}

void loop() {

    for (int row = 6; row <= 8; row++)
    {
        digitalWrite(row, HIGH);

        for (int col = 2; col <= 5; col++)
        {     
            if(digitalRead(col) == 0){
                Serial.print("ID:");
                Serial.println(col + row);
            }
            delay(10);
        }

        delay(10);
        digitalWrite(row, LOW);
    }

    delay(50);
}