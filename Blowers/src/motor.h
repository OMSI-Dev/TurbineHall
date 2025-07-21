MoToTimer btnDelay, timeLimit;
bool motorOn;

//Defines how long the game should run in ms
#define timeLength 60000

void updateIndicators(bool motorOn)
{
    if(motorOn)
    {   
        //Turn off start LED
        startBtnPWM.update(0);
        #ifdef hasStop
        //Turn on stop LED
        stopBtnPWM.update(1);
        #endif
        //Change rate and update heartbeat
        heartBeat.setRate(10);
        heartBeat.update(1);
    }
    else
    {
        startBtnPWM.update(1);
        #ifdef hasStop
        stopBtnPWM.update(0);
        #endif
        heartBeat.setRate(200);
        heartBeat.update(1);
        rampLightSpeed = 1;
    }
}

void motor(uint16_t speed)
{   

    //Check to see if motor is already running and if it should allow start button
    if(!motorOn)
    {    
        if(startBtn.isPressed() && !btnDelay.running())
        {
            //set that the motor is on
            motorOn = true;
            //lock out buttons for at least 1 second
            btnDelay.setTime(1000);
            //start the game timer
            timeLimit.setTime(timeLength);
        }
    }

    //Check if the motor is on and if it has variable speed control
    //Horizontal blowers do not have variable speeds.
    if(motorOn)
    {   
        #if !defined(controlledSpeed)
            speed = 255;
            //Logic of optoisolator is flipped of high/low
            digitalWrite(motorEn,LOW);
            digitalWrite(motorPin, LOW);    
        #else
            digitalWrite(motorEn,HIGH);
            analogWrite(motorPin,speed);
        #endif
        
        //update button lights
        updateIndicators(motorOn);
        //update light animation
        animationLight();
    }
    else
    {
        //set motor to to off
        digitalWrite(motorEn,HIGH);
        digitalWrite(motorPin, HIGH);
        //Update button lights
        updateIndicators(motorOn);
        //Set neoPixels to off
        lightOff();
    }

    #ifdef hasStop
        //have the timeout reset or if the stop button was pressed
        if((motorOn && !timeLimit.running()) || (stopBtn.isPressed() && !btnDelay.running()))
        {
        motorOn = false;
        btnDelay.setTime(1000);
        }
    #else
        if((motorOn && !timeLimit.running()))
        {
        motorOn = false;
        btnDelay.setTime(1000);
        }    
    #endif

} 

uint16_t speedControl()
{  
    //read the postion of the potentionmeter and remap it to a PWM value
    uint16_t tempRead = analogRead(pot);
    uint16_t tempSpeed = map(tempRead, 0,1024,0,255);
    return tempSpeed;

}
