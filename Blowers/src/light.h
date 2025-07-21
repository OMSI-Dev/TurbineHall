

//this sets the size of the array
//and if it is a ring or strip
//Small ring is around potentiometer
//large ring is around blower
//strips are in shake tables

#ifdef ring
  #ifdef small
    const uint8_t ledNum = 24;
    CRGB ringLight[ledNum];
  #elif defined(large)
    const uint8_t ledNum = 60;
    CRGB ringLight[ledNum];
  #endif
#elif defined(strip)
  const uint8_t ledNum = 24;
  const uint8_t halfLed = ledNum/2-1;
  CRGB ledStrip[ledNum];
#endif

MoToTimer ledTimer,rampTimer;
uint8_t i =0;
//Creates a time for the lights to ramp up to speed & a goal value
uint16_t rampTime = 125, r = rampTime;

bool rampLightSpeed = 1;

//Higher the number the slower it updates
#define lowSpeed 30
#define highSpeed 1

uint8_t halfNum = ledNum/2;

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
    // take a reading and then map it to the high and low of the ring speeds.
    uint32_t avg= 0;
    for(uint8_t avgNum = 0; avgNum < 100; avgNum++)
    {
      uint16_t tempRead = analogRead(pot);
      avg += tempRead;
    }

    Serial.println(avg);
    uint16_t AvgTempRead = avg/100;
    Serial.print("Avg Pot:");
    Serial.println(AvgTempRead);

    uint16_t tempPos = map(AvgTempRead, 0,1024,3,24);
    //Constrain it in the values to prevent any accdental overflow
    tempPos = constrain(tempPos,3,24);
    return tempPos;

}

uint16_t stripPosistion()
{
    // take a reading and then map it to the high and low of the ring speeds.
    uint16_t tempRead = analogRead(pot);
    Serial.print("Pot: ");
    Serial.println(tempRead);
    uint16_t tempPos = map(tempRead, 0,1020,3,ledNum/2-1);
    //Constrain it in the values to prevent any accdental overflow
    tempPos = constrain(tempPos,0,ledNum/2);
    return tempPos;

}

//if the ring is active use this animation sequence
#ifdef ring
  void animationLight()
  {
    #ifdef small
      //this is the highest position to put the led to.
      uint8_t ledPos = ringSpeed();
      //Set to current position
      fill_gradient_RGB(ringLight,ledPos,CRGB::Green,CRGB::Red);
      FastLED.show();
      //clear and update again
      FastLED.clear();
      FastLED.show();
    #else

         if(!ledTimer.running())
      {
        i++;
        if(i==ledNum/4){i = 0;}
        quad1[i] = CRGB::RoyalBlue;
        quad2[i] = CRGB::RoyalBlue;
        quad3[i] = CRGB::RoyalBlue;
        quad4[i] = CRGB::RoyalBlue;
        ledTimer.setTime(50);
        fadeToBlackBy(ringLight,ledNum,55);
      }
      FastLED.show();
    #endif
  }
#endif

//if the strip is active use this animation sequence
#ifdef strip
  void animationLight()
  {
          //this is the highest position to put the led to.
      uint8_t ledPos = stripPosistion();
      Serial.print("Strip Value: ");
      Serial.println(ledPos);
      //Set to current position
      fill_gradient_RGB(ledStrip1,ledPos,CRGB::Green,CRGB::Red);
      for(uint8_t x=halfLed; x>=0; x--)
      { 
        // Serial.print("Strip1:");
        // Serial.print(x);
        // Serial.print(":");
        // Serial.print("Strip2:");
        // Serial.println(halfLed-x);       

        //Copy the order of strip1 in reverese and apply to strip2
        ledStrip2[x] = ledStrip1[halfLed-x];
        if(x==0){break;}
      }
      

      FastLED.show();
      //clear and update again
      FastLED.clear();
      FastLED.show();
  }
#endif

void lightOff()
{
    FastLED.clear();
    FastLED.show();
}

void lightTest()
{

  //quick setup test to check LEDs
  #ifdef strip
    fill_solid(ledStrip,ledNum,CRGB::Red);
    FastLED.show();
    delay(1000);
    fill_solid(ledStrip,ledNum,CRGB::Blue);
    FastLED.show();
    delay(1000);
    fill_solid(ledStrip,ledNum,CRGB::Green);
    FastLED.show();
    delay(1000);
  #else
    fill_solid(ringLight,ledNum,CRGB::Red);
    FastLED.show();
    delay(1000);
    fill_solid(ringLight,ledNum,CRGB::Blue);
    FastLED.show();
    delay(1000);
    fill_solid(ringLight,ledNum,CRGB::Green);
    FastLED.show();
    delay(1000);
  #endif
}