#ifndef WATCHDOG_H
#define WATCHDOG_H
class Watchdog
{
public:
    Watchdog();
    ~Watchdog();
    void setup(int wTimer);
    void reset();
    void disable();
    void enable(int wTimer);

    bool isEnabled();
    bool isRebootNeeded();
    void reboot();
private:
    bool _isEnabled;
    bool _wantsToReboot;
};
#endif
