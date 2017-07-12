// // Team C Calvin, Caroline, Eddie

#include <vector>
#include <future>
#include <iostream>
#include <thread>


using std::future; // The class template std::future provides a mechanism to access the result of asynchronous operations
using std::ref;//The thread constructors are variadic templates, This implies that to pass a reference to a thread constructor, we must use a reference wrapper
using std::async;
using std::vector;
using std::cout;
using std::endl;

// Adding row at a time
// If you create too many threads, group together the amount of work eg rows/32 or row/64 which is to fill in the c matrix.
vector<double> helperFunction(const vector<double> &a ,const vector<vector<double>> &b)
{
	vector<double> tmp(b[0].size(),0); // The new matrix of n*n matrix
	auto n = a.size(); // Number of colums of matrix a, which is the inner dimension
	for(int i = 0; i < b[0].size() ; i++ )// Producing rows of the C matrix
	{
		for(int k = 0; k < n; k++ )
		{
			tmp[i] = tmp[i] + a[k]* b[k][i];
		}
	}
	return tmp;
};

//We are multithreading the for loops
vector<vector<double>> pMatrixMult(const vector<vector<double>> &a ,const vector<vector<double>> &b)
{
	auto n = a.size();// Finds the number of rows with the matrix
	
	vector<vector<double>> finalResult;
	vector<future<vector<double>>> vectorMatrix; // The new matrix of n*n matrix
	for (int i = 0; i < n; ++i) 
	{
			vectorMatrix.push_back(async(std::launch::async, helperFunction, ref(a[i]), ref(b)));
	}
	for (int i = 0; i < vectorMatrix.size(); ++i) 
	{
		finalResult.push_back(vectorMatrix[i].get());
	}
	return finalResult;
};