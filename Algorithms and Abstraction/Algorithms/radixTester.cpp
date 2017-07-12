#include "order.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

int main()
{
	std::vector<int>Container = {1,2,3,4,5};
	std::vector<int>Container2 = {3,52,4,52,5};
	for(auto i = Container2.begin(); i != Container2.end(); i++)
	{
		cout<<*i<<","<<endl;
	}
	cout<<"After insertionSort"<<endl;
	// randomOrderStat(Container.begin(),Container.end(),[](int a,int b)
	// 	{
	// 		return a<b; // Lamda expression
	// 	},0);

	insertionSort(Container2.begin(),Container2.end(),[](int a,int b)
		{
			return a<b; // Lamda expression giving a comparator function
		});
	for(auto i = Container2.begin(); i != Container2.end(); i++)
	{
		cout<<*i<<","<<endl;
	}
	return 0; 
};