/*
  Huge map Arduboy demo.

  author: Miloslav Ciz
  license: CC0 1.0
*/

#include <Arduboy2.h>
#include "map.h"

Arduboy2 arduboy;

const unsigned char PROGMEM tiles[] =
{
  16, 16,
  0xff, 0xff, 0xff, 0xbf, 0xdf, 0xbf, 0xdf, 0xef, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0x7f, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf7, 0xeb, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xdf, 0xef, 0xdf, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 
  0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfd, 0xfd, 0xbb, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xf7, 0xeb, 0xf7, 0xff, 0xff, 0xff, 0xf9, 0xf3, 0xf9, 0xbf, 0x5f, 0xbf, 0xef, 0xf7, 
  0xbf, 0xdf, 0xfc, 0xf9, 0xe7, 0xf3, 0xf9, 0xff, 0xef, 0xf7, 0xff, 0xff, 0xd7, 0xeb, 0xff, 0xff, 
  0x8b, 0x77, 0x7f, 0xf5, 0xea, 0x75, 0x2a, 0x15, 0xa1, 0x46, 0xaf, 0x4e, 0xa7, 0x52, 0xa9, 0x5f, 
  0xfe, 0xc5, 0x9a, 0x3c, 0xba, 0x3c, 0x9a, 0xc5, 0xfa, 0xc1, 0x4e, 0x9f, 0x5e, 0x9f, 0x4e, 0xe1, 
  0x8b, 0x77, 0x7f, 0xf5, 0xea, 0x75, 0x2a, 0x15, 0xab, 0x5f, 0xb9, 0x53, 0xbf, 0x53, 0xb9, 0x5f, 
  0xfe, 0xcd, 0x9a, 0xf4, 0x9a, 0xc4, 0xfa, 0xd5, 0xea, 0xc1, 0x4e, 0x9f, 0x5e, 0x9f, 0x4e, 0xe1, 
  0x3f, 0x5f, 0xaf, 0x53, 0xad, 0x5d, 0xae, 0xfe, 0xfe, 0x5e, 0xae, 0xfe, 0xfd, 0xfb, 0xf7, 0x0f, 
  0xf0, 0xe1, 0xe2, 0xc5, 0xca, 0x85, 0x8b, 0x97, 0x8a, 0xc5, 0xe3, 0xe5, 0xeb, 0xe5, 0xf2, 0xf8, 
  0xff, 0xff, 0xff, 0x3f, 0x1f, 0x07, 0x23, 0x55, 0xfd, 0x53, 0x2f, 0x1f, 0xff, 0xff, 0xff, 0xff, 
  0xdf, 0x85, 0x00, 0x10, 0x28, 0x54, 0x7e, 0x14, 0x3e, 0x7e, 0x2f, 0x1d, 0x2a, 0x01, 0x0b, 0xbf, 
  0xcb, 0x82, 0x10, 0x0a, 0x15, 0x7e, 0x14, 0x3e, 0x54, 0x3e, 0x1e, 0x2e, 0x17, 0x2c, 0x91, 0xc7, 
  0xff, 0xff, 0xeb, 0xd5, 0xaa, 0xd0, 0xa0, 0xde, 0xbe, 0xde, 0xa0, 0xd0, 0xab, 0xd5, 0xeb, 0xff, 
  0x1f, 0x8f, 0x47, 0xf7, 0x9b, 0x93, 0xf1, 0xfd, 0xfd, 0x7b, 0x4b, 0xc7, 0x77, 0xef, 0x1f, 0xff, 
  0xfe, 0xfc, 0xd9, 0xaa, 0x51, 0xa2, 0x05, 0x83, 0x05, 0xa2, 0x54, 0xaa, 0xd9, 0xfc, 0xfe, 0xff, 
  0x03, 0xf3, 0x53, 0x73, 0x53, 0xd3, 0x51, 0xf6, 0x56, 0x71, 0xd3, 0x53, 0x73, 0x53, 0xf3, 0x03, 
  0xfc, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x81, 0x7d, 0x7d, 0x81, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfc, 
  0x02, 0xea, 0xd6, 0x02, 0x06, 0xea, 0xd6, 0x02, 0x06, 0xea, 0xd6, 0x02, 0x06, 0xea, 0xd6, 0x02, 
  0x00, 0xea, 0xd5, 0x00, 0x00, 0xea, 0xd5, 0x00, 0x00, 0xea, 0xd5, 0x00, 0x00, 0xea, 0xd5, 0x00, 
  0x00, 0xaa, 0x00, 0xff, 0xff, 0x06, 0x06, 0x07, 0xf7, 0x06, 0x06, 0x07, 0xff, 0x00, 0xaa, 0x00, 
  0x80, 0xaa, 0x00, 0x7f, 0x7f, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7f, 0x00, 0xaa, 0x80, 
  0xff, 0xfe, 0x06, 0xb3, 0x71, 0xe9, 0xd9, 0xb9, 0x71, 0xe9, 0xd9, 0xb9, 0x73, 0x06, 0xfe, 0xff, 
  0xbf, 0xbf, 0x80, 0xbb, 0xb7, 0xae, 0x9d, 0xbb, 0xb7, 0xae, 0x9c, 0xb8, 0xb7, 0x80, 0xbf, 0xbf, 
  0x0f, 0xc3, 0x19, 0x25, 0x24, 0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x25, 0x19, 0x83, 0x0f, 0xff, 
  0xf0, 0xcf, 0x80, 0xbf, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0xbf, 0x80, 0xcf, 0xf0, 0xff, 
  0xff, 0xff, 0xff, 0x03, 0xe9, 0xb5, 0xfa, 0xb8, 0xfa, 0xb8, 0xb5, 0xe9, 0x03, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xab, 0xd0, 0x6f, 0x87, 0x4f, 0xa7, 0x6f, 0xe7, 0xaf, 0x17, 0xb0, 0xeb, 0xff, 0xff, 
  0x88, 0x98, 0xcc, 0x44, 0x62, 0x65, 0x60, 0x61, 0x20, 0x60, 0x20, 0x60, 0x20, 0x50, 0x30, 0x18, 
  0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x30, 0x10, 0x08, 0x0c, 0x06, 0x03, 
  0x0d, 0xf2, 0x1f, 0xc0, 0x60, 0x65, 0x60, 0x61, 0x20, 0x60, 0x20, 0x60, 0x20, 0x50, 0x30, 0x18, 
  0x60, 0x9f, 0xf0, 0x00, 0x18, 0x0c, 0x82, 0xc0, 0x40, 0x60, 0x30, 0x10, 0x08, 0x0c, 0x06, 0x03, 
  0x88, 0x98, 0xcc, 0x44, 0x62, 0x65, 0x60, 0x61, 0x20, 0x60, 0x20, 0x60, 0x90, 0x07, 0xfe, 0x01, 
  0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0xe0, 0xb0, 0x94, 0x02, 0xf0, 0x9f, 0x60, 
  0x0d, 0x9e, 0x5e, 0x8e, 0x4e, 0x04, 0x26, 0x66, 0x35, 0x65, 0x26, 0x4c, 0x2e, 0x4d, 0x0d, 0x09, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x30, 0x10, 0x08, 0x0c, 0x06, 0x03, 
  0x88, 0x98, 0xcc, 0x44, 0x62, 0x65, 0x60, 0x61, 0x20, 0x60, 0x20, 0x60, 0x20, 0x50, 0x30, 0x18, 
  0xa5, 0xa1, 0xa4, 0xb0, 0xd0, 0xb0, 0xd2, 0xd4, 0xb2, 0xb4, 0xb0, 0xd4, 0xa4, 0xa6, 0xa6, 0xa3, 
  0xff, 0x3f, 0x8f, 0xa7, 0xe3, 0xf3, 0x79, 0x71, 0x3d, 0x1d, 0x0d, 0x0e, 0x8c, 0x86, 0x46, 0x05, 
  0x03, 0xfd, 0xfc, 0x0f, 0x07, 0x01, 0x80, 0xc0, 0x40, 0x60, 0x34, 0x13, 0x09, 0x0c, 0x04, 0x02, 
  0x09, 0x1d, 0x0e, 0x06, 0x26, 0x66, 0x6d, 0x6e, 0xcc, 0x19, 0x79, 0xb3, 0xc7, 0xcf, 0x1f, 0xff, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x61, 0x32, 0x00, 0x01, 0xff, 0x7b, 0x84, 
  0xdb, 0xa4, 0x7f, 0xc0, 0x02, 0x05, 0x40, 0x61, 0xa0, 0x60, 0x20, 0x60, 0x20, 0x50, 0x30, 0x18, 
  0xff, 0xff, 0xfc, 0xfb, 0xf9, 0xf6, 0xec, 0xd8, 0xd8, 0xd1, 0xb0, 0xa0, 0xa0, 0xa4, 0xa6, 0xa3, 
  0x88, 0x98, 0xcc, 0x44, 0x62, 0x65, 0x60, 0x21, 0x20, 0x10, 0x01, 0xc0, 0xb0, 0x3f, 0xdb, 0xe4, 
  0xa1, 0xa1, 0xa0, 0xa0, 0xa0, 0xb0, 0xd0, 0xd8, 0xec, 0xf6, 0xfb, 0xfb, 0xfc, 0xff, 0xff, 0xff, 
};

int16_t viewX, viewY;

bool btn(int b)
{
  return arduboy.justPressed(b) || (arduboy.pressed(b) && arduboy.everyXFrames(5));
}

void setup()
{
  viewX = 737 * 16;
  viewY = 665 * 16;
  arduboy.begin();
  arduboy.setFrameRate(255);
}

void loop()
{
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();
 
  int16_t camSpeed = 3;

  if (arduboy.pressed(A_BUTTON))
    camSpeed = 16;

  if (btn(UP_BUTTON))
    viewY -= camSpeed;
  else if (btn(DOWN_BUTTON))
    viewY += camSpeed;

  if (btn(RIGHT_BUTTON))
    viewX += camSpeed;
  else if (btn(LEFT_BUTTON))
    viewX -= camSpeed;

  if (viewX < 0)
    viewX = 0;
  else if (viewX > 1024 * 16)
    viewX = 1024 * 16;

  if (viewY < 0)
    viewY = 0;
  else if (viewY > 1024 * 16)
    viewY = 1024 * 16;

  int16_t tileX = viewX / 16;
  int16_t tileY = viewY / 16;
  int16_t fractX = viewX % 16;
  int16_t fractY = viewY % 16;

  for (int16_t y = 0; y < 5; ++y)
    for (int16_t x = 0; x < 9; ++x)
      Sprites::drawOverwrite(x * 16 - fractX,y * 16 - fractY,tiles,getMapTile(tileX + x,tileY + y));

  arduboy.print(tileX);
  arduboy.print(' ');
  arduboy.print(tileY);

  arduboy.display();
}
