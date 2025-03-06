#include <Arduino.h>
#include <Timer.h>
#include <Bounce2.h>
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#include <Pulse.h>
#include "pins.h"
#include "light.h"
#include "motor.h"

Rgbw rgbw = Rgbw(
  kRGBWDefaultColorTemp,
  kRGBWExactColors,      // Mode
  W3                     // W-placement
);

void setup() 
{
  Serial.begin(9600);
  //set to RGB or RGBW if using strips for shake table/ this also switches libraries
  #ifdef ring
    FastLED.addLeds<NEOPIXEL, dataPin>(ringLight, ledNum);
  #elif defined(strip)
    //ledStrip.begin();
    FastLED.addLeds<WS2812, dataPin, GRB>(ledStrip, ledNum).setRgbw(RgbwDefault());
  #endif

  setPins();
  lightOff();

}

void loop() 
{
  startBtn.update();
  uint16_t speed = speedControl();
  motor(speed);

}
