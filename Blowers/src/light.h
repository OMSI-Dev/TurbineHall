
#ifdef ring
  #ifdef small
    #define ledNum 24
    CRGB ringLight[ledNum];
  #elif defined(large)
    #define ledNum 60
    CRGB ringLight[ledNum];
  #endif
#elif defined(strip)
  #define ledNum 26
  CRGB ledStrip[ledNum];
#endif

MoToTimer ledTimer,rampTimer;
uint8_t i =0;
uint16_t rampTime = 125, r = rampTime;

bool rampLightSpeed = 1;

#ifdef ring
  //break into sections
  CRGB* quad1 = &ringLight[0]; 
  CRGB* quad2 = &ringLight[(ledNum/4 * 1)]; 
  CRGB* quad3 = &ringLight[(ledNum/4 * 2)]; 
  CRGB* quad4 = &ringLight[(ledNum/4 * 3)]; 
#endif
#ifdef strip
  //break into sections
  CRGB* ledStrip1 = &ledStrip[0]; 
  CRGB* ledStrip2 = &ledStrip[(ledNum/2 * 1)]; 
#endif

uint16_t lightSpeedControl()
{
    uint16_t tempRead = analogRead(pot);
    uint16_t tempSpeed = map(tempRead, 0,1024,100,20);
    Serial.print("Pot: ");
    Serial.println(tempRead);
    return tempSpeed;

}

uint16_t ringSpeed()
{
    uint16_t tempRead = analogRead(pot);
    uint16_t tempPos = map(tempRead, 0,1024,1,25);
    Serial.print("Pot: ");
    Serial.println(tempRead);
    tempPos = constrain(tempPos,1,25);
    Serial.print("tempPos: ");
    Serial.println(tempPos);
    return tempPos;

}

#ifdef ring
  void animationLight()
  {
    //this is the highest position to put the led to.
    uint8_t ledPos = ringSpeed();
    //Set to current position
    fill_gradient_RGB(ringLight,ledPos,CRGB::Green,CRGB::Red);
    FastLED.show();
    //clear and update again
    FastLED.clear();
    FastLED.show();
  }
#endif

#ifdef strip
  void animationLight()
  {
      if(!rampLightSpeed)
        {
          if(!ledTimer.running())
          {
              
              i++;
              if(i==ledNum/2){i = 0;}

              ledStrip1[i] = CRGB::OrangeRed;
              ledStrip2[i] = CRGB::OrangeRed;

              #if !defined(controlledSpeed)
              ledTimer.setTime(50);
              #else
              uint8_t speed = lightSpeedControl();
              ledTimer.setTime(speed);
              #endif

              fadeToBlackBy(ledStrip,ledNum,100);
          }
        }
      if(rampLightSpeed)
      {
        if(!rampTimer.running())
        {
            i++;
            if(i==ledNum/2){i = 0;}

            ledStrip1[i] = CRGB::OrangeRed;
            ledStrip2[i] = CRGB::OrangeRed;
            r--;
            rampTimer.setTime(r);

            uint8_t speed = lightSpeedControl();

            Serial.print("R: ");
            Serial.print(r);
            Serial.print(" | ");
            Serial.print("Speed: ");
            Serial.println(speed);
            
            if(r==speed)
            {
              r=rampTime;
              rampLightSpeed = 0;
              Serial.println("Lights match Speed...");
              Serial.print("R = ");
              Serial.println(r);
            }
            fadeToBlackBy(ledStrip,ledNum,100);
        }
      }

        FastLED.show();
  }
#endif

void lightOff()
{
    //fill_solid(ringLight,ledNum,CRGB::Black);
    FastLED.clear();
    FastLED.show();
}
