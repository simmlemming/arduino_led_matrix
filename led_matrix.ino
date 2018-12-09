#include <FastLED.h>
#include <RTClib.h>
#include <Wire.h>
#include "Digit.h"
#include "MatrixConfig.h"

#define NUM_LEDS MATRIX_WIDTH * MATRIX_HEIGHT
#define MATRIX_PIN 2

RTC_DS3231 rtc;

CRGB leds[NUM_LEDS];
uint8_t ledBrightness = 4;

Digit hourLow = Digit();
Digit hourHigh = Digit();

Digit minuteLow = Digit();
Digit minuteHigh = Digit();

Digit secondLow = Digit();
Digit secondHigh = Digit();

CRGB bgColor = CRGB(0, 0, 32);

CRGB hourFontColor = CRGB::Orange;
CRGB hourBgColor = bgColor;
CRGB hourDotColor = CRGB::Red;

CRGB minuteFontColor = CRGB::Orange;
CRGB minuteBgColor = bgColor;
CRGB minuteDotColor = CRGB::Red;

CRGB secondFontColor = CRGB::Red;
CRGB secondBgColor = bgColor;
CRGB secondDotColor = CRGB::Orange;

void setup() {
  //  bg_colors[0] -= 40;
  Serial.begin(9600);
  Wire.begin();

  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // delay(3000);

  FastLED.addLeds<LED_TYPE, MATRIX_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip).setDither(0);
  FastLED.setBrightness(ledBrightness);

  //  for (int i = 0; i < NUM_LEDS; i++) {
  //    leds[i] = bgColor;
  //  }

  hourHigh.setCoordinates(0, 10);
  hourLow.setCoordinates(4, 10);
  
  hourHigh.setFontColor(hourFontColor);
  hourLow.setFontColor(hourFontColor);
  
  hourHigh.setBgColor(hourBgColor);
  hourLow.setBgColor(hourBgColor);
  
  hourHigh.setDotColor(hourDotColor);
  hourLow.setDotColor(hourDotColor);


  
  minuteHigh.setCoordinates(9, 10);
  minuteLow.setCoordinates(13, 10);
  
  minuteHigh.setFontColor(minuteFontColor);
  minuteLow.setFontColor(minuteFontColor);
  
  minuteHigh.setBgColor(minuteBgColor);
  minuteLow.setBgColor(minuteBgColor);
  
  minuteHigh.setDotColor(minuteDotColor);
  minuteLow.setDotColor(minuteDotColor);



  secondHigh.setCoordinates(4, 3);
  secondLow.setCoordinates(8, 3);
  
  secondHigh.setFontColor(secondFontColor);
  secondLow.setFontColor(secondFontColor);
  
  secondHigh.setBgColor(secondBgColor);
  secondLow.setBgColor(secondBgColor);
  
  secondHigh.setDotColor(secondDotColor);
  secondLow.setDotColor(secondDotColor);
}

int frameCounter = 0;
int digit = 0;

void loop() {
  updateDigits();
//  updateColors(secondHigh);
//  updateColors(secondLow);

  hourHigh.draw(leds);
  hourLow.draw(leds);

  minuteHigh.draw(leds);
  minuteLow.draw(leds);

  secondHigh.draw(leds);
  secondLow.draw(leds);

  FastLED.show();
  FastLED.delay(30);
}


#define NUM_COLORS 4
//CRGB bg_colors[] = {CRGB::Chocolate, CRGB::DarkRed, CRGB::DarkGreen, CRGB::DarkBlue, CRGB::Maroon};
CRGB fontColors[] = {CRGB::Red, CRGB::Orange, CRGB::Green, CRGB::Yellow};

void updateColors(Digit& digit) {
  int colorIndex = digit.get() % NUM_COLORS;
  digit.setFontColor(fontColors[colorIndex]);
}

void updateDigits() {
  DateTime dt = rtc.now();

  byte h = dt.hour();
  hourHigh.set(h / 10);
  hourLow.set(h % 10);

  byte m = dt.minute();
  minuteHigh.set(m / 10);
  minuteLow.set(m % 10);

  byte s = dt.second();
  secondHigh.set(s / 10);
  secondLow.set(s % 10);
}
