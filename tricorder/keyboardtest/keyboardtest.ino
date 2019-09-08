int counter = 0;
int status = 0;

void setup() {
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);

    Serial.begin(9600);    
}


void validateCol(int row){

    digitalWrite(row, HIGH);
    if(digitalRead(2) == HIGH){
        Serial.println("row:");
        Serial.print(row);
        Serial.println("Btn 2 pressionado");
    }
    
    if(digitalRead(3) == HIGH){
        Serial.println("row:");
        Serial.print(row);
        Serial.println("Btn 3 pressionado");
    }

    if(digitalRead(4) == HIGH){
        Serial.println("row:");
        Serial.print(row);
        Serial.println("Btn 4 pressionado");
    }

    if(digitalRead(5) == HIGH){
        Serial.println("row:");
        Serial.print(row);
        Serial.println("Btn 5 pressionado");
    }
    digitalWrite(row, LOW);
}


void loop() {
    validateCol(6);
    delay(1000);
}
