#include <FastLED.h>
#include <RTClib.h>
#include <Wire.h>
#include "Digit.h"
#include "MatrixConfig.h"

#define NUM_LEDS MATRIX_WIDTH * MATRIX_HEIGHT
#define MATRIX_PIN 2

#define PIN_LR A1
#define PIN_MR A2
#define PIN_D 7

RTC_DS3231 rtc;

CRGB leds[NUM_LEDS];

Digit hourLow = Digit();
Digit hourHigh = Digit();

Digit minuteLow = Digit();
Digit minuteHigh = Digit();

Digit secondLow = Digit();
Digit secondHigh = Digit();

CRGB bgColor = CRGB(0, 0, 0);

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
  pinMode(PIN_LR, INPUT);
  pinMode(PIN_MR, INPUT);
  pinMode(PIN_D, INPUT_PULLUP);

  Serial.begin(9600);
  Wire.begin();

//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//   delay(3000);

  FastLED.addLeds<LED_TYPE, MATRIX_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip).setDither(0);

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

int diag[4];

void loop() {
  int brightness = getBrightness(diag);
  bool isDiagnosticsMode = !digitalRead(PIN_D);
  
  if (isDiagnosticsMode) {
    updateDigits(diag);
  } else {
    updateDigits(rtc.now());
  }
  
  hourHigh.draw(leds);
  hourLow.draw(leds);

  minuteHigh.draw(leds);
  minuteLow.draw(leds);

  secondHigh.draw(leds);
  secondLow.draw(leds);

  FastLED.setBrightness(brightness);
  FastLED.show();
  FastLED.delay(30);
}

void updateDigits(int diag[]) {
  hourHigh.set(diag[1] / 10);
  hourLow.set(diag[1] % 10);

  minuteHigh.set(diag[2] / 10);
  minuteLow.set(diag[2] % 10);

  secondHigh.set(diag[0] / 10);
  secondLow.set(diag[0] % 10);
}

void updateDigits(DateTime dt) {
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
