#define pot A0
#define btnIn 7
#define btnLight 10
#define dataPin 4
#define motorPin 11
#define motorEn 12

//Comment out what ring is being used.
#define large
//#define small

//Comment out what strip is being used
//#define strip
#define ring


Bounce2::Button startBtn = Bounce2::Button();
Pulse btnPWM;

void setPins()
{
    startBtn.attach(btnIn,INPUT_PULLUP);
    startBtn.setPressedState(LOW);
    startBtn.interval(5);
    btnPWM.attach(btnLight);

    pinMode(pot, INPUT);
    pinMode(btnLight,OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(motorEn, OUTPUT);
    pinMode(13,OUTPUT);
    //set output pins low/off
    digitalWrite(btnLight, LOW);
    digitalWrite(motorPin, LOW);
    digitalWrite(motorEn,HIGH);


}