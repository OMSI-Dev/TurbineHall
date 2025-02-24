
#ifdef ring
  #ifdef small
    #define ledNum 24
    CRGB ringLight[ledNum];
  #elif defined(large)
    #define ledNum 60
    CRGB ringLight[ledNum];
  #endif
#elif defined(strip)
  #define ledNum 24
  Adafruit_NeoPixel strip(ledNum, dataPin, NEO_GRBW + NEO_KHZ800);
#endif

MoToTimer ringTimer;
uint8_t i =0;

//break into sections
CRGB* quad1 = &ringLight[0]; 
CRGB* quad2 = &ringLight[(ledNum/4 * 1)]; 
CRGB* quad3 = &ringLight[(ledNum/4 * 2)]; 
CRGB* quad4 = &ringLight[(ledNum/4 * 3)]; 

uint16_t lightSpeedControl()
{
    uint16_t tempRead = analogRead(pot);
    uint16_t tempSpeed = map(tempRead, 0,1024,100,20);

    return tempSpeed;

}

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

void lightOff()
{
    //fill_solid(ringLight,ledNum,CRGB::Black);
    FastLED.clear();
    FastLED.show();
}
