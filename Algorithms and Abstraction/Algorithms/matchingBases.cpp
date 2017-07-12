#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <string>

using std::iostream;
using std::endl;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::max;

int matchingBases(string strand);

//LongerstCommonSubsequence
inline bool ifMatchingBases(char a, char b)
{
	if((a == 'C' && b == 'G') || (a == 'G' && b == 'C') || (a == 'U' && b == 'A') || (a == 'A' && b == 'U'))
	{
		return true;
	}
	else
	{
		return false;
	}
};

int LongerstCommonSubsequenceFunction(const string &strand, int i, int j, vector<vector<int>> &lookupTable)
{
	int counter = 0;
	if(lookupTable[i][j] != -1)
	{
		return lookupTable[i][j];
	}
	if(i <= j)
	{
		return 0;
	}// Base cases
	if(ifMatchingBases(strand[i], strand[j]))
	{
		counter = 1 + LongerstCommonSubsequenceFunction(strand, i-1, j+1, lookupTable);
	}
	else
	{
		counter = max(LongerstCommonSubsequenceFunction(strand, i-1,j, lookupTable),LongerstCommonSubsequenceFunction(strand, i, j+1, lookupTable));
	}
	lookupTable[i][j] = counter;
	return counter;
};
// Lookup table must be passed in by reference

int matchingBases(string strand)
{
	vector<vector<int>> lookupTable(strand.size(), vector<int>(strand.size(),-1));
	return LongerstCommonSubsequenceFunction(strand,strand.size()-1,0, lookupTable);
};