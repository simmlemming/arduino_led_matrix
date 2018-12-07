#include <FastLED.h>
#include "invisible_colors.h"
#include <RTClib.h>
#include <Wire.h>

#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16
#define NUM_LEDS MATRIX_WIDTH * MATRIX_HEIGHT

#define MATRIX_PIN 2
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define TEXT_X 6
#define TEXT_Y 4

uint8_t ledBrightness = 32;

RTC_DS3231 rtc;

CRGB leds[NUM_LEDS];
int indexes[NUM_LEDS];
int next_index = 0;
InvisibleColors invisibleColors;

#define NUM_COLORS 3
CRGB bg_colors[] = {CRGB::Chocolate, CRGB::DarkRed, CRGB::DarkGreen, CRGB::DarkBlue, CRGB::Maroon};
CRGB text_colors[] = {CRGB::Red, CRGB::Orange, CRGB::Red, CRGB::Red, CRGB::Indigo};
int color_index = 0;


void setup() {
  bg_colors[0] -= 40;
  Serial.begin(9600);
  Wire.begin();

//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // delay(3000);

  FastLED.addLeds<LED_TYPE, MATRIX_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip).setDither(0);
  FastLED.setBrightness(ledBrightness);

  fill(indexes, NUM_LEDS);
  invisibleColors = prepare_next_frame(0);

//    CRGB c1 = CRGB::Red;
//    CRGB c2 = CRGB::Orange;
//    CRGB c3 = CRGB::Blue;
//    CRGB c4 = CRGB::Green;
//  
//    drawDigit3x5(leds, 0, 1, 11, c1);
//    drawDigit3x5(leds, 7, 5, 11, c1);
//  
//    drawDigit3x5(leds, 2, 9, 11, c2);
//    drawDigit3x5(leds, 1, 13, 11, c2);
//  
  //  drawDigit3x5(leds, 0, 1, 0, c3);
  //  drawDigit3x5(leds, 7, 5, 0, c3);
  //
  //  drawDigit3x5(leds, 0, 9, 0, c4);
  //  drawDigit3x5(leds, 2, 13, 0, c4);
  //
//    FastLED.show();
//    FastLED.delay(9234242342);
}

void t() {
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  DateTime now = rtc.now();

//  Serial.print(now.year(), DEC);
//  Serial.print('/');
//  Serial.print(now.month(), DEC);
//  Serial.print('/');
//  Serial.print(now.day(), DEC);
//  Serial.print(" (");
//  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
//  Serial.println();
//  Serial.println();
}

void loop() {
  //  if (color_index != 0) {
  //    return;
  //  }

  if (next_index == NUM_LEDS) {
    invisibleColors = prepare_next_frame(random(9));
    t();
    FastLED.delay(5000);
  }

  visualize(indexes[next_index++], invisibleColors, bg_colors[color_index], text_colors[color_index]);
  visualize(indexes[next_index++], invisibleColors, bg_colors[color_index], text_colors[color_index]);
  visualize(indexes[next_index++], invisibleColors, bg_colors[color_index], text_colors[color_index]);
  visualize(indexes[next_index++], invisibleColors, bg_colors[color_index], text_colors[color_index]);

  FastLED.show();
}

void visualize(int index, InvisibleColors colors, CRGB bg_color, CRGB text_color) {
  CRGB color = leds[index];
  if (colors.contains(color)) {
    leds[index] = text_color;
  } else {
    leds[index] = bg_color;
  }
}

InvisibleColors prepare_next_frame(int digit) {
  // Number
  InvisibleColors result = drawDigit5x7_invisible(leds, digit, TEXT_X, TEXT_Y);

  // Frame
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    drawPixelXY_invisible(leds, i, 0);
    drawPixelXY_invisible(leds, i, MATRIX_HEIGHT - 1);
  }

  for (int i = 1; i < MATRIX_HEIGHT - 1; i++) {
    drawPixelXY_invisible(leds, 0, i);
    drawPixelXY_invisible(leds, MATRIX_WIDTH - 1, i);
  }

  // Indexes
  shuffle(indexes, NUM_LEDS);
  next_index = 0;

  if (color_index++ >= NUM_COLORS) {
    color_index = 0;
  }

  return result;
}
