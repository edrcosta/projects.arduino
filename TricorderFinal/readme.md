### Atual Specs ###################################

- Power: 9V batery 
- Processing: atmega328p 8mhz
- Display: oled ic2 128x64 

### Screen Code ###################################

U8GLIB_SSD1306_128X64_2X u8g(U8G_I2C_OPT_NONE);

### Pinout ########################################
+-------------------------------------------------+
|    Key    |  CODE  |  SeqCode  | Type           |
+-------------------------------------------------+
|    left   |  A2    | 16        | Analog         |
|    rigth  |  A1    | 15        | Analog         |          
|    up     |  A3    | 17        | Analog         |
|    down   |  2     | 2         | Digital (why?) |
+-------------------------------------------------+