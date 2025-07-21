#include <Arduino.h>
#include <Timer.h>
#include <Bounce2.h>
#include <FastLED.h>
#include <Pulse.h>
#include "pins.h"
#include "light.h"
#include "motor.h"


void setup() 
{
  Serial.begin(9600);

  //set to RGB or RGBW if using strips for shake table
  #ifdef ring
    FastLED.addLeds<NEOPIXEL, dataPin>(ringLight, ledNum);
  #elif defined(strip)
    FastLED.addLeds(&rgbwEmu, ledStrip, ledNum);
  #endif
  //enable correct pins
  setPins();
  //start with lights off
  lightTest();
  lightOff();

}

void loop() 
{
  //check buttons
  startBtn.update();
  
  #ifdef hasStop
  stopBtn.update();
  #endif

  uint16_t speed = speedControl();
  motor(speed);

}
