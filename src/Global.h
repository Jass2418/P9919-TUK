#include <TaskScheduler.h>
#include <Watchdog.h>
#include "Models/DbContext.h"
#include "Tasks/Tasks.h"

// Variables that can be used anywhere

// Database
extern DbContext db;
// Tasks & Task Manager
extern Scheduler ts;

extern Watchdog wd;