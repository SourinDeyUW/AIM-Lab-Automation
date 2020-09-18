#include <iostream>
#include <fstream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

#define READ_END 0
#define WRITE_END 1


int main()
{
    int i, c1, stat;

    int mcpipe1[2], status;                 //mcpipe going to be the pipe

    char mc0[10], mc1[10];                  //to pass the pipe address to the child process


    if ((c1 = pipe(mcpipe1)))                //Create a pipe for master and a child process
    {
        perror("unable to create the pipe");           // A condition to know if pipe was unsuccesful
        exit(1);
    }


    sprintf(mc0, "%d", mcpipe1[READ_END]);       //create a string value to pass the child process that is the address of pipe
    sprintf(mc1, "%d", mcpipe1[WRITE_END]);


    if ((c1 = fork()) == -1)                 // Create the first child
    {
        perror("unable to fork child");
        exit(1);
    }
    else if (c1 == 0)
    {


        execl("process_manager", "process_manager", mc0, mc1, NULL);  // Pass the pipe information as the parameters

        exit(1);
    }

        close(mcpipe1[READ_END]);       // Close read side of the pipe



    char command;     			// Command character

    int pid, value, run_time;
    int rid, num;               	// Commands variables
    char cmd;

    while(command != 'T')
	{

	 cin >> command; 		// Read command from input

	write(mcpipe1[WRITE_END], (char *)&command, sizeof(char));    // Write command to child


        if(command=='S')
        {
            cin >> pid;
            cin >> value;
            cin >> run_time;

            write(mcpipe1[WRITE_END], (int *)&pid, sizeof(int));
            write(mcpipe1[WRITE_END], (int *)&value, sizeof(int));
            write(mcpipe1[WRITE_END], (int *)&run_time, sizeof(int));
        }

        else if(command=='B')
        {
            cin >> rid;

            write(mcpipe1[WRITE_END], (int *)&rid, sizeof(int));

        }

        else if(command=='U')
        {

            cin >> rid;


            write(mcpipe1[WRITE_END], (int *)&rid, sizeof(int));

        }

        else if(command=='C')
        {
            cin >> cmd;

            cin >> num;

            write(mcpipe1[WRITE_END], (int *)&cmd, sizeof(char));
            write(mcpipe1[WRITE_END], (int *)&num, sizeof(int));
        }
        else if(command=='P')
        {

        }


    }

       write(mcpipe1[WRITE_END], (char *)&command, sizeof(char));    //T command


       close(mcpipe1[WRITE_END]);                  //close the write side of pipe

    wait(&status);                              // Wait for child and get its status
    exit(0);
}
