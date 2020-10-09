#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/*
 * threads with printf, that output correctly
 * cout don't always produce output in the correct order
*/


void * odd(void *mid) {
  int i;
  int *id = (int *) mid;
  //printf ("my id is %d\n",*id);
  cout <<"my id is "<<*id<<endl;

  for (i =0; i<10; i++) {
    //printf("odd \n");
    cout <<"odd \n";
  }

}

void * even(void * mid) {
  int i;

  int *id = (int *) mid;
  //printf ("my id is %d\n",*id);
  cout <<"my id is "<<*id<<endl;

  for (i =0; i<10; i++) {
    //printf("even \n");
    cout <<"even \n";
  } 
}

main()
{
  int i=1;
  pthread_t th1, th2;

// create thread1
  if (pthread_create(&th1, NULL, odd, &i)) {
    perror("error creating the first thread");
    exit(1);
  }
  //printf("created the first thread\n");
  cout << "created the first thread" << endl;

sleep(1);

  i++;
//create thread2
  if (pthread_create(&th2, NULL, even, &i)) {
    perror("error creating the second thread");
    exit(1);
  }
 // printf ("created the second thread\n");
  cout << "created the second thread" << endl;

//wait for threads to finish
  pthread_join(th1, 0);
  pthread_join(th2, 0);
}
