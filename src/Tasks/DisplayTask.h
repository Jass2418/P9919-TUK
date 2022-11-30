#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H
#include <Display7.h>
#include "Global.h"
#define UPDATE_DISPLAY_SEC 1
class DisplayTask {
    public:
        static void setup(){
            display.begin();
            display.setBrightness(254);
            display2.begin();
            display2.setBrightness(254);
            lastTime = now();
        };
        static void loop(){
            if(numberOfSeconds(lastTime - now()) > UPDATE_DISPLAY_SEC ){
                display.clear();
                display2.clear();

                display.setDisplay(db.velocity,3);
                display.setDisplayFloat(db.tonHours,2,2);
                display.setDisplay(db.production,6);

                display2.setDisplay(db.velocity,3);
                display2.setDisplayFloat(db.tonHours,2,2);
                display2.setDisplay(db.production,6);

                display.show();
                display2.show();
            }
        };
    private:
        static Display7 display;
        static Display7 display2;
        static time_t lastTime;
};

Display7 DisplayTask::display(4,5,7,9); // Strobe,Data,Clock,OE
Display7 DisplayTask::display2(4,5,7,9); // Strobe,Data,Clock,OE

time_t DisplayTask::lastTime = 0;
#endif