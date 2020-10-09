#include <cstdio>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/*
 * Show the problems with out using a cout
 * even a cout.flush)() doesn't help.
*/

void odd(int id) {
  int i;
  printf ("my id is %d\n",id);

  for (i =0; i<10; i++) {
    printf("odd \n");
  }

}

void  even(int id) {
  int i;

  printf ("my id is %d\n",id);

  for (i =0; i<10; i++) {
    printf("even \n");
  } 
}

main() {

  int i=1;
  thread th1, th2;

// create thread1
  th1 = thread(odd, i);
  printf("created the first thread\n");

  i++;
//create thread2
  th2 = thread(even, i);
  printf ("created the second thread\n");

//wait for threads to finish
  th1.join();
  th2.join();

}
