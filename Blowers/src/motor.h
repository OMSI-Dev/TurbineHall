MoToTimer btnDelay, timeLimit;
bool motorOn;

#define timeLength 60000

void updateIndicators(bool motorOn)
{
    if(motorOn)
    {
        startBtnPWM.update(0);
        stopBtnPWM.update(1);
        heartBeat.setRate(10);
        heartBeat.update(1);
    }
    else
    {
        startBtnPWM.update(1);
        stopBtnPWM.update(0);
        heartBeat.setRate(100);
        heartBeat.update(1);
        rampLightSpeed = 1;
    }
}

void motor(uint16_t speed)
{   
    //turn on or off the fan & lights
    if(!motorOn)
    {    
    if(startBtn.isPressed() && !btnDelay.running())
    {
        motorOn = true;
        btnDelay.setTime(1000);
        timeLimit.setTime(timeLength);
    }
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
        

        updateIndicators(1);

        animationLight();
    }
    else
    {
        
        digitalWrite(motorEn,LOW);
        digitalWrite(motorPin, LOW);
        updateIndicators(0);
        lightOff();
    }

    if((motorOn && !timeLimit.running() && !btnDelay.running()) || (stopBtn.isPressed() && !btnDelay.running()))
    {
       motorOn = false;
       btnDelay.setTime(1000);
    }
} 

uint16_t speedControl()
{
    uint16_t tempRead = analogRead(pot);
    uint16_t tempSpeed = map(tempRead, 0,1024,0,255);

    return tempSpeed;

}
