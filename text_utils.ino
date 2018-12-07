
// шрифт 5х7
const uint8_t font5x7[][5] PROGMEM = {
  {0x3e, 0x51, 0x49, 0x45, 0x3e}, // 0 0x30 48
  {0x00, 0x42, 0x7f, 0x40, 0x00}, // 1 0x31 49
  {0x42, 0x61, 0x51, 0x49, 0x46}, // 2 0x32 50
  {0x21, 0x41, 0x45, 0x4b, 0x31}, // 3 0x33 51
  {0x18, 0x14, 0x12, 0x7f, 0x10}, // 4 0x34 52
  {0x27, 0x45, 0x45, 0x45, 0x39}, // 5 0x35 53
  {0x3c, 0x4a, 0x49, 0x49, 0x30}, // 6 0x36 54
  {0x01, 0x71, 0x09, 0x05, 0x03}, // 7 0x37 55
  {0x36, 0x49, 0x49, 0x49, 0x36}, // 8 0x38 56
  {0x06, 0x49, 0x49, 0x29, 0x1e}, // 9 0x39 57
};

// шрифт 3х5 квадратный
const uint8_t font3x5[][3] PROGMEM = {
  {0b11111, 0b10001, 0b11111},    // 0
  {0b00000, 0b00000, 0b11111},    // 1
  {0b10111, 0b10101, 0b11101},    // 2
  {0b10101, 0b10101, 0b11111},    // 3
  {0b11100, 0b00100, 0b11111},    // 4
  {0b11101, 0b10101, 0b10111},    // 5
  {0b11111, 0b10101, 0b10111},    // 6
  {0b10000, 0b10000, 0b11111},    // 7
  {0b11111, 0b10101, 0b11111},    // 8
  {0b11101, 0b10101, 0b11111},    // 9
};

void drawDigit3x5(CRGB leds[], byte digit, byte X, byte Y, CRGB color) {
  if (digit > 9) return;
  for (byte x = 0; x < 3; x++) {
    byte thisByte = pgm_read_byte(&(font3x5[digit][x]));
    for (byte y = 0; y < 5; y++) {
      if (x + X > MATRIX_WIDTH || y + Y > MATRIX_HEIGHT) continue;
      if (thisByte & (1 << y)) drawPixelXY(leds, x + X, y + Y, color);
    }
  }
}

InvisibleColors drawDigit5x7_invisible(CRGB leds[], byte digit, byte X, byte Y) {
  InvisibleColors result;

  if (digit > 9) return;
  for (byte x = 0; x < 5; x++) {
    byte thisByte = pgm_read_byte(&(font5x7[digit][x]));
    for (byte y = 0; y < 7; y++) {
      if (x + X > MATRIX_WIDTH || y + Y > MATRIX_HEIGHT) continue;
      if (thisByte & (1 << 6 - y)) {
        CRGB modified = drawPixelXY_invisible(leds, x + X, y + Y);
        result.add(modified); 
      }
    }
  }

  return result;
}

CRGB drawPixelXY_invisible(CRGB leds[], int8_t x, int8_t y) {
  if (x < 0 || x > MATRIX_WIDTH - 1 || y < 0 || y > MATRIX_HEIGHT - 1) return;
  int index = XY(x, y);
  leds[index] += CRGB(1, 1, 1);
  return leds[index];
}

void drawDigit5x7(CRGB leds[], byte digit, byte X, byte Y, CRGB color) {
  if (digit > 9) return;
  for (byte x = 0; x < 5; x++) {
    byte thisByte = pgm_read_byte(&(font5x7[digit][x]));
    for (byte y = 0; y < 7; y++) {
      if (x + X > MATRIX_WIDTH || y + Y > MATRIX_HEIGHT) continue;
      if (thisByte & (1 << 6 - y)) drawPixelXY(leds, x + X, y + Y, color);
    }
  }
}

void drawPixelXY(CRGB leds[], int8_t x, int8_t y, CRGB color) {
  if (x < 0 || x > MATRIX_WIDTH - 1 || y < 0 || y > MATRIX_HEIGHT - 1) return;
  leds[XY(x, y)] = color;
}
