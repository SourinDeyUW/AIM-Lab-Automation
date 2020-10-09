#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;


//function the first thread uses.
//note, while there is no parameter going to be passed, still no it declared anyway
void * firstthread(void * noparam) {
  int i;
  for (i =0; i<10; i++) {
    cout <<"I'm the first thread and the oldest child.\n";
  }

}

//function the second thread uses
//note, while there is no parameter going to be passed, still no it declared anyway
void * secondthread(void * noparam) {
  for (int i = 0; i < 10; i++) {
    cout <<"No fair, The parent likes me better\n";
  }
}

main() {
  int i;
  //thread variables
  pthread_t th1, th2;

// create thread1
   //the 0 out the end, means no parameters
  if (pthread_create(&th1, NULL, firstthread, 0)) {
    perror("error creating the first thread");
    exit(1);
  }
  cout << "created the first thread" << endl;

//create thread2
   //the 0 out the end, means no parameters
  if (pthread_create(&th2, NULL, secondthread, 0)) {
    perror("error creating the second thread");
    exit(1);
  }
  cout << "created the second thread" << endl;

  //the parent process is the only one who should get to this code.
  for (i = 0; i < 20; i++) {
    cout << "Why did I have threads again?\n";
  }

//wait for threads to finish
  pthread_join(th1, 0);
  pthread_join(th2, 0);
}
