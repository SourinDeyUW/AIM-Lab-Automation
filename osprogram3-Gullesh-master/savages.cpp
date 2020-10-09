
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <semaphore.h>
#include <mutex>

using namespace std;

// Declare semaphores & mutexes
sem_t needCook, potFilled,pot;
mutex sidLock;
int Nservings=10;
int servings=Nservings;

// savage ids
int sId = 0;

// cook
void cook(){
	int t;

	printf("cook starting.\n");

	while(true){			// if pot is empty cook will woke up and fill the pot.

		t = (int)rand() % 10;
		printf("cook will sleep for %d seconds since pot is full.\n",t);
		sleep(t);

		sem_wait(&needCook);
		t = (int)rand() % 10;
		printf("cook wokke up to fill the pot in %d seconds.\n",t);
		sleep(t);
		servings = Nservings;
		printf("cook filled the pot, savage can eat now.\n");
		sem_post(&potFilled);
	}
}

void savage(){
	int i,id, t;
	
	sidLock.lock();
		id = sId;
		sId++;
	sidLock.unlock();

	printf("savage %d: started\n", id);

	// Check the pot, eat if food available, signal cook otherwise
	while(true){
	
		t = (int)rand() % 10;
		printf("savage %d: roaming around pot for %d seconds\n", id, t);
		sleep(t);

		sem_wait(&pot);
			if(servings == 0){
				printf("savage %d: encoutered with the empty pot and wants to wake up cook.\n", id);
				sem_post(&needCook); // Signal the cook
				sem_wait(&potFilled); // Wait for the cook to fill
				printf("savage %d: resuming after pot filled\n", id);
			}
			t = (int)rand() % 10;
			printf("savage %d: will eat a serving for %d seconds\n", id, t);
			sleep(t);
			servings--;
			printf("savage %d: ate a serving and %d servings still left in the pot.\n", id, servings);
		sem_post(&pot);
	}
}


int main(int argc, char *argv[]){

	
	// getting number of servings in full pot
	if(argc == 2){
		Nservings = atoi(argv[1]);
		servings = Nservings;
	}

	// Declare main variables & seed rng
	srand((unsigned)time(0));
	int i;
	thread cooking;
	thread savages[10];

	printf("Creating %d servings for 10 savages.\n", Nservings);

	// Initialize semaphores
	sem_init(&potFilled, 0, 0);
	sem_init(&needCook, 0, 0);
	sem_init(&pot, 0, 1);


	// Start the threads
		cooking = thread(cook);

	for(i = 0; i < 10; i++){
		savages[i] = thread(savage);
	}
	printf("threads created\n");

	// wait for threads to join
	cooking.join();
	for(i = 0; i < 10; i++){
		savages[i].join();
	}
}

