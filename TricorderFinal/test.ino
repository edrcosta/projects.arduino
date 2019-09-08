#include "U8glib.h"

U8GLIB_SSD1306_128X64_2X u8g(U8G_I2C_OPT_NONE);

#define KEY_NONE 0
#define KEY_PREV A2
#define KEY_NEXT A1
#define KEY_SELECT A3
#define KEY_BACK 2

uint8_t pinKeyPrev = A2;
uint8_t pinKeyNext = A1;
uint8_t pinKeySelect = A3;
uint8_t pinKeyBack = 2;

uint8_t keyCode = KEY_NONE;
uint8_t keyCode2 = KEY_NONE;
uint8_t uiKeyCode = KEY_NONE;

uint8_t screenUpdate = 1;

void setupInputs(void) {
    pinMode(pinKeyPrev, INPUT_PULLUP);
    pinMode(pinKeyNext, INPUT_PULLUP);
    pinMode(pinKeySelect, INPUT_PULLUP);
    pinMode(pinKeyBack, INPUT_PULLUP);
}

void detectKey(void) {


    screenUpdate = 1;
}

void renderLoop(void) {
    u8g.setFont(u8g_font_unifont);
    u8g.setPrintPos(0, 20); 
    u8g.print(String(keyCode));    
}

void setup() {
    setupInputs();
}

void loop() {  

    detectKey();

    if (screenUpdate != 0) {
        u8g.firstPage();
        do  { renderLoop();} while(u8g.nextPage() );
        screenUpdate = 0;
    }
}