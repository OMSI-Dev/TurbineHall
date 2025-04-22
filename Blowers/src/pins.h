#define pot A0
#define startBtnIn 7
#define startBtnLight 10
#define stopBtnIn 5
#define stopBtnLight 9
#define dataPin 4
#define motorPin 11
#define motorEn 12

//Comment out if strip or ring is being used
#define strip
//#define ring

//Comment out depening on larg or small ring
#if ring
    //#define large
    #define small
#endif

//Comment out if motors just turn on
#define controlledSpeed

//comment out if not using stop button
//used to set pinMode
#define hasStop

//used for RGBW Emulation in fastLED
//Do not change.
Rgbw rgbw = Rgbw(
    kRGBWDefaultColorTemp,
    kRGBWExactColors,      // Mode
    W3                     // W-placement
);

//If the WS2812 gives an error, you can ignore it, it is correct and will compile
typedef WS2812<dataPin, RGB> ControllerT;  // RGB mode must be RGB, no re-ordering allowed. (per FastLED)
static RGBWEmulatedController<ControllerT, GRB> rgbwEmu(rgbw);

//Bounce objects
Bounce2::Button startBtn = Bounce2::Button();
Pulse startBtnPWM;
#ifdef hasStop
    Bounce2::Button stopBtn = Bounce2::Button();
    Pulse stopBtnPWM;
#endif

//used for the LED on pin13, for trouble shooting
Pulse heartBeat;

void setPins()
{
    startBtn.attach(startBtnIn,INPUT_PULLUP);
    startBtn.setPressedState(LOW);
    startBtn.interval(5);
    //attach to pulse objects
    startBtnPWM.attach(startBtnLight);

    //only attach if the stop button is being used
    //Used on the shake tables but not on the blowers
    #ifdef hasStop
        stopBtn.attach(stopBtnIn,INPUT_PULLUP);
        stopBtn.setPressedState(LOW);
        stopBtn.interval(5);
        stopBtnPWM.attach(stopBtnLight);
    #endif

    //used to debug
    heartBeat.attach(13);

    //Set all pins connected just to prevent floating
    pinMode(pot, INPUT);
    pinMode(stopBtnLight,OUTPUT);
    pinMode(startBtnLight,OUTPUT);
    pinMode(motorPin, OUTPUT);
    pinMode(motorEn, OUTPUT);
    pinMode(13,OUTPUT);

    //set output pins low/off
    digitalWrite(startBtnLight, LOW);
    digitalWrite(stopBtnLight, LOW);
    digitalWrite(motorPin, LOW);
    digitalWrite(motorEn,LOW);

}