#ifndef PROCESSSCHEDULECONTROLLER_H
#define PROCESSSCHEDULECONTROLLER_H

#include <string>
#include <iostream>
#include "ProcessControlBlock.h"
#include "ProcessQueue.h"

class ProcessScheduleController
{
private:
    ProcessQueue scheduleQueue;

public:
    ProcessScheduleController();

    void addProcess(ProcessControlBlock* pcb);

    void popAndRun ();

    bool haveProcess();

    void startSchedule();

    ~ProcessScheduleController();
};


#endif // PROCESSSCHEDULECONTROLLER_H
