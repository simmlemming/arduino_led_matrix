#include <FastLED.h>

class XY {
  public:
    XY(int _x, int _y);
    XY();
    int x, y;
};

class Digit {
  public:
    Digit();
    void set(byte digit);
    byte get();
    void setCoordinates(int x, int y);
    void setFontColor(CRGB color);
    void setBgColor(CRGB color);
    void setDotColor(CRGB color);
    void draw(CRGB leds[]);

  private:
    static const int WIDTH = 3;
    static const int HEIGHT = 5;
    static const int NUM_PIXELS = WIDTH * HEIGHT;
    static const int MAX_NUM_FRAMES = NUM_PIXELS;
    
    byte _digit;
    int _x, _y;
    XY _frames[MAX_NUM_FRAMES];
    int _currentFrame;
    CRGB _fontColor, _bgColor, _dotColor;

    void _updateFrames();
    bool _isPixelFilled(XY pixel);
};

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
