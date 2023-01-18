#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H
#include <Button.h>
#include <ResponsiveAnalogRead.h>
#include "Global.h"

#define MIN_V_ANALOG 0
#define MAX_V_ANALOG 1023

#define MIN_V_PROD 0
#define MAX_V_PROD 999999

#define MIN_V_VEL 0
#define MAX_V_VEL 700

#define MIN_V_W 0.0
#define MAX_V_WEIGHT 99.99

#define UPDATE_PROD 1

class SensorTask {
    public:
        static void setup(){
            startStopBtn.begin();
            resetBtn.begin();
            lastTime = now();
        };
        static void loop(){
            // Buttons
            if(resetBtn.pressed()){
                db.production = 0;
            }
                
            if(startStopBtn.pressed()){
                db.isProductionActive = !db.isProductionActive;
            }
            // Analog Sensors
            velocitySensor.update();
            weightSensor.update();

            db.tonHours = map(weightSensor.getValue(),MIN_V_ANALOG,MAX_V_ANALOG,MIN_V_W,MAX_V_WEIGHT);
            db.velocity = map(velocitySensor.getValue(),MIN_V_ANALOG,MAX_V_ANALOG,MIN_V_VEL,MAX_V_VEL);
            if(numberOfMinutes(now() - lastTime) >= UPDATE_PROD && db.isProductionActive){
                db.production += db.velocity;
                lastTime = now();
            }
        };
    private:
        static Button startStopBtn;
        static Button resetBtn;
        static ResponsiveAnalogRead velocitySensor;
        static ResponsiveAnalogRead weightSensor;
        static time_t lastTime;
};

Button SensorTask::startStopBtn(8);
Button SensorTask::resetBtn(6);
ResponsiveAnalogRead SensorTask::velocitySensor(A0,false);
ResponsiveAnalogRead SensorTask::weightSensor(A1,false);
time_t SensorTask::lastTime = 0;
#endif