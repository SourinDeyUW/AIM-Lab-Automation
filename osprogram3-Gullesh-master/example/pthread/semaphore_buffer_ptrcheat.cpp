#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int max_num = 20;
sem_t full,empty,multex;
int buffer[10], bufferc = 0;
long consumern =1, producern=1;


/*
 * a note of this version.  I'm cheating with the pointers and not using semaphore or mutex to ge the id for the process.
 * note that consumern and producern are long to match the pointer.
 * I'm sending a value as a pointer that is the id number
 * If I was to use *mid "correctly, it would cause a segmentation fault
 * note the cast int id = (long)mid;  get the pointer value and uses it as an integer
 * instead of as pointer.
 */


void *produc(void * mid) {
  int i,eid,id,t;

  //geting an id number
  id =  (long)mid;

  printf("producer %d:  Starting \n",id);

// the producer will produce 10 items for this one, otherwise, we could just go infinite.

  for (int x=0; x<10;x++)  {

    t = (int) rand() % 10; 
    printf("Producer %d:  producing for %d seconds\n",id,t);
    sleep (t);

    //don't add to buffer if full    
    
    sem_wait( &empty );
 
    //criticial section
    sem_wait( &multex );
      buffer[bufferc] = id; 
      bufferc++;
    sem_post( &multex );

    printf("Producer %d:  has placed an item number %d in the buffer\n",id,x);
    sem_post( &full );
  } 
}

void *consum(void * mid) {
  int i,t,eid,id,item;


  //geting an id number
  id =  (long)mid;

  printf("Consumer %d:  Starting \n",id);

  //initial set to infinite for testing
  for ( ;1<2;) {

    printf("Consumer %d: is ready to consume an item\n",id);
    sem_wait( &full );

    //enter critical section
    sem_wait( &multex );
      bufferc--;
      item = buffer[bufferc]; 
    sem_post( &multex );

    printf("consumer %d:  has a new item %d\n",id,item);
    sem_post( &empty);
    t = (int) rand() % 30;
    printf("Consumer %d: consuming for  %d seconds\n",id,t);
    sleep (t);
  } 
}

main(int argc, char* argv[]) {
  int i;


  int num_p = 1; 
  int num_c=1;
  if (argc ==3) {
    num_p = atoi( argv[1] );
    num_c = atoi( argv[2] );
  } 
  printf("p is %d, c is %d\n", num_p, num_c);

  pthread_t cons[num_c];
  pthread_t prod[num_p];


  srand((unsigned)time(0));

//init semaphore full to 0 since nothing in queue yet
   sem_init(&full, 0, 0);

//init semaphore empty to 10, since we can produce 10 items.
  sem_init(&empty, 0, 10);

//init semaphore multex to 1, so first person can entry critical section
  sem_init(&multex, 0, 1);


// create threads 
  for (i=0; i<num_c; i++) {
     if (pthread_create(&cons[i], NULL, consum, (void *)consumern)) {
       perror("error creating the thread");
       exit(1);
     }
    consumern++;
  }
  printf ("consmer threads created\n");

  for (i=0; i<num_p; i++) {
    if (pthread_create(&prod[i], NULL, produc, (void *)producern)) {
      perror("error creating the thread");
      exit(1);
    }
    producern++;
  }
  printf ("threads created\n");


//wait for threads to finish 
  for(i=0;i<num_c;i++) 
    pthread_join(cons[i], 0);

  for(i=0;i<num_p;i++) 
  pthread_join(prod[i], 0);

}
