
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

MoToTimer ringTimer;
uint8_t i =0;

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
    Serial.println(tempRead);
    return tempSpeed;

}

#ifdef ring
  void animationLight()
  {
      if(!ringTimer.running())
      {
          i++;
          if(i==ledNum/4){i = 0;}

          quad1[i] = CRGB::RoyalBlue;
          quad2[i] = CRGB::RoyalBlue;
          quad3[i] = CRGB::RoyalBlue;
          quad4[i] = CRGB::RoyalBlue;

          #if !defined(controlledSpeed)
          ringTimer.setTime(50);
          #else
          uint8_t speed = lightSpeedControl();
          ringTimer.setTime(speed);
          #endif

          fadeToBlackBy(ringLight,ledNum,55);
      }
      
      FastLED.show();
  }
#endif

#ifdef strip
  void animationLight()
  {
        if(!ringTimer.running())
        {
            i++;
            if(i==ledNum/2){i = 0;}

            ledStrip1[i] = CRGB::RoyalBlue;
            ledStrip2[i] = CRGB::RoyalBlue;

            #if !defined(controlledSpeed)
            ringTimer.setTime(50);
            #else
            uint8_t speed = lightSpeedControl();
            ringTimer.setTime(speed);
            #endif

            fadeToBlackBy(ledStrip,ledNum,55);
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
