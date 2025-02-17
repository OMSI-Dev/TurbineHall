#include <Arduino.h>
#include <Timer.h>
#include <Bounce2.h>
#include <FastLED.h>
#include "pins.h"
#include "light.h"

#ifdef small
  CRGB ring[24];
  #define ledNum 24
#elif large
  CRGB ring[30];
  #define ledNum 30
#endif


void setup() 
{
FastLED.addLeds<NEOPIXEL, dataPin>(ring, ledNum);
}

void loop() {
  // put your main code here, to run repeatedly:
}
