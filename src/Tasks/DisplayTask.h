#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H
#include <Display7.h>
#include "Global.h"
#define UPDATE_DISPLAY_SEC 1
class DisplayTask {
    public:
        static void setup(){
            display.begin();
            display.setBrightness(40);
            lastTime = now();
        };
        static void loop(){
            if(numberOfSeconds(lastTime - now()) > UPDATE_DISPLAY_SEC ){
                display.clear();
                
                display.setDisplay(db.velocity,4);
                display.setDisplayFloat(db.tonHours,2,2);
                display.setDisplay(db.production,6);
                display.setDisplay(db.velocity,4);
                display.setDisplayFloat(db.tonHours,2,2);
                display.setDisplay(db.production,6);
                
                display.show();
            }
        };
    private:
        static Display7 display;
        static time_t lastTime;
};

Display7 DisplayTask::display(4,5,7,9); // Strobe,Data,Clock,OE

time_t DisplayTask::lastTime = 0;
#endif