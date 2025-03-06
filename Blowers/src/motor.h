MoToTimer btnDelay, timeLimit;
bool motorOn;

#define timeLength 60000


void motor(uint16_t speed)
{   
    //turn on or off the fan & lights
    if(startBtn.isPressed() && !btnDelay.running())
    {
        motorOn = !motorOn;
        btnDelay.setTime(500);
        timeLimit.setTime(timeLength);
    }


    if(motorOn)
    {   
        #if !defined(controlledSpeed)
            digitalWrite(motorEn,HIGH);
            digitalWrite(motorPin, HIGH);    
        #else
            digitalWrite(motorEn,HIGH);
            analogWrite(motorPin,speed);
        #endif
        

        btnPWM.update(0);
        animationLight();

    }
    else
    {
        
        digitalWrite(motorEn,LOW);
        digitalWrite(motorPin, LOW);
        btnPWM.update(1);
        lightOff();
    }

    if(motorOn && !timeLimit.running() && !btnDelay.running())
    {
       motorOn = false;
    }
} 

uint16_t speedControl()
{
    uint16_t tempRead = analogRead(pot);
    uint16_t tempSpeed = map(tempRead, 0,1024,0,255);

    return tempSpeed;

}

