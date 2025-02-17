MoToTimer testTimer;
uint8_t i=0;

void rampMotor()
{
    if(!testTimer.running())
    {
        analogWrite(motorPin,i);
        Serial.println(i);
        i++;
        testTimer.setTime(100);
    }

    if(i>255){i=0; testTimer.setTime(5000);}

} 