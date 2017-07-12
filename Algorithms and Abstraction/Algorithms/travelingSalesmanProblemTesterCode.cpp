#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map> 

using std::vector;
using std::endl;
using std::cout;

int helperCalculatorFunction(int S, int c, const vector<vector<int>> &connects, vector<std::unordered_map<int, int>> &container);
int shortestCycle(const vector<vector<int>> &connects); 
vector<vector<int>>connects {{0,1,2,3,4},{4,5,6,3},{6,4,3,5}};
int main(void)
{
	auto r = shortestCycle(connects);
	cout<<r<<endl;
	return 0;
};