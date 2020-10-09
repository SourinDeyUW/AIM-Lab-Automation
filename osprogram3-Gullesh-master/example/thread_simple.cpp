#include <cstdio>
#include <iostream>
#include <thread>
#include <cstdlib>

using namespace std;

//to use a yield, but based on tests in this code, may not do much.
//     this_thread::yield();

//function the first thread uses.

void firstthread() {
  int i;
  for (i =0; i<10; i++) {
    cout <<"I'm the first thread and the oldest child.\n";
//     this_thread::yield();
  }

}

//function the second thread uses
void secondthread() {
  for (int i = 0; i < 10; i++) {
    cout <<"No fair, The parent likes me better\n";
  }
}

main() {
  int i;
  //thread variables
  thread th1, th2;

// create thread1
  th1 = thread(firstthread); 
  cout << "created the first thread" << endl;

//create thread2
  th2 =thread(&secondthread);
  cout << "created the second thread" << endl;

  //the parent process is the only one who should get to this code.
  for (i = 0; i < 20; i++) {
    cout << "Why did I have threads again?\n";
  }

//wait for threads to finish
  th1.join();
  th2.join();
}
