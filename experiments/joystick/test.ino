/* Pins */
#define JOYSTICK_INPUT_X A1
#define JOYSTICK_INPUT_Y A0
#define JOYSTICK_INPUT_BUTTON A2

/* Joystick information */
int JOYSTICK_X = 0 ;
int JOYSTICK_Y = 0 ; 
int JOYSTICK_BUTTON = 0 ;
int JOYSTICK_PREVIOUS_X = 0;
int JOYSTICK_PREVIOUS_Y = 0;
int JOYSTICK_DIRECTION_HAS_CHANGED = 1;

void setup()  
{ 
    Serial.begin(9600);

    pinMode(JOYSTICK_INPUT_BUTTON, INPUT_PULLUP);
} 

void joystick_get_status(){
    JOYSTICK_X = analogRead(JOYSTICK_INPUT_X);  
    JOYSTICK_Y = analogRead(JOYSTICK_INPUT_Y);  
    JOYSTICK_BUTTON = digitalRead(A2);

    if(JOYSTICK_DIRECTION_HAS_CHANGED == 1){
        JOYSTICK_PREVIOUS_X = JOYSTICK_X;
        JOYSTICK_PREVIOUS_Y = JOYSTICK_Y;
        JOYSTICK_DIRECTION_HAS_CHANGED = 0;
    }

    if(JOYSTICK_X > JOYSTICK_PREVIOUS_X){
        if (JOYSTICK_X - JOYSTICK_PREVIOUS_X > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }else{
        if (JOYSTICK_PREVIOUS_X - JOYSTICK_X > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }

    if(JOYSTICK_Y > JOYSTICK_PREVIOUS_Y){
        if (JOYSTICK_Y - JOYSTICK_PREVIOUS_Y > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }else{
        if (JOYSTICK_PREVIOUS_Y - JOYSTICK_Y > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }
}

void loop() 
{ 
    joystick_get_status();

    if(JOYSTICK_DIRECTION_HAS_CHANGED){
        /*Joystick STATUS*/
        Serial.print(" X:");
        Serial.print(JOYSTICK_X, DEC);
        Serial.print(" Y:");
        Serial.print(JOYSTICK_Y, DEC);  
       
        Serial.print("\n");
        JOYSTICK_DIRECTION_HAS_CHANGED = 0;
    }

    if(JOYSTICK_BUTTON == 0){
        Serial.print(" B:");
        Serial.println(JOYSTICK_BUTTON);
        Serial.print("\n");
    }
    

    delay(10);
}