#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

/*
 * This is an example of using a data sturcture that is atomic and none atomic version to demo the difference.
 *
 * note, the base version was borrowed from https://baptiste-wicht.com/posts/2012/07/c11-concurrency-tutorial-part-4-atomic-type.html
*/

using namespace std;

//This data structure is thread safe since it declared with atomic
struct AtomicCounter {
    atomic<int> value;

    AtomicCounter() : value(0) {}

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get(){
        return value.load();
    }
};

//this data structure is not thread safe and will likely give unexpected and different results every time it runs.
struct Counter {
    int value;

    Counter() : value(0) {}

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get(){
        return value;
    }
};


AtomicCounter atomiccounter;
Counter       counter;


void incr() {
  for(int i = 0; i < 500; ++i){
    counter.increment();
    atomiccounter.increment();
  }
}


int main(){

    vector<thread> threads;

    for(int i = 0; i < 10; ++i){
        threads.push_back(
          thread(incr)
        );
    }

    for(auto& thread : threads){
        thread.join();
    }

    cout << "normal: "<<counter.get() << endl;
    cout << "atmoic: "<<atomiccounter.get() << endl;

    return 0;
}
