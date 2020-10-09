#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int max_num = 20;
sem_t full,empty,multex;
int buffer[10], bufferc = 0;
int consumern =1, producern=1;

/*
 * uses just semaphores for everything.
*/

void produc() {
  int i,eid,id,t;

  //geting an id number
  sem_wait( &multex );
    id =  producern;
    producern++ ;
  sem_post( &multex );


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

void consum() {
  int i,t,eid,id,item;

  //geting an id number
  sem_wait( &multex );
    id =  consumern;
    consumern++ ;
  sem_post( &multex );

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

  thread cons[num_c];
  thread prod[num_p];


  srand((unsigned)time(0));

//init semaphore full to 0 since nothing in queue yet
   sem_init(&full, 0, 0);

//init semaphore empty to 10, since we can produce 10 items.
  sem_init(&empty, 0, 10);

//init semaphore multex to 1, so first person can entry critical section
  sem_init(&multex, 0, 1);


// create threads 
  for (i=0; i<num_c; i++) {
    cons[i] = thread(consum);
  }
  printf ("consmer threads created\n");

  for (i=0; i<num_p; i++) {
    prod[i] = thread(produc);
  }
  printf ("threads created\n");


//wait for threads to finish 
  for(i=0;i<num_c;i++) 
    cons[i].join();

  for(i=0;i<num_p;i++) 
    prod[i].join();

}
