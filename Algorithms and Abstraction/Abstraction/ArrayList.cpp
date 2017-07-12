#include <iostream>

using std::cout;



int main(void) {
	int a = 42;
	int &d = a;

	cout << d << '\n';

	d = 99;
	cout << d << '\n';
	cout << a << '\n';

	// Once you have created your refernce it is always bound to that memory location but with pointers you can change the address
	return 0;
}
