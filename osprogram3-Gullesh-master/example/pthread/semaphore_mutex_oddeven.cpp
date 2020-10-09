#include <cstdio>
#include <iostream>
#include <pthread.h>
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

void *odd(void * noparm) {
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

void *even(void * noparm) {
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
  pthread_t th1, th2;

//init semaphore sem1 to 0, so  sem1 will always go second
  sem_init(&sem1,0,0);
//init semaphore sem2 to 1  so sem2  will always go first
  sem_init(&sem2,0,1);


// create thread 1
 if (pthread_create(&th1, NULL, odd, 0)) {
    perror("error creating the first thread");
    exit(1);
  }

  printf("created the first thread\n");

// create thread 2
  if (pthread_create(&th2, 0, even, 0)) {
    perror("error creating the second thread");
    exit(1);
  }
  printf("created the second thread\n");

//wait for threads to finish
  pthread_join(th1, 0);
  pthread_join(th2, 0);
}
