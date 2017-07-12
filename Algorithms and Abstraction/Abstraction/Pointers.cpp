#include <iostream>
#include <vector>


using std::vector;
using std::cout;

struct Point {
	double x;
	double y;
};

	

void recur(int arg){

	if(arg>0) {
		int i = {5};
		cout << arg << "" << &i <<""<< &arg <<'\n';
		recur(arg-1);
	}
}



int main(void) {

	int a = {42}; 

	short s = {99};
	// a holds a number 42
	int *b = {&a}; 
	// B is a pointer to a
	int *c = {new int}; 
	// Another way to create a pointer. Calls heap pointer
	
	cout << b << '\n';
	cout << c << '\n';
	cout << &b << '\n';
	cout << &c << '\n';
	cout << a << '\n';
	recur(3);
	
	Point  p = {1,5};
	Point *pp = {&p}; // Pointer to a point

	cout << p.x << '\n';
	cout << pp -> x << '\n' ;// in general a-> b is == *a.b

	// You can dereference this using * or b[0] which is a shorthand syntax
	delete c ;
	return 0;
}