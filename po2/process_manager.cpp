#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include "pcb.h"
#include "queue_array.h"

using namespace std;

int NoRid = 3;

QueueArray<int> blockedState[3] = { QueueArray<int> (4), QueueArray<int> (4), QueueArray<int> (4) };

QueueArray<int> readyState(4);          

vector<PCB> pcbTable(100);

vector<int> Ind;

int TIME=0;

int runIndex=-1;                 //index of currently running process in pcb table which we initialize with -1(nothing running)


bool isBlocked(int tableIndex)               // Checking a process to see if it is blocked or not
{
    for(int i = 0; i < 3; i++)                      // Going through all blocked states
    {
        for(int j = 0; j < 4; j++)                 // Going trhough all priorities
        {
            int* array =  blockedState[i].Qstate(j);
            int size = blockedState[i].Qsize(j);

            for(int k = 0; k < size; k++)             // Finding that specific process
            {
                if(tableIndex == array[k])
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void schduler()       
{
    if(runIndex == -1)              //check if any process is running
    {
        if(readyState.QAsize()!=0)        //check if we have any process in ready state
        {
            int tableIndex = readyState.Dequeue();   // Getting process pid with highest priority

            runIndex = tableIndex;  
        }
    }    
}

void reporter()
{   

    cout << "*****************************************************" << endl;

    cout << "The current system state is as follows:" << endl;

    cout << "*****************************************************" << endl;

    cout << "CURRENT TIME:" << TIME << endl;

    cout << "RUNNING PROCESS:";

    string header = "PID\tPriority\tValue\tStart Time\tTotal CPU time";
    cout<< endl;

    if(runIndex != -1)
    {
        cout << endl;
        cout << header << endl;
        cout << pcbTable[runIndex].pid<<"\t"<<pcbTable[runIndex].priority << "\t\t" << pcbTable[runIndex].value << "\t\t" <<
        pcbTable[runIndex].startTime << "\t\t" << pcbTable[runIndex].getCPUTime() << endl;
        cout << endl;
    }
    else
    {
        cout << " empty" << endl;
    }
    
    cout << "BLOCKED PROCESSES:" << endl;

    for(int i = 0; i < NoRid; i++)         //print all blocled process
    {
        cout << "Queue of processes Blocked for resource " << i ;
        if(blockedState[i].QAsize()!=0)                          //proceed printing if blocked state is not empty
        {
            cout << ":" << endl;
            cout << header << endl;

            for(int j = 0; j < 4; j++)                   
            {
                int* array = blockedState[i].Qstate(j);
                int size = blockedState[i].Qsize(j);
                if(size > 0)
                {
                    for(int k = 0; k < size; k++)
                    {
                        cout << pcbTable[array[k]].pid << "\t" << pcbTable[array[k]].priority << "\t\t" << pcbTable[array[k]].value << 
                        "\t" << pcbTable[array[k]].startTime << "\t\t" << pcbTable[array[k]].getCPUTime() << endl;
                    }
                }
            }
        }
        else
        {
            cout << " is empty" << endl;
        }
    }

    cout << "PROCESSES READY TO EXECUTE:" << endl;             // Printing ready state processes
    for(int j = 0; j < 4; j++)
    {
        cout << "Queue of processes with priority " << j;

        int* array = readyState.Qstate(j);                    // Getting readystate pid to an array
        int size = readyState.Qsize(j);
        if(size>0)
        {
            cout << " :" << endl;
            cout << header << endl;

            for(int k = 0; k < size; k++)
            {
                cout << pcbTable[array[k]].pid << "\t" << pcbTable[array[k]].priority <<
                 "\t\t" << pcbTable[array[k]].value << "\t" << pcbTable[array[k]].startTime<< 
                 "\t\t" << pcbTable[array[k]].getCPUTime() << endl;
            }
        }
        else
        {
            cout << " is empty" << endl;
        }
    }
    
    cout << "*****************************************************" << endl;
    sleep(2);

}

void updateTime()                    //updates TIME, quantum and run time
{
    TIME++;

    for(int i = 0; i < Ind.size(); i++)        //update time since start for all processes
    {
        bool isInside = false;
        for(int j = 0; j < 4; j++)
        {
            int* array =  readyState.Qstate(j);
            int size = readyState.Qsize(j);

            for(int k = 0; k < size; k++)                     //find table index in ready states
            {
                if(Ind[i] == array[k])
                {
                    isInside = true;
                }
            }
        }
      
        if(isBlocked(Ind[i]) || runIndex == Ind[i] || isInside)       // If process is in blockstate, run state or ready state
        {
            pcbTable[Ind[i]].updateTimeSinceStart();
        }
    }

    if(runIndex != -1)                    // If something running
    {
        pcbTable[runIndex].updateRunTime();          // Updating run time and quantum of process

        pcbTable[runIndex].updateQuantumRun();         // updating quantum
        
        int oldRunIndex;

        if(pcbTable[runIndex].runTime == 0)            // Pulling process out if it is finished 
        {
            oldRunIndex = runIndex;
            runIndex = -1;
        }


        else if(pcbTable[runIndex].quantum == 0 && pcbTable[runIndex].runTime != 0)        // If quantum finished but process didn't finish, 
        {                                                                                  // update the priority and quantum
            oldRunIndex = runIndex;
            runIndex = -1;
            
            pcbTable[oldRunIndex].updatePriority();
            pcbTable[oldRunIndex].updateQuantum();

            readyState.Enqueue(oldRunIndex, pcbTable[oldRunIndex].priority);     // Putting the process in ready state
        }
    }
}


#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
    int i, max = 100;
    int mcpipe2[2];
    char command;

    int pid, value, runTime, rid, num;                  // Command Arguements
    char cmd;
    
    mcpipe2[0] = atoi(argv[1]);             //convert the parameters into the address for the pipe
    mcpipe2[1] = atoi(argv[2]);

    while (true) 
    {
        read(mcpipe2[0], &command, sizeof(char));    //read a character from the pipe

        if (command == 'S')
        {
            
            read(mcpipe2[READ_END], (int *)&pid, sizeof(pid));
            read(mcpipe2[READ_END], (int *)&value, sizeof(value));                  //Creating a new process with arguments from commander
            read(mcpipe2[READ_END], (int *)&runTime, sizeof(runTime));
            
            PCB process = PCB(pid, value, runTime, TIME);
            pcbTable[pid] = process;                                                    //pushing the new process into the pcb table
            
            Ind.push_back(pid);

            readyState.Enqueue(pid, 0);                                               //putting the process into ready queue
           

            schduler();

        } 
        else if (command == 'B') 
        {
            read(mcpipe2[READ_END], (int *)&rid, sizeof(rid));

            if(rid >= 0 && rid <= 2 && runIndex != -1)
            {
                int blockedIndx = runIndex;
                runIndex = -1;                                            // changing the index so we can stop the process
                
                pcbTable[blockedIndx].updatePriorityBlocked();            // Changing priority and quantum after blocking the process 
                pcbTable[blockedIndx].updateQuantum();

                int priority = pcbTable[blockedIndx].priority;            // Getting new priority and save it in block state

                blockedState[rid].Enqueue(blockedIndx, priority);              
  

                schduler();
            }
        }
        else if(command=='U')
        {
            read(mcpipe2[READ_END], (int *)&rid, sizeof(rid));

            if(rid >= 0 && rid <= 2)
            {
                int unblockedIndx = blockedState[rid].Dequeue();                         // Gettubg pid of process with highest priority
               
                readyState.Enqueue(unblockedIndx, pcbTable[unblockedIndx].priority);      // Push the process in to ready state

                schduler();         
            }
            else
            {
                cout << "not valid rid!" << endl;               // rid is not 0,1 or 2
            }
        }
        else if (command =='Q') 
        {
            updateTime();                                  //Time should be updated
            schduler();

        }
        else if(command=='C')
        {
            read(mcpipe2[READ_END], (int *)&cmd, sizeof(char));       // Reading arguments 
            read(mcpipe2[READ_END], (int *)&num, sizeof(int));
            int newValue;
            
            if(runIndex != -1)           
            {                                                  // Make sure there is a process running

                if(cmd == 'A')
                {                                                                                   
                    newValue = pcbTable[runIndex].value + num;
                    pcbTable[runIndex].setValue(newValue);
                }
                else if(cmd == 'S')
                {                                                       // changing the value according to the command

                    newValue = pcbTable[runIndex].value - num;
                    pcbTable[runIndex].setValue(newValue);
                }
                else if(cmd == 'M')
                {
                    newValue = pcbTable[runIndex].value * num;
                    pcbTable[runIndex].setValue(newValue);
                }
                else if(cmd == 'D')
                {
                    newValue = pcbTable[runIndex].value / num;
                    pcbTable[runIndex].setValue(newValue);
                }
                else 
                {
                    cout << "Command is invalid" << endl;
                }
            }

            updateTime();                       // Time should be updated after C command - it will incemented by 1 after Q and C
            schduler();
        }
        else if(command=='P')
        {
            pid_t pid = fork();                 //fork a reporter process
            if(pid < 0)
            {
                perror("Fork Failed");
                return 1;
            }
            else if (pid == 0)                 //Create child process 
            {
                reporter();
                exit(1);
            }
            else
            {
                wait(NULL);                 //parent process

            }
        }
        else if(command=='T')
        {
            
            int total = 0;
            for(int i = 0; i < Ind.size(); i++)
            {
                total += pcbTable[Ind[i]].timeSinceStart;
            }                                                           // Calculating TurnAround time
            double turnAround = (double) total / (double) Ind.size();

            cout << "The average turnAround Time: " << turnAround << endl;            
            
            return 0;
        }

    }

    close(mcpipe2[0]);
    close(mcpipe2[1]);            //close the pipe 
    return 0;
}
