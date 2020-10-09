

Thread examples

thread_simple.cpp is a simple threading example that creates two threads.
thread_oddeven_?.cpp creates two threads as well.  cout using couts, which the stream can be "corrupted" by threading, which printf is the example with printf's with the output is not corrupted.

to compile:
g++ thread_simple.cpp -pthread -std=c++11 -o simple
g++ thread_oddeven_cout.cpp -pthread -std=c++11 -o oddeven_c
g++ thread_oddeven_printf.cpp -pthread -std=c++11 -o oddeven_p


semaphore and mutex examples

odddeven semphoare lock steps the two threads and  makes sure that odd and even always alternate back and forth
buffer (three versions)  all of them take parameters for the number producers and consumers.
  uses semaphores to access the buffer and id number
  uses sempahores for the buffere and mutex for the id number  
  param sends the id number as parameter to each thread.
unisex is a solution for the unisex bathroom, that works, but it has starvation issues

compile:
g++ semaphore_mutex_oddeven.cpp -pthread -std=c++11 -o oddeven
g++ semaphore_buffer.cpp -pthread -std=c++11 -o buffer
g++ semaphore_buffer_param.cpp -pthread -std=c++11 -o buffer_param
g++ semaphore_mutex_buffer.cpp -pthread -std=c++11 -o buffer_sm
g++ semaphore_mutex_unisex.cpp -pthread -std=c++11 -o unisex


atomic 
  atmoic_example.cpp is simple example to use a data structure with the atomic method instead of locking.

g++ atomic_example.cpp -o atomic -pthread -std=c++11


