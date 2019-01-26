#include "Digit.h"
#include "MatrixConfig.h"
#include "Arrays.h"
#include <Arduino.h>

XY::XY(int _x, int _y) {
  x = _x;
  y = _y;
};

XY::XY() {
  x = 0;
  y = 0;
}

Digit::Digit() {
  _x = 3;
  _y = 4;
  _digit = -1;

  _fontColor = CRGB::Red;
  _bgColor = CRGB::Black;

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      int frameIndex = MAX_NUM_FRAMES - (y * WIDTH + x) - 1;
      _frames[frameIndex].x = x;
      _frames[frameIndex].y = y;
    }
  }

  _currentFrame = MAX_NUM_FRAMES; // Means nothing is left to draw
}

void Digit::set(byte digit) {
  if (_digit == digit || digit > 9) {
    return;
  }

  if (_currentFrame < MAX_NUM_FRAMES) {
    return;
  }
  
  _digit = digit;
  _updateFrames();
}

void Digit::setCoordinates(int x, int y) {
  _x = x;
  _y = y;
}

void Digit::setFontColor(CRGB color) {
  _fontColor = color;
}

void Digit::setBgColor(CRGB color) {
  _bgColor = color;
}

void Digit::setDotColor(CRGB color) {
  _dotColor = color;
}

byte Digit::get() {
  return _digit;
}

void Digit::draw(CRGB leds[]) {
  if (_currentFrame >= MAX_NUM_FRAMES) {
    return;
  }

  for (int i = 0; i <= _currentFrame; i++) {
    XY pixel = _frames[i];
    int ledIndex = Matrix::xy(_x + pixel.x, _y + pixel.y);

    if (_isPixelFilled(pixel)) {
      leds[ledIndex] = _fontColor;
    } else {
      leds[ledIndex] = _bgColor;
    }

    if (i == _currentFrame && i != (MAX_NUM_FRAMES - 1)) {
      leds[ledIndex] = _dotColor;
    }
  }

  _currentFrame++;
}

bool Digit::_isPixelFilled(XY pixel) {
  byte thisByte = pgm_read_byte(&(font3x5[_digit][pixel.x]));
  return (thisByte & (1 << pixel.y));
}

void Digit::_updateFrames() {
//  Arrays::shuffle(_frames, MAX_NUM_FRAMES);
  _currentFrame = 0;
}
