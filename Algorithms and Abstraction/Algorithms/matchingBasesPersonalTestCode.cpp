#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include "matchingBases.cpp"
#include <string>

using std::iostream;
using std::endl;
using std::vector;
using std::string;
using std::cout;


int main()
{
	// cout<<"Testing the first"<<endl;
	// matchingBases("CCACUGAACAGUG");
	cout<<"Testing the second"<<endl;
	matchingBases("ACGUGCCACGAUUCAACGUGGCACAG");
	return 0;
};