#include <iostream>
#include <string>
#include "ArrayQueue.h"
#include "ArrayStack.h"
#include "Stack.h"
#include "Queue.h"


using std::cout;
using std::cin;
using std::string;



int main() 
{

	ArrayStack<int> stack ;	
			
	cout<< "Array stack\n";
	if(stack.isEmpty())
	{
		cout<< "Stack is empty\n";
		cout<< "Push Function, adding the number 1099\n";
		stack.push(1000);
		cout<< "Peek Funciton\n";
		cout<< stack.peek()<< '\n';
		for(int i = 0; i <= 1100 ; ++i )
		{
			stack.push(i);
			cout << stack.peek() << "\n";
		}
		cout << "Adding elements to stack\n";
		cout << "Peek Funciton\n";
		cout<< stack.peek()<< '\n';
		for(int i = 0 ; i> 1101 ; --i) 
		{
			stack.pop();
			cout<< stack.peek() << "\n";
		}
		cout << "Removing elements from stack\n";
		cout<< "Peek Funciton\n";
		cout<< stack.peek()<< '\n';

	}

	cout<< "ArrayQueue\n";

	ArrayQueue<int> queue ;	
			

	if(queue.isEmpty())
	{
		cout<< "queue is empty\n";
		cout<< "enqueue Function of the number \n";
		queue.enqueue(12000);
		cout<< "Peek Funciton\n";
		cout<<queue.peek()<< '\n';
		for(int i = 0; i < 1100 ; ++i )
		{
			queue.enqueue(i);
			cout << queue.peek() << "\n";
		}
		cout<< "Adding elements\n";
		cout << "Peek Funciton\n";
		cout<< queue.peek()<< '\n';
		for(int i = 0 ; i > 1101 ; --i) 
		{
			queue.dequeue();
		}
		cout<< "removing elements\n";
		cout << "dequeue Function\n";
		queue.peek();
		cout<< "Peek Funciton\n";
		cout<< queue.peek()<< '\n';

		cout<< "Copy constructor test\n";

		cout<<"Queue copy constructor\n";

		ArrayQueue<int> queue2 = queue ;// testing the copy constructor on Array Queue Dest = Source
		cout << "Peek Funciton for new queue\n";
		cout<< queue2.peek()<< '\n';
		cout<<"Stack copy constructor\n";
		ArrayStack<int> stack2 = stack ;// testing the copy constructor on Array stack 
		cout << "Peek Funciton for new stack\n";
		cout<< stack2.peek()<< '\n';

		
		// assignment operator is used when reassigning objects eg if queue2 already existed

	}


return 0;
};