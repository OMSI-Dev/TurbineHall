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

uint8_t p = 0;
void loop() 
{
  startBtn.update();
  if(startBtn.pressed())
  {
    p++;
    if(p>5){p=0;}
  }

  uint16_t tempRead = analogRead(pot);
  uint16_t tempSpeed = map(tempRead,0,1024,60, 240);
  
  Serial.print("Speed:");
  Serial.println(tempSpeed);

  analogWrite(motorPin,tempSpeed);

}
