#ifndef DISPLAY7_H   /* Include guard */
#define DISPLAY7_H

#include "Arduino.h"
#include "LinkedList.h"
#define OUTPUT_ENABLED_MS 1
#define STROBE_ENABLE_MS 1
static const int segChar[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};

class Display7 {
    public :
        Display7(int sPin, int dPin, int cPin, int oPin, int bright = 254);
        void begin();
        void setDisplay(int num, int zeroPosition = 0, bool isShown = true);
        void setDisplayFloat(float num, int decimalPosition = 2, int zeroPosition = 0, bool isShown = true);
        void setDisplayRaw(int value, bool isShown = true);
        void setDigit(int value, bool hasDot = false, bool isShown = true);
        void setBrightness(int value);
        int getBrightness();
        void turnOn();
        void turnOff();
        void setStatus(bool isOn);
        void show();
        void clear();
    private :
        int _strobePin;
        int _dataPin;
        int _clockPin;
        int _outputPin;
        int _outputPinHelper;
        int _bright;
        bool _isOn;
        LinkedList<int> digits = LinkedList<int>();
};

class DisplaySymbol
{
    public:
        static int empty;
        static int letterC;
        static int letterF;
        static int degree;
        static int dot;
        static int guion;
        static int clusterRed;
        static int clusterGreen;
        static int clusterYellow;
};

class DisplayCluster
{
private:
    /* data */
public:
    static int off;
    static int red;
    static int green;
    static int yellow;
};

#endif