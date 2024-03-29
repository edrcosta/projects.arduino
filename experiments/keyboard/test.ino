#include "Adafruit_Keypad.h"

const byte ROWS = 3; // rows
const byte COLS = 10; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','4', '5', '6', '7', '8', '9', '0'},
  {'a','a','a','a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a','a','a','a', 'a', 'a', 'a', 'a', 'a', 'a'},  
};
byte rowPins[ROWS] = {PB5, PD7, PD6 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = {PC0, PC1, PC2, PC3, PC4, PC5, PB1, PB2, PB3, PB4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  customKeypad.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  customKeypad.tick();

  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    Serial.print((char)e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
    else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");
  }

  delay(10);
}