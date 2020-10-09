#include <cstdio>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/*
 * threads with printf, that output correctly
 * cout don't always produce output in the correct order
*/


void odd(int id) {
  int i;
  cout <<"my id is "<<id<<endl;

  for (i =0; i<10; i++) {
    cout <<"odd \n";
  }

}

void even(int id) {
  int i;
  cout <<"my id is "<<id<<endl;

  for (i =0; i<10; i++) {
    cout <<"even \n";
  } 
}

main() {
  int i=1;
  thread th1, th2;

// create thread1
  th1 = thread(odd, i);
  cout << "created the first thread" << endl;

  i++;
//create thread2
  th2 = thread(even, i);
  cout << "created the second thread" << endl;

//wait for threads to finish
  th1.join();
  th2.join();
}
