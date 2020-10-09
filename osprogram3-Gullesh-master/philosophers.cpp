#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <semaphore.h>
#include <mutex>
#include <vector>

using namespace std;

//semaphores and one mutex
vector<sem_t> frk(5);
mutex multex;

// Philosopher id starting 0
int philoid =0;


 
void philosopher() {
  int id,t,left,right;

  multex.lock() ;                   //geting an id number
    id = philoid;
    philoid++;
    left=min(id,(id+1)%5);    // To avoid dead lock I use this so last philosopher
    right=max(id,(id+1)%5);   // somehow change her hands order(you told me to mention it here for you.)

  multex.unlock();
  printf("philosopher %d:  Starting.\n",id);

  while (true)  {

   //thinking
    t = (int) rand() % 10; 
    printf("philosopher %d: is pondering about eating for %d seconds.\n",id,t);
    sleep (t);

  printf("philosopher %d: concluded he should eat something rather than starving.\n",id);

  sem_wait(&frk[left]);                
	sem_wait(&frk[right]);
// Eating
	printf("philosopher %d: got forks %d and %d.\n", id, left, right);

    t = (int) rand() % 10;
	printf("philosopher %d: is eating for %d seconds.\n", id, t);
	sleep(t);

  sem_post(&frk[min(id,(id+1)%5)]);
	sem_post(&frk[max(id,(id+1)%5)]);

    printf("philosopher %d: is done eating and put down forks %d and %d.\n", id, left, right);

    }

}

int main() {
  int i;
  srand((unsigned)time(0));

  thread philosophers[5];

  printf("5 philosophers with 5 forks will start running.\n");

   for(i = 0; i < 5; i++){
		sem_init(&frk[i], 0, 1);
	}

// create threads 
  for (i=0; i<5; i++) {
     philosophers[i] = thread(philosopher);
  }
  printf ("philosophers threads created.\n");


//wait for threads to finish 
  for(i=0;i<5;i++) {
    philosophers[i].join();
  }

}
