#ifndef SYSTEM_TASK_H
#define SYSTEM_TASK_H
#include "Global.h"
#include <TimeLib.h>
#include <avr/wdt.h>
#define DEFAULT_TIME 1357041600
#define RESET_TIME_MINS 200

class SystemTask {
    public:
        static void setup(){
            Serial.begin(9600);
            setTime(DEFAULT_TIME);
            db.startTime = now();
            db.isProductionActive = true;
        };
        static void loop(){
            // Reboot with Flag
            if(db.aRebootIsNeeded)
                reboot();
            
            // Reboot by no usage
            if(numberOfMinutes(now() - db.startTime) >= 
            RESET_TIME_MINS){
                reboot();
            }
        };
    private:
        static void reboot(){
            //wd.reboot();
        }
};
#endif