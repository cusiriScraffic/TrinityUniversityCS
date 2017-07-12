#ifndef ARRAYSTACK
#define ARRAYSTACK
#include "Stack.h"

template<typename T>

class ArrayStack : public Stack <T>
{

	private:

	T* container; // This is a pointer to an array container of type T
	int size;		// This is a variable which shows the size of the array
	int stackTop;



	public:
 //Copy constructor You want to copy the content and not just the pointer.
	ArrayStack(): container(new T[10]),size(10),stackTop(0)
	{
	
	};  // Default Constructor, with initialization list
	ArrayStack(const ArrayStack& a): container(new T[a.size]),size(a.size),stackTop(a.stackTop)
	{ // This is the prefereed syntax for constructors 
	// Initializers
	// making exact copies of what is in a	
	//Copying the contents of the array with a for loop
		for(int i = 0; i < size; ++i) 
		{
			container[i] = a.container[i]; // a.container is the old array (Source = destination)
			// this is the standard way of copying over the contents c++ or c
		}	

	};// Just an array stack that takes in a stack


	//The copy constructor is to make a copy of the stack if you want to make a copy.


	~ArrayStack(){
		delete [] container;
	}; // Destructor


	T pop() override
	{
		stackTop -= 1;
		return container[stackTop];
	}

	T peek() const override
	{
		return container[stackTop - 1];
	}
		

	 void push(const T& item) override {
		
		if(stackTop >= size){
			T* container2;
			container2 = new T [size *2]; // Create a new container array by a factor of 2
			
			for(int i = 0; i < size; ++i) {
				container2[i] = container[i];
			} // Range for loop needs to know the size of the array or it needs have an iterator
			
			delete [] container; // Which deletes the old container, which has been moved to c2
	 		container = container2; // Copy things over to the new array
			//Creates a new array that is bigger then copies things overs
			size = size*2; // Update new size of array

		} 
		container[stackTop] = item;
		++stackTop;
			
		// Make array bigger if the top is bigger
		// Increment item into stack
		
	}

	bool isEmpty() const override
	{
		if(stackTop == 0) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}


};

#endif