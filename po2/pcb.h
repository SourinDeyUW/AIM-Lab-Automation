#ifndef PCB_H
#define PCB_H

class PCB
{
    public:
        PCB(int, int, int, int);
        PCB();
        void updateRunTime();
        void updatePriority();
        void updateQuantum();
        void updateQuantumRun();
        void setValue(int);
        int getCPUTime();
        void updateTimeSinceStart();
        void updatePriorityBlocked();

        int timeSinceStart;
        int totalTime;
        int pid;
        int priority;
        int value;
        int startTime;
        int runTime;
        int cpuTime;
        int quantum;
};

#endif
