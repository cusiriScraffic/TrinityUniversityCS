#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::iter_swap;
using std::cout;
using std::endl;

template<typename T>
void insertionSort(T begin, T end)
{

	std::stable_sort(begin, end,[](int a,int b)
		{
			return a<b; // Lamda expression giving a comparator function
		});
};// O(n) 
int randomNum(int i, int j) {
    int r = rand();
    return i + r%(j-i);
}
template<typename T>
void turnFunction(T a, T b) {
    auto tmp = *a;
    *a = *b;
    *b = tmp;
    
}
template<typename T, typename C>
bool executer(T a, T b, C lt) {
    if(lt(*a,*b)) {
        return true;
    } else {
        bool ret = !lt(*a,*b) && !lt(*b,*a);
        return ret;
    }    
}
template<typename T, typename C>
T part(T p, T r, const C &lt) {
    T x = r;
    T i = p-1;
    for(auto j = p; j!=r; j++) {
        if(executer(j,x,lt)) {
            i++;
            std::swap(*i,*j);
        }
    }
    turnFunction(i+1,r);
    return i+1;
}
template<typename T,typename C>
T partitionFunction(T p, T end, const C &lt)
{
  auto r = end-1;
  auto x = *r;                  // x = A[r]
  auto i = p-1;               // i = p - 1
  for (auto j = p; j != r; ++j){// for j= p to r-1
    if (lt(*j, x) || *j == x){      // if A[j] <= x
      ++i;                              // i = i+1
      auto tmp = *i;                // exchange A[i] with A[j]
      *i = *j;
      *j = tmp;
    }
  }
  auto tmp = *(i+1);            // exchange A[i+1] with A[r]
  *(i+1)= *r;
  *r = tmp;
  return i+1;
};
template<typename T,typename C>
T randomizedPartition(T p, T r, C lt)
{
    srand(time(NULL));
    int i = randomNum(0,(r-p));
    std::swap(*(p+i), *r);
    T returner = part(p, r, lt);
    return returner;
};
template<typename T,typename C,typename S>
T randomOrderStat(T begin, T end,C lt,S index)
{
	if(begin == end)
	{
		return begin;
	}
	T q = randomizedPartition(begin,end,lt);
	auto k = q - (begin + 1 );
	if(index == k) // If the pivot value is the answer
	{
		return q;
	}
	else if(index < k)
	{
		return randomOrderStat(begin,q-1,lt,index);
	}
	else
	{
		return randomOrderStat(q + 1,begin,lt,index - (k+1));
	}
};
template<typename T,typename C,typename S>
T linearPartition(T begin, T end, C lt)
{	
	// First case with no remainder
	std::vector<typename T::value_type> storeOfMedianValues;
	int counter = 0;
	int lengthOfArray =  end - begin;
	int numberOfGroups = (lengthOfArray)/5; // The number of groups	
	int locationOfPivot;
		while(counter < numberOfGroups - 1)
		{
			insertionSort(begin+(counter*5), begin + (counter*5) + 5,lt); // Where ever the group starts(counter*5) until start + 5
			storeOfMedianValues.push_back(*(begin+(counter*5)+2));// Dereference the iteator to get the int. From start + 2 to get the median 
			counter+=1;
		}
		insertionSort(begin+(counter*5),end,lt);// Goes from counter*5, until end

	/* Break into groups of 5, 
	take median of each group, 
	take as pivot the median of medians (by calling select recursively)
	*/
		auto medianOfMedians = linearOrderStat(storeOfMedianValues.begin(),storeOfMedianValues.end(),lt,storeOfMedianValues.size()/2);
		// TO do the partition you need to know where the pivot is
		for(auto i = begin; i != end; i++ )
		{
			if(*i == medianOfMedians)
			{
				 locationOfPivot = i - begin; //Destination, sources // Gives i as int index
			}
		}
		iter_swap(begin + locationOfPivot,end - 1); // makes pivot point my last position
		return partitionFunction(begin,end,lt);

};
template<typename T,typename C,typename S>
T linearOrderStat(T begin, T end,C lt,S index)
{
	randomOrderStat(begin, end, lt, index);
};