// Rotary Encoder Inputs
#define ROTARY_ENCODERT_CLK_INPUT 2
#define ROTARY_ENCODERT_DT 3
#define ROTARY_ENCODERT_SW 4

// rotary encoder states
int ROTARY_COUNTER = 0;
int ROTARY_ENCODER_CURRENT_STATE_CLK;
int ROTARY_ENCODER_LAST_STATE_CLK;
int ROTARY_ENCODER_HAS_CHANGED = 0;
String ROTARY_ENCODER_DIRECTION ="";
unsigned long ROTARY_ENCODER_BUTTON_LAST_STATE = 0;

void setup() {
  pinMode(ROTARY_ENCODERT_CLK_INPUT,INPUT);
  pinMode(ROTARY_ENCODERT_DT,INPUT);
  pinMode(ROTARY_ENCODERT_SW, INPUT_PULLUP);

  Serial.begin(9600);

  ROTARY_ENCODER_LAST_STATE_CLK = digitalRead(ROTARY_ENCODERT_CLK_INPUT);
}

/*
  Check rotary encoder current state
*/
void rotary_encoder_get_status(){
  ROTARY_ENCODER_CURRENT_STATE_CLK = digitalRead(ROTARY_ENCODERT_CLK_INPUT);

  // CHECK IF STATE CHANGE 
  if (ROTARY_ENCODER_CURRENT_STATE_CLK != ROTARY_ENCODER_LAST_STATE_CLK  && ROTARY_ENCODER_CURRENT_STATE_CLK == 1){    
    if (digitalRead(ROTARY_ENCODERT_DT) != ROTARY_ENCODER_CURRENT_STATE_CLK) {
      // DECREMENT
      ROTARY_COUNTER --;
      ROTARY_ENCODER_DIRECTION ="DEC";
    } else {
      // INCREMENT
      ROTARY_COUNTER ++;
      ROTARY_ENCODER_DIRECTION ="INC";
    }
    ROTARY_ENCODER_HAS_CHANGED = 1;
  }

  // STORE STATE
  ROTARY_ENCODER_LAST_STATE_CLK = ROTARY_ENCODER_CURRENT_STATE_CLK;

  // ROTARY ENCODER BUTTON CHECK
  if (digitalRead(ROTARY_ENCODERT_SW) == LOW) {
    if (millis() - ROTARY_ENCODER_BUTTON_LAST_STATE > 50) {
      Serial.println("Button pressed!");
    }
    ROTARY_ENCODER_BUTTON_LAST_STATE = millis();
  }
}

void loop() {
  rotary_encoder_get_status();
  
  // DEBUG ENCODER
  if(ROTARY_ENCODER_HAS_CHANGED == 1){
    Serial.print("Direction: ");
    Serial.print(ROTARY_ENCODER_DIRECTION);
    Serial.print(" | ROTARY_COUNTER: ");
    Serial.println(ROTARY_COUNTER);
    ROTARY_ENCODER_HAS_CHANGED = 0;
  }
  delay(1);
}