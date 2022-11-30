#include "Watchdog.h"
#include <avr/wdt.h>

#define WDT_15_MS 0
#define WDT_30_MS 1
#define WDT_60_MS 2
#define WDT_120_MS 3
#define WDT_250_MS 4
#define WDT_500_MS 5
#define WDT_1_S 6
#define WDT_2_S 7
#define WDT_4_S 8
#define WDT_8_S 9

Watchdog::Watchdog()
{
    _isEnabled = false;
}

Watchdog::~Watchdog()
{
    
}

void Watchdog::setup(int wTimer){
    wdt_disable();
    wdt_enable(wTimer);
    _isEnabled = true;
}

void Watchdog::reset(){
    wdt_reset();
}

void Watchdog::disable(){
    wdt_disable();
    _isEnabled = false;
}

void Watchdog::enable(int wTimer){
    wdt_enable(wTimer);
    _isEnabled = true;
}

bool Watchdog::isEnabled(){
    return _isEnabled;
}

// Functions for resetting the system

bool Watchdog::isRebootNeeded(){
    return _wantsToReboot;
}

void Watchdog::reboot(){
    _wantsToReboot = true;
}