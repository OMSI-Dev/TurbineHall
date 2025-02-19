#include <Arduino.h>
#include <Timer.h>
#include <Bounce2.h>
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#include <Pulse.h>
#include "pins.h"
#include "light.h"
#include "motor.h"

void setup() 
{
  Serial.begin(9600);
  //set to RGB or RGBW if using strips for shake table/ this also switches libraries
  #ifdef ring
    FastLED.addLeds<NEOPIXEL, dataPin>(ringLight, ledNum);
  #elif strip
    strip.begin();
  #endif

  setPins();
  lightOff();

}

void loop() 
{
  startBtn.update();
  motor();

}
