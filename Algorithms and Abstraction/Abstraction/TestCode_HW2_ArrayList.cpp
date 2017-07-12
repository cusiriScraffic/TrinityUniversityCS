#include <iostream>
#include <string>
#include "ArrayList.h"

using std::cout;
using std::cin;
using std::string;

void printingArray();
void printInt(int i);
void printString(string s);

ArrayList<int> test; // Container
ArrayList<string> test3 ; // string container

string a = "iii";

void printingArray() 
{
    for (int i = 0; i < test.size(); i++) 
    { 
       cout<<test[i]<<"\n"; 
    }
}
void printInt(int i)
{
	cout<<i<<"\n";
}

void printString(string s)
{
	cout<<s<<"\n";
}

// Main

int main(void) 
{
  	
  	printingArray();
    printString("Testing array");
    printString("Tesing push_back");
  	for (int i = 0; i < 11; i++) 
  	{ 
  		test.push_back(i); 
	  }
  	printingArray();
  	printString("Testing is isEmpty");
  	test.isEmpty();
  	printString("Testing is size");
  	printInt(test.size());
  	printString("Testing is insert");
  	test.insert(10,5);  
  	printingArray();
  	printString("Tesing pop_back");
  	test.pop_back();
  	printingArray();
  	printString("Testing is remove");
  	printString("Testing");
  	test.remove(1);
  	printingArray();
  	printInt(test.size());
  	printString("Testing is Copy Constructor");
  	ArrayList<int> test2 = test;
  	printInt(test2.size());
  	printString("Testing is clear");
  	test.clear();
  	cout<<"List size "<<test.size()<<"\n";
  	printString("Testing is ArrayList is string type");
  	test3.push_back("i");
  	printString("Testing");
  	printString(test3[0]);
  	test3.insert("B",0);
  	printString("Testing");
  	printString(test3[0]);
  	printString("Testing");
  	cout<<"tesing";

  	// Thousand vaiable testing
  	for(int i = 0; i <= 1000; ++i )
  	{
  		test.push_back(i);
  	}
  	for(int i = 0; i <= 1000; ++i )
  	{
  		cout<<test[i]<<",";
  	} 		
	for(int i = 0; i <= 1000; i++ )
  	{
  		test3.push_back(a); 
  	}  	
  	for(int i = 0; i <= 1000; ++i )
  	{
  		cout<<test3[i];
  	} 
  	printString("Testing is Iterators");
  	for(auto i = test.cbegin(); i != test.cend(); ++i)
  	{
  		cout<<"Testing";
  	}
  	for(auto i = test.cbegin(); i != test.cend(); ++i)
  	{
  		cout<<"Testing Iter\n";
  	}
  	printString("CLEAR");
  	test.clear();
};

