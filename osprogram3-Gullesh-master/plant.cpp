
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <semaphore.h>
#include <mutex>


using namespace std;

sem_t callDesk, callTech, fixed, moretechs;             // defining semaphores and mutex

mutex clIdLock, tchIds,tchaval;

int clId=0;
int tchId=0;
int tchavail=0;         //client Id starting

void helpDesk(){               // Help desk

    printf("help Desk starting.\n");

    while(true){
        
        printf("help Desk is waiting to recieve a call.\n");

        sem_wait(&callDesk);

        printf("Help desk got a call, and is gonna call Tech.\n");

        sem_post(&callTech);
    }
}

void client(){

    int i,id, t;
	
	clIdLock.lock();
		id = clId;
		clId++;
	clIdLock.unlock();

    printf("client %d started.\n", id);
    
    while(true){

        t = (int)rand() % 10;
        printf("client %d doing something useless for %d seconds.\n", id,t);
        sleep(t);

        printf("client %d broke something and will call help Desk right now.\n", id);
        sem_post(&callDesk);

        printf("client %d is waiting for tech to solve the problem.\n", id);

        sem_wait(&fixed);
    }
}

void tech(){

    int i,id, t;
	
	tchIds.lock();
		id = tchId;
		tchId++;
	tchIds.unlock();

    printf("plant tech %d started.\n", id);

    while(true){

        t = (int)rand() % 10;             // Having coffee and fun
        printf("tech %d having some coffee for %d seconds and doesn't care about help call.\n", id,t);
        sleep(t);

        tchaval.lock();
		tchavail++;
	    tchaval.unlock();

        if(tchavail==3){

             sem_wait(&callTech);  // wait for a call from help Desk
             tchavail-=3;

            for(i=0; i < 2; i++){
				sem_post(&moretechs);
			}
         t = (int)rand() % 10;             // fixing problem by techs in amount of time
         printf("techs %d fixing problem with help of other 2 techs in %d seconds.\n", id,t);
         sleep(t);

         sem_post(&fixed);
            
        }

        else{

            printf("tech %d waits more techs to be available.\n", id);

            sem_wait(&moretechs);
        }

    }
}



int main(int argc, char* argv[]){

	int i;

    // threads defining
	thread clients[2];
	thread helpDsk;
	thread techs[5];

	srand((unsigned)time(0));

	// Initialize semaphores
	sem_init(&fixed, 0, 0);
	sem_init(&callDesk, 0, 0);
	sem_init(&callTech, 0, 0);
	sem_init(&moretechs, 0, 0);

	// Start the threads

	printf("Starting 2 client threads, 1 help desk thread, and 5 tech threads.\n");

    helpDsk = thread(helpDesk);
	
    for(i = 0; i < 2; i++){
		clients[i] = thread(client);
	}
	
	for(i = 0; i < 5; i++){
		techs[i] = thread(tech);
	}

	// wait for threads to join
    
    helpDsk.join();

	for(i=0; i < 2; i++){
		clients[i].join();
	}
	
	for(i=0; i < 5 ; i++){
		techs[i].join();
	}
}









