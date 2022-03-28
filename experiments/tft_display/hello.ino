#include <TFT.h>  
#include <SPI.h>

#define reset 8
#define cs 10
#define dc 9

TFT TFTscreen = TFT(cs, dc, reset);
 
void setup() {
  TFTscreen.begin();
  TFTscreen.setTextSize(2);
  TFTscreen.background(0, 0, 0);
}
 
void loop() {
  TFTscreen.stroke(random(0, 255), random (0, 255), random (0, 255));
  TFTscreen.text("Hello World", 5, 50);
  delay(100);
}