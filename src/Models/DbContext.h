#ifndef DBCONTEXT_H
#define DBCONTEXT_H

#include <DbSetEEPROM.h>
#include <Arduino.h>
#include <TimeLib.h>
class DbContext {
    public:
        // Runtime Registers (Non-volatile memory)
        byte deviceId;
        uint32_t velocity;
        float tonHours;
        uint32_t production;
        bool isProductionActive;
        bool aRebootIsNeeded;
        time_t startTime;
        // EEPROM Registers (Volatile memory)
        DbSetEEPROM<byte> deviceIdEEPROM = DbSetEEPROM<byte>(1);
        DbSetEEPROM<uint32_t> productionMEM = DbSetEEPROM<uint32_t>(1,deviceIdEEPROM.lastPosition());
};

#endif