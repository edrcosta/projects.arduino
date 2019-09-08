/*
  Huge map Arduboy demo.

  author: Miloslav Ciz
  license: CC0 1.0
*/

#include <stdint.h>

//-----------------------------------------------------------------------------
// CONFIG: set basic values here

#define T_GROUND       0
#define T_GROUND2      1
#define T_GROUND3      2
#define T_ROAD         3
#define T_ROAD2        4
#define T_ROCK         5
#define T_TREE_T       6
#define T_TREE_B       7
#define T_BUSH         8
#define T_SIGN         9
#define T_HOUSE_ROOF   10
#define T_HOUSE_WINDOW 11
#define T_HOUSE_DOOR   12
#define T_BARREL       13
#define T_GRAVE        14
#define T_WATER        15
#define T_WATER_B_L    16
#define T_WATER_B_R    17
#define T_WATER_B_T    18
#define T_WATER_B_B    19
#define T_WATER_B_TL   20
#define T_WATER_B_TR   21
#define T_WATER_B_BL   22
#define T_WATER_B_BR   23

#define USE_CACHE 1

#define CACHE_WIDTH 32
#define CACHE_HEIGHT 16
#define CACHE_BASE_POINT_X 12
#define CACHE_BASE_POINT_Y 6

const uint8_t patternTree[] =
{
  1, 2, // width, height
  // tiles
  T_TREE_T,
  T_TREE_B
};

const uint8_t patternHouse[] =
{
  3, 2, // width, height
  // tiles
  T_HOUSE_ROOF,   T_HOUSE_ROOF, T_HOUSE_ROOF,
  T_HOUSE_WINDOW, T_HOUSE_DOOR, T_HOUSE_WINDOW
};

typedef struct
{
  int16_t x;
  int16_t y;
  const uint8_t *pattern;
} PatternObject;

const PatternObject patternObjects[] =
{
  { 87, 94, patternHouse },   // NW town
  { 94, 95, patternHouse },
  { 89, 97, patternHouse },

  { 737, 666, patternHouse }, // SE TOWN
  { 740, 681, patternHouse },
  { 739, 671, patternHouse },

  { 929, 349, patternHouse }, // E, sea house
  { 218, 430, patternHouse }, // W, abandoned house
};

#define PATTERN_OBJECTS (sizeof(patternObjects) / sizeof(PatternObject))

//-----------------------------------------------------------------------------
// PRIVATES: don't touch

int16_t _mapX, _mapY; // in order to save space on code, pass these via globals

#if USE_CACHE == 1
  uint8_t _cache[CACHE_WIDTH * CACHE_HEIGHT];
  int16_t _cachePosX = -1000;
  int16_t _cachePosY = -1000;
#endif

int8_t _isWithinDistance(int16_t x, int16_t y, int16_t d, uint8_t distanceType)
{
  int16_t dx = x - _mapX;
  int16_t dy = y - _mapY;

  switch (distanceType)
  {
    case 0:
    {
      int32_t dxw = dx;
      int32_t dyw = dy;
      int32_t dw = d;

      return dxw * dxw + dyw * dyw <= dw * dw;
      break;
    }

    case 1:
    default:
      if (dx < 0)
        dx *= -1;

      if (dy < 0)
        dy *= -1;

      return dx + dy <= d;
      break;
  }
}

int8_t isInRect(int16_t x, int16_t y, int16_t w, int16_t h); // forw decl

static inline int16_t _checkPatternObjects()
{
  for (uint16_t i = 0; i < PATTERN_OBJECTS; ++i)
  {
    uint8_t w = patternObjects[i].pattern[0];
    uint8_t h = patternObjects[i].pattern[1];

    if (isInRect(patternObjects[i].x,patternObjects[i].y,w,h))
    {
      int16_t x = _mapX - patternObjects[i].x;
      int16_t y = _mapY - patternObjects[i].y;

      return patternObjects[i].pattern[2 + y * w + x];
    }
  }

  return -1;
}

static inline int16_t _abs(int16_t v)
{
  return v >= 0 ? v : -1 * v;
}

//-----------------------------------------------------------------------------
// PUBLICS: use to create the map

int8_t isInRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
  return
    _mapX >= x && _mapX < (x + w) &&
    _mapY >= y && _mapY < (y + h);
}

static inline int8_t isInDiamond(int16_t x, int16_t y, int16_t r)
{
  return _isWithinDistance(x,y,r,1);
}

static inline int8_t isInCircle(int16_t x, int16_t y, int16_t r)
{
  return _isWithinDistance(x,y,r,0);
}

static inline int8_t isInPoint(int16_t x, int16_t y)
{
  return _mapX == x && _mapY == y;
}

int8_t isInLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t width)
{
  int16_t l = x1;
  int16_t r = x2;
  int16_t t = y1;
  int16_t b = y2;

  if (x1 > x2)
  {
    l = x2;
    r = x1;
  }

  if (y1 > y2)
  {
    t = y2;
    b = y1;
  }
  
  if ((_mapX < (l - width)) ||
      (_mapX > (r + width)) ||
      (_mapY < (t - width)) ||
      (_mapY > (b + width)))
    return 0;

  int32_t w = x2 - x1;
  int32_t h = y2 - y1;
  int32_t x = _mapX - x1;
  int32_t y = _mapY - y1;

  int32_t wh = w * h;

  if (wh == 0)
    return 1;

  int32_t diff = _abs( (64 * (h * x - w * y)) / wh );

  return diff <= width * 2;
}

int8_t isInNoise(int16_t seed)
{
  uint8_t a = (_mapX + seed) * (_mapY - seed);
  uint8_t b = _mapX + 7 * (_mapY + seed);

  return ((a % 7) & 0x01) != ((b % 3) & 0x01);
}

static inline int8_t isInDither()
{
  return _mapX % 2 == _mapY % 2;
}

uint8_t pattern(const uint8_t *pat, int8_t offX, int8_t offY)
{
  uint8_t w = pat[0];
  uint8_t h = pat[1];

  uint8_t x = (_mapX + offX) % w;
  uint8_t y = (_mapY + offY) % h;
  
  return pat[2 + y * w + x];
}

#define checkPatternObjects\
  {\
    int16_t t = _checkPatternObjects();\
    if (t >= 0)\
      return t;\
  }

//-----------------------------------------------------------------------------
// MAP FUNCTION: create the map here

/*
  This function should return the base unpostrpcessed tile, such as ground,
  or water.
*/

uint8_t getBaseMapTile(int16_t x, int16_t y)
{
  /* the x and y parameters will be passed to functions via global variables,
     in order to save code space on passing parameters */

  _mapX = x;
  _mapY = y;

  checkPatternObjects  // checks for patterns like houses, possibly returns

  if
  ( // "ruins"
    isInRect(275,250,30,20) ||
    isInRect(520,320,25,40) ||
    isInCircle(500,868,21)
  )
    return isInNoise(66) ? T_GROUND2 : T_ROAD2; 
  
  if
  ( // roads
    isInLine(122,870,250,700,0) ||
    isInLine(582,900,122,870,1) ||
    isInLine(800,710,582,900,0) ||
    isInLine(650,620,800,710,0) ||
    isInLine(500,700,650,620,0) ||
    isInLine(250,700,500,700,1) ||
    isInLine(480,700,480,400,1) ||
    isInLine(197,250,480,400,0) ||
    isInLine(480,400,850,300,0) ||
    isInLine(850,300,850,150,1) ||
    isInLine(850,150,800,50,1)  ||
    isInLine(800,50,400,50,1)   ||
    isInLine(400,50,180,70,1)   ||
    isInLine(180,70,200,300,1)  ||
    isInLine(200,300,300,500,0) ||
    isInLine(300,500,300,700,1) ||
    isInLine(90,95,187,150,0)
   )
    return isInNoise(33) ? T_ROAD : T_ROAD2;

  if
  ( // water 
    (                                  // sea
      !isInLine(900,600,950,500,4) &&  // islands
      (
        (x > 890 && ! isInCircle(450,220,500)) ||     
        isInCircle(1260,640,400)
      )
    ) ||

    isInLine(1200,400,705,483,7) ||    // big river
    isInLine(1200,600,720,480,5) ||
    isInLine(740,472,410,602,5)  ||
    isInLine(430,597,200,570,11) ||
    isInLine(190,570,0,600,9)    ||

    isInLine(600,0,620,200,3)    ||    // small river
    isInLine(620,200,625,500,10) ||

    isInLine(0,300,305,402,1)    ||    // small river 2
    isInLine(300,400,435,600,1)  ||

    isInLine(510,1024,600,700,1) ||    // small river 3
    isInLine(598,702,1024,620,1) ||

    (                                  // curvy river
      isInCircle(20,900,300) &&
      !isInCircle(25,895,290)  
    ) ||

    (                                  // lake
      (isInCircle(300,150,75) ||
      isInCircle(350,120,60)) &&
      isInCircle(320,180,100)
    ) ||

    isInCircle(130,780,23)             // small lake
  )
    return T_WATER;

  if
  (
    isInCircle(200,1200,400) &&
    isInNoise(1001) &&
    isInNoise(576)
  )
    return T_BUSH;

  if
  ( // trees
      !isInRect(10,10,1000,1000)   ||  // map border
      (                                // wider border
        !isInRect(20,20,960,960) &&
        (isInNoise(996) || isInNoise(612))
      ) ||
      (                                // center forest
        isInCircle(500,540,150) &&
        !isInCircle(450,480,170)
      ) ||
      isInLine(300,640,700,800,8)  ||  // S forest
      (                                // NE forest
        (
        isInLine(450,150,750,200,15) ||
        isInLine(750,200,800,350,15) ||
        isInDiamond(730,150,110)
        ) &&
        isInCircle(690,240,170)
      )
  )
    return pattern(patternTree,0,0);
      
  if
  ( // random trees, different offset
    isInNoise(5) && isInNoise(100)
  )
    return pattern(patternTree,0,1);

  if
  ( // rocks
    (
      isInNoise(30) && isInNoise(40) && isInNoise(50) &&
      isInNoise(60) && isInNoise(70)
    ) ||

    isInCircle(-125,80,200)  ||      // NW rock

    isInDiamond(310,830,60)  ||      // SW rock
    isInRect(310,830,100,30) ||

    isInDiamond(800,870,55)  ||      // SE rock
    isInRect(780,860,45,300)
  )
    return T_ROCK;

  if
  ( // signs
    isInPoint(185,147) ||
    isInPoint(483,402) ||
    isInPoint(499,52)  ||
    isInPoint(766,325) ||
    isInPoint(801,707) ||
    isInPoint(248,699) ||
    isInPoint(195,249)
  )
    return T_SIGN;

  if
  ( // barrels
    isInPoint(96,97) ||
    isInPoint(865,573) ||
    isInRect(742,667,3,3)
  )
    return T_BARREL;

  if
  ( // graves
    isInPoint(195,693) ||
    isInPoint(353,466) ||
    isInRect(762,328,4,5)
  )
    return T_GRAVE;

  // grounds 

  if (isInNoise(1))
    return T_GROUND2;

  if (isInNoise(3))
    return T_GROUND3;

  return T_GROUND;      // default tile
}

/*
  Helper function, returns a pattern of tile neigbours as a 4 bit mask:

  0000----
      ^^^^
      |||\_ top
      ||\__ right
      |\___ bottom
      \____ left

  1 means the neighbour differs from the center tile, 0 means the opposite.
*/

uint8_t getNeighbourPattern(int16_t x, int16_t y)
{
  uint8_t tile = getBaseMapTile(x,y);

  uint8_t result = 0;

  result |= (getBaseMapTile(x,     y - 1) != tile) << 0;
  result |= (getBaseMapTile(x + 1, y    ) != tile) << 1;
  result |= (getBaseMapTile(x    , y + 1) != tile) << 2;
  result |= (getBaseMapTile(x - 1, y    ) != tile) << 3;

  return result;
}

/*
  This function retrieves the base tile and applies some post-processing to it,
  e.g. add borders, or clean up patterns.
*/

static inline uint8_t getProcessedMapTile(int16_t x, int16_t y)
{
  uint8_t tile = getBaseMapTile(x,y);

  if (
    (tile == T_TREE_T && getBaseMapTile(x,y + 1) != T_TREE_B) ||
    (tile == T_TREE_B && getBaseMapTile(x,y - 1) != T_TREE_T))
    return T_GROUND;

  if (tile == T_WATER)
  {
    uint8_t neigh = getNeighbourPattern(x,y);

    switch (neigh)
    {
      case 0:  break;
      case 1:  return T_WATER_B_T;  break;
      case 2:  return T_WATER_B_R;  break;
      case 4:  return T_WATER_B_B;  break;
      case 8:  return T_WATER_B_L;  break;
      case 3:  return T_WATER_B_TR; break;
      case 6:  return T_WATER_B_BR; break;
      case 12: return T_WATER_B_BL; break;
      case 9:  return T_WATER_B_TL; break;
      default: return T_GROUND; break;
    }
  }

  return tile;
}

#if USE_CACHE == 1
  static inline uint8_t getMapTileWithCache(int16_t x, int16_t y)
  {
    if (
      (x < _cachePosX) ||
      (x >= _cachePosX + CACHE_WIDTH) ||
      (y < _cachePosY) ||
      (y >= _cachePosY + CACHE_HEIGHT)
      )
    {
      // cache miss

      for (uint8_t j = 0; j < CACHE_HEIGHT; ++j)
        for (uint8_t i = 0; i < CACHE_WIDTH; ++i)
          _cache[j * CACHE_WIDTH + i] = getProcessedMapTile(x - CACHE_BASE_POINT_X + i,y - CACHE_BASE_POINT_Y + j);

      _cachePosX = x - CACHE_BASE_POINT_X;
      _cachePosY = y - CACHE_BASE_POINT_Y;
    }

    x -= _cachePosX;
    y -= _cachePosY;
    return _cache[y * CACHE_WIDTH + x];
  }
#endif

/*
  This function is to be used for retrieving the tiles from the outside.
*/

uint8_t getMapTile(int16_t x, int16_t y)
{
  #if USE_CACHE == 1
    return getMapTileWithCache(x,y);
  #else
    return getProcessedMapTile(x,y);
  #endif
}
