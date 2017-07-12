#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <unordered_map> 

using std::find;
using std::min;
using std::vector;
using std::cout;

int helperCalculatorFunction(int S, int c, const vector<vector<int>> &connects, vector<std::unordered_map<int, int>> &container);
int shortestCycle(const vector<vector<int>> &connects); 

int helperCalculatorFunction(int S, int c, const vector<vector<int>> &connects, vector<std::unordered_map<int, int>> &container) 
{
	auto r = container[c].find(S);
	if (r!= container[c].end()) 
	{
		return r -> second;	
	}
	else 
	{
		int optimalSolution = 100000000;
		int S1 = S& ~(1<<c); // Bit shift by c
		for (int j = 1; j < connects.size(); ++j) 
		{
			if (j != c && S & (1<<j)) 
			{
				optimalSolution = min(optimalSolution, helperCalculatorFunction(S1, j, connects, container) + connects[j][c]);
			}
		}
		container[c][S] = optimalSolution;
		return optimalSolution;
	}
}
int shortestCycle(const vector<vector<int>> &connects) 
{

	int sizeOfDistances = connects.size();
	vector<std::unordered_map<int, int>> cache(sizeOfDistances);
	
	for(int i = 1; i < sizeOfDistances; ++i) 
	{
		cache[i][1<<i] = connects[0][i]; // Distance from 0 to i, shift bits by i
	}

	int Store = 0;

	for(int i = 1; i < sizeOfDistances; ++i) 
	{
		Store|= 1<<i; // Performs bitwise OR operation on two specified integer values and sets a value to the result of the operation.
	}
	int optimalSolution = 1000000000;

	for (int i = 1; i < sizeOfDistances; ++i) 
	{
		optimalSolution = min(optimalSolution, helperCalculatorFunction(Store, i, connects, cache) + connects[i][0]);
	}
	return optimalSolution;
};
