#include "invisible_colors.h"

InvisibleColors::InvisibleColors() {
  _next_index = 0;
}

void InvisibleColors::add(CRGB color) {
  if (contains(color) || _next_index >= MAX_INVISIBLE_COLORS) {
    return;
  }

  _colors[_next_index++] = color;
}

bool InvisibleColors::contains(CRGB item) {
  for (int i = 0; i < MAX_INVISIBLE_COLORS; i++) {
    if (_colors[i] == item) {
      return true;
    }
  }

  return false;
}
