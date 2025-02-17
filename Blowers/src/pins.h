#define pot A0
#define btnIn 1
#define btnLight 2
#define dataPin 3
#define motorPin 4
#define motorEn 5

#define small

Bounce2::Button startBtn = Bounce2::Button();


void setPins()
{
    startBtn.attach(btnIn,INPUT_PULLUP);
    startBtn.setPressedState(LOW);
    startBtn.interval(5);

    pinMode(pot, INPUT);
    pinMode(btnLight,OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(motorEn, OUTPUT);

    //set output pins low/off
    digitalWrite(btnLight, LOW);
    digitalWrite(motorPin, LOW);
    digitalWrite(motorEn,LOW);


}