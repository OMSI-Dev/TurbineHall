

//this sets the size of the array
//and if it is a ring or strip
//Small ring is around potentionmeter
//larg ring is around blower
//strips are in shake tables

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
//Creates a time for the lights to ramp up to speed & a goal value
uint16_t rampTime = 125, r = rampTime;

bool rampLightSpeed = 1;

//Higher the number the slower it updates
#define lowSpeed 30
#define highSpeed 1

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
    uint16_t tempRead = analogRead(pot);
    uint16_t tempPos = map(tempRead, 0,1024,lowSpeed,highSpeed);
    Serial.print("Pot: ");
    Serial.println(tempRead);
    //Constrain it in the values to prevent any accdental overflow
    tempPos = constrain(tempPos,lowSpeed,highSpeed);
    Serial.print("tempPos: ");
    Serial.println(tempPos);
    return tempPos;

}

//if the ring is active use this animation sequence
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

//if the strip is active use this animation sequence
#ifdef strip
  void animationLight()
  {
      //if rampspeed is off, use a timer based on the pot position
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
      //if rampspeed is on, update the timers pace until it reaches full speed  
      else{
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
              //Reset the ramp vars
              r=rampTime;
              //turn off ramping
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
    FastLED.clear();
    FastLED.show();
}
