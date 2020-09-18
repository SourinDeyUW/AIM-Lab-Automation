//=====================================
//
//Mehdi Nourelahi	
//
//Operating system design: COSC 4740
//
//Program 1 assignment
//
//=====================================
#ifndef QA_H
#define QA_H

#include<queue>                         // Using STL queue container
using namespace std;                

template <class type>
class QueueArray
{
    public:
                        
        QueueArray(int);                //Constructor

        ~QueueArray();                  //Destructor
        
        int Enqueue(type, int);         // Enqueues an item in queue of array index
        
        type Dequeue();                // Dequeues an item from first non-empty queue 
        
        int Qsize(int);                // Returns number of items in the queues of array at index
        
        int Asize();                   // Returns size of the array 
       
        int QAsize();                  // Returns the total number of items stored in array of queues

        type* Qstate(int);             // Copies all items stored in the queue at array index and return pointer to that array
        

    private:
        queue<type>* array;            // Array of queues
        int arraySize;                 // Size of the array
        int totalItems;                // Number of all items in queus
};


template<typename type>                                           

QueueArray<type>::QueueArray(int size)        // Constructor for class        
{

    arraySize = size;                         // Copy size into arraySize 
    totalItems = 0;
    array = new queue<type> [arraySize];      // Create a pointer to array of queues
}

template<typename type>

QueueArray<type>::~QueueArray()                //Destructor for class
{
    
    for(int i = 0; i < arraySize; i++)         //freeing memory by poping all items in queues
    {
        while(!array[i].empty())
        {
            array[i].pop();
        }
    }

    totalItems = 0;

    delete[] array;                           //Deallocate memory
}

template<typename type>
int QueueArray<type>::Asize()
{
	    return arraySize;
}
template<typename type>
int QueueArray<type>::Enqueue(type item, int index)           // Enqueue item in queue of array index
{
    //Validate index
    if(index < 0 || index >= arraySize)                   // Return -1 if index is out of range 
                                                                            // 1 if successful, and 0 otherwise
    {
        return -1;
    }

    array[index].push(item);                                  // Enqueue item


    if(array[index].back() == item)                        // Check if pushing item was successful 
    {
        totalItems++;
        return 1;                                                                                   
    }
    else
    {
        return 0;
    }
}

template<typename type>
int QueueArray<type>::Qsize(int index)               // Return number of items in the queue at array index

{
   
    if(index < 0 || index >= arraySize)                     // Return -1 if index is out of range
    {
        return -1;
    }
    else
    {
        int size = array[index].size();
        return size;
    }
}


template<typename type>
int QueueArray<type>::QAsize()
{
    return totalItems;                                     // Return total number of items
}


template<typename type>                      // Dequeue item from the first non-empty queue of array
type QueueArray<type>::Dequeue()
{
       	for(int i = 0; i < arraySize; i++)                  // Find first non-empty queue and pop from it
    {
        if(!array[i].empty())
        {
            type rm = array[i].front();
            array[i].pop();
            totalItems--;
	    return rm;
          }
    }
return 0;
}


template<typename type>                                       //Return all stored items
type* QueueArray<type>::Qstate(int index)
{

    if(index < 0 || index >= arraySize)                      //Validate index
    {
        return NULL;
    }
    else
    {
        int size = array[index].size();                        //Create array
        type* returnArray = new type[size];
        

        int i = 0;                                                        //Copy elements into array 
        while(!array[index].empty())
        {
            returnArray[i] = array[index].front();
            array[index].pop();
            i++;
        }


        for(int i = 0; i < size; i++)                              // Put back elements in their place
        {
            array[index].push(returnArray[i]);
        }
        
        return returnArray;
    }
}
#endif
