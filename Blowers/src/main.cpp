#include <Arduino.h>
#include <Timer.h>
#include <Bounce2.h>
#include <FastLED.h>
#include "pins.h"
#include "light.h"
#include "motor.h"

#ifdef small
  CRGB ring[24];
  #define ledNum 24
#elif large
  CRGB ring[30];
  #define ledNum 30
#endif


void setup() 
{
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, dataPin>(ring, ledNum);
  setPins();
  digitalWrite(13,HIGH);
}

void loop() 
{
  rampMotor();
  //digitalWrite(motorPin,HIGH);
}
