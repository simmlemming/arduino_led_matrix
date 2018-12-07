const bool kMatrixSerpentineLayout = true;

uint16_t XY( uint8_t x, uint8_t y) {
  uint16_t i;

  if ( kMatrixSerpentineLayout == false) {
    i = (y * MATRIX_WIDTH) + x;
  }

  if ( kMatrixSerpentineLayout == true) {
    if ( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (MATRIX_WIDTH - 1) - x;
      i = (y * MATRIX_WIDTH) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * MATRIX_WIDTH) + x;
    }
  }

  return i;
}

bool eq(CRGB l, CRGB r) {
  //  print(l);
  //  print(r);
  bool result = (l.r == r.r && l.g == r.g && l.b == r.b);
  return result;
}

void print(CRGB color) {
  Serial.print(color.r);
  Serial.print(", ");
  Serial.print(color.g);
  Serial.print(", ");
  Serial.println(color.b);
}
