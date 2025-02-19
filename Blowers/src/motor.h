MoToTimer btnDelay, timeLimit;
bool motorOn;

#define timeLength 60000

void motor()
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
        digitalWrite(motorEn,HIGH);
        digitalWrite(motorPin, HIGH);
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