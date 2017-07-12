#ifndef ARRAYQUEUE
#define ARRAYQUEUE
#include "Queue.h"

template<typename T>


class ArrayQueue : public Queue <T>
{
	private:	
	
	T* container; // Pointer to an array of type T
	int size; 
	int front;
	int back;// Front of the queue

	public:
		ArrayQueue(): container(new T[10]),size(10),front(0),back(0)
		{

		};// Constructors
		~ArrayQueue()
		{
		delete [] container;
		};
		//destructors
		 

		 ArrayQueue(const ArrayQueue& b):container(new T[b.size]),size(b.size),front(b.front),back(b.back)
		 {
		 	for(int i = 0; i < size ; ++i)
		 	{
		 		container[i] = b.container[i];
		 	}
		 };//Copy constructor
	

		bool isEmpty() const
		{
			if(front == back) 
			{
				return true;
			} 
			else 
			{
				return false;
			}// If the front of the queue = the back of the queue then it is in the same position = empty
		}
		T dequeue()  {
			T x = container[front];
			front = (front + 1)%size; // This is the index because it would be that number % the same number which is 0 so it wraps around
			return x;  
		} // This removes from the queue

		T peek() const 
		{
			return container[front];
		} // This looks at the front of the queue

		void enqueue(const T& t)  
		{

			if ((back + 1) % size == front) {
				T* Data = new T[size * 2];
				for (int i = 0; i < size; ++i) { Data[i] = container[(i + front) % size];} // Takes the front wraps it around and copies to the beging of the queue
				front = 0;
				back = size - 1;
				delete [] container; // delete tthe old container
				container = Data;
				size = size * 2;
			
		}
			container[back] = t ;
			back = (back + 1) % size; //because it would be that number % the same number which is 0 so it wraps around

		} // This adds to the queue

};


#endif

