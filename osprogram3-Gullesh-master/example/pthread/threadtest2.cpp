#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>


using namespace std;

/*
 * This is a test of fork when it forks in the 2rd thread.  howmany threads do i get?
 */


//function the first thread uses.
void * firstthread(void * noparam) {
  int i;

  
  //testing forks with threads, need to wait a couple of seconds here.
  sleep(2); 

  for (i =0; i<10; i++) {
    cout <<getpid() <<" I'm the first thread and the oldest child.\n";
  }

}

//function the second thread uses
void * secondthread(void * noparam) {
  int c1;

  //so fork in thread and now what happens?
  
  if ((c1 = fork()) == -1) /* Create the first child process */ {
    perror("unable to fork first child");
    exit(1);
  }
  else if (c1 == 0) { /* This is the first child process */

    cout <<"first child pid = "<< getpid()<<endl;
  }

  for (int i = 0; i < 10; i++) {
    cout <<getpid() <<" No fair, The parent likes me better\n";
  }
}

main() {
  int i, c1, status;
  pthread_t th1, th2;

// create thread1
  if (pthread_create(&th1, NULL, firstthread, 0)) {
    perror("error creating the first thread");
    exit(1);
  }
  cout << "created the first thread" << endl;

//create thread2
  if (pthread_create(&th2, NULL, secondthread, 0)) {
    perror("error creating the second thread");
    exit(1);
  }
  cout << "created the second thread" << endl;
  
  //the parent process is the only one who should get to this code.
  for (i = 0; i < 20; i++) {
    cout <<getpid() << " Why did I have threads again?\n";
  }

//wait for threads to finish
  pthread_join(th1, 0);
  pthread_join(th2, 0);
}
