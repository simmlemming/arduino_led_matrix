#include <FastLED.h>

#define MAX_INVISIBLE_COLORS 4

class InvisibleColors {
  public:
    InvisibleColors();
    void add(CRGB color);
    bool contains(CRGB color);

  private:
    CRGB _colors[MAX_INVISIBLE_COLORS];
    int _next_index;
};
