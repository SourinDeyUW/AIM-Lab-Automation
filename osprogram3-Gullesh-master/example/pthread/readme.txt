The following code is used the pthread lecture.
thread_simple.cpp create two threads, like the simple.cpp created two processes
thread_oddeven.cc creates two threads (two versions)

to compile this on cosc linux 
g++ thread_simple.cpp -lpthread -o simple

#shows the difference with a printf and cout for output
g++ thread_oddeven_cout.ccp -lpthread -o oddeven_cout
g++ thread_oddeven_printf.ccp -lpthread -o oddeven_printf


#semaphores and mutex examples
semaphore_mutex_oddeven is a simple example that lock steps the odd and even so that odd then even, then odd, etc.

buffer example 
  with sempahores  only uses only sempahores to manage the buffer, and id numbers
  semaphores and mutex use the mutex lock for the buffer cr and id numbers.  the semphores manage empty and full
  the ptrcheat uses void * values to send id numbers as parameter (as a pointer actually).  not recommended, but an exampe of how starnge pointers can be used.

unisex is an implmenetation for the unisex bathroom problem, that works, but it has starvation issues

compile:
g++ semaphore_mutex_oddeven.cpp -o oddeven -lpthread -std=c++11
g++ semaphore_buffer.cpp -o buffer -lpthread -std=c++11
g++ semaphore_mutex_buffer.cpp -o buffer_sm -lpthread -std=c++11
g++ semaphore_buffer_ptrcheat.cpp -o buffer_cheat -lpthread -std=c++11
g++ semaphore_mutex_unisex.cpp -o unisex -lpthread -std=c++11



The threadtest are test cases where a fork is used with threading to see what
happens.  The output prints the pid with every line of output.

threadtest.cpp, a fork is called from main with 2 running threads

threadtest1.cpp a fork is called from the first thread and the second thread
may not have been created yet.

threadtest2.cpp  a fork is called from the second thread (and first thread is
running).

threadtest3.cpp  just for completeness, the fork is called in main first, before
any threads are created

g++ threadtest.cpp -lpthread -o ttest 
g++ threadtest1.cpp -lpthread -o ttest1
g++ threadtest2.cpp -lpthread -o ttest2
g++ threadtest3.cpp -lpthread -o ttest3

You can run them to see what happens
