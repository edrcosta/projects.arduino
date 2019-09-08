
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 20); 
  // call procedure from base class, http://arduino.cc/en/Serial/Print
  u8g.print("Hello World!");
  
}

void setup(void) {
  
}

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(500);
}
