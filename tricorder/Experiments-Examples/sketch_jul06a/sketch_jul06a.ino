int outputs[] = {2, 3, 4, 5};
int inputs[] = {14, 15, 16};

void setup() {

    Serial.begin(9600);
    
    pinMode(18, INPUT);
    // for (int i = 0; i < sizeof(inputs); i++){
    //     pinMode(inputs[i], INPUT);
    // }

    // for (int i = 0; i < sizeof(outputs); i++){
    //     pinMode(outputs[i], INPUT);
    // }
}


void loop() {
    

    digitalWrite(2, HIGH);

    if(digitalRead(18)){
        Serial.println("BOTAO RESSIONADO");
    }

    delay(10);
} 
