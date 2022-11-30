#include "Display7.h"
#include "LinkedList.h"
// AVR CODE
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        #include "PWMFreak.h"
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
        #include "PWMFreak.h"
#endif
Display7::Display7(int sPin, int dPin, int cPin, int oPin, int bright){
    _strobePin = sPin;
    _dataPin = dPin;
    _clockPin = cPin;
    _outputPin = oPin;
    begin();
    setBrightness(bright);
}

void Display7::begin(){
    pinMode(_strobePin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    _isOn = true;
    // Arduino Uno Code
    #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
        setPwmFrequency(_outputPin, 1);
    // Arduino Mega Code
    #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
        setPwmFrequency(_outputPin, 1);
    // Other Boards
    #else
        pinMode(_outputPin, OUTPUT);
    #endif
}

void Display7::setDisplay(int num, int zeroPosition, bool isShown){
    if(num == 0)
        digits.add(0);
    while(num > 0) //do till num greater than  0
    {
        int mod = num % 10;  //split last digit from number
        digits.add(mod);
        num = num / 10;    //divide num by 10. num /= 10 also a valid one 
    }
    while (digits.size() < zeroPosition)
        digits.add(0);

    while (digits.size() > 0)
        setDigit(digits.pop(),false,isShown);
}

void Display7::setDisplayFloat(float num, int decimalPosition, int zeroPosition, bool isShown){
    for (int i = 0; i < decimalPosition; i++)
        num = num * 10;
    if(num == 0)
        digits.add(0);
    while((int)num > 0) //do till num greater than  0
    {
        int mod = (int) num % 10;  //split last digit from number
        digits.add(mod);
        num = num / 10;    //divide num by 10. num /= 10 also a valid one 
    }
    // Set zero if availables position
    while (digits.size() < (zeroPosition + decimalPosition))
        digits.add(0);
    
    while (digits.size() > 0)
    {
        if((digits.size() - 1) == decimalPosition)
            setDigit(digits.pop(),true,isShown);
        else
            setDigit(digits.pop(),false,isShown);
    }
}

void Display7::setDisplayRaw(int value, bool isShown){
    // digitalWrite(_strobePin, LOW);
    // delayMicroseconds(STROBE_ENABLE_MS);
    shiftOut(_dataPin, _clockPin, MSBFIRST,value);  
    //set strobe pin high to stop storing bits
    // digitalWrite(_strobePin, HIGH);
    // delayMicroseconds(STROBE_ENABLE_MS);
}

void Display7::setBrightness(int value){
    if(value > 254)
        value = 254;
    else if (value < 0)
        value = 0;
    this->_bright = value;
    analogWrite(_outputPin, _isOn ? _bright : LOW);
}

int Display7::getBrightness(){
    return this->_bright;
}

void Display7::setDigit(int value, bool hasDot, bool isShown){
    if(value < 0 || value > 9)
        value = 0;
    // digitalWrite(_strobePin, LOW);
    // delayMicroseconds(STROBE_ENABLE_MS);
    shiftOut(_dataPin, _clockPin, MSBFIRST,
     isShown ? (segChar[value] + (hasDot ? DisplaySymbol::dot : 0)) : 0);  
    //set strobe pin high to stop storing bits
    // digitalWrite(_strobePin, HIGH);
    // delayMicroseconds(STROBE_ENABLE_MS);
}

void Display7::turnOn(){
    _isOn = true;
}

void Display7::turnOff(){
    _isOn = false;
}

void Display7::setStatus(bool isOn){
    _isOn = isOn;
}

void Display7::show(){
    // analogWrite(_outputPin, _isOn ? _bright : LOW);
    digitalWrite(_strobePin, HIGH);
    delayMicroseconds(STROBE_ENABLE_MS);
}

void Display7::clear(){
    digitalWrite(_strobePin, LOW);
    delayMicroseconds(STROBE_ENABLE_MS);
    // analogWrite(_outputPin, LOW);
}

// Display Symbols
int DisplaySymbol::empty = 0;
int DisplaySymbol::degree = 99;
int DisplaySymbol::letterC = 57;
int DisplaySymbol::letterF = 113;
int DisplaySymbol::dot = 128;
int DisplaySymbol::guion = 64;

// Display Cluster
int DisplayCluster::off = 0;
int DisplayCluster::red = 128;
int DisplayCluster::green = 32;
int DisplayCluster::yellow = 64;
