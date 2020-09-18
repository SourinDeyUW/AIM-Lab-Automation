#include "pcb.h"

PCB::PCB(int newPid, int newValue, int newTime, int newStart)
{
    pid = newPid;
    value = newValue;                                   //constructor for pcb class
    runTime = newTime;
    totalTime = newTime;
    startTime = newStart;

    priority = 0;                          //new process with priority 0 and quantum 1
    quantum = 1;
    timeSinceStart = 0;
}


PCB::PCB()
{
    
}


void PCB::updateRunTime()
{
    runTime--;                           // After running for a sec
}


void PCB::updatePriority()           // Updating priority after finishing quantum
{
    if(priority < 3)
    {
        priority++;
    }
   
    
}
void PCB::updateQuantum()
{
    if(priority == 0)
    {                              // Updating quantum according to their priority
        quantum = 1;
    }
    else if(priority == 1)
    {
        quantum = 2;
    }
    else if(priority == 2)
    {
        quantum = 4;
    }
    else if(priority == 3)
    {
        quantum = 8;
    }
}
void PCB::setValue(int newValue)           // Setting a new value for process
{
    value = newValue;
}

int PCB::getCPUTime()                      //return cpu time
{
    int cpuTime = totalTime - runTime;

    if(cpuTime > 0)
    {
        return cpuTime;
    }
    else
    {
        return 0;
    }
}


void PCB::updateTimeSinceStart()
{
    timeSinceStart++;
}


void PCB::updateQuantumRun()      // Updating quantum for running processs
{
    quantum--;
}

void PCB::updatePriorityBlocked()    // Updating priority after blocking a process
{
    if(priority > 0)
    {
        priority--;
    }
    if(priority==0)
    {
        priority=0;
    }
    
}