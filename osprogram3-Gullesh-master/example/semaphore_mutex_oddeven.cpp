#include <cstdio>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <semaphore.h>
#include <mutex>


using namespace std;

/*
 * we want the odd and even to alternate, so use two semphores
 */

mutex multex;
sem_t sem1, sem2; 
int idnumber =1;

void odd() {
  int i,id;

  //geting an id number
  multex.lock() ;
    id =  idnumber;
    idnumber++ ;
  multex.unlock();

  printf ("my id is %d\n",id);

  for (i =0; i<10; i++) {
    sem_wait( &sem1 );
    printf("odd \n");
    sem_post( &sem2 );
  }

}

void even() {
  int i,id;

  //geting an id number
  multex.lock() ;
    id =  idnumber;
    idnumber++ ;
  multex.unlock();

  printf ("my id is %d\n",id);

  for (i =0; i<10; i++) {
    sem_wait( &sem2 );
    printf("even \n");
    sem_post( &sem1 );
  } 
}

main()
{
  thread th1, th2;

//init semaphore sem1 to 0, so  sem1 will always go second
  sem_init(&sem1,0,0);
//init semaphore sem2 to 1  so sem2  will always go first
  sem_init(&sem2,0,1);


// create thread 1
  th1 = thread(odd);
  printf("created the first thread\n");

// create thread 2
  th2 = thread(even);
  printf("created the second thread\n");

//wait for threads to finish
  th1.join();
  th2.join();
}
