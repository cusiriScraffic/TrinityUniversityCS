
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template<typename T, typename K>
void countSort(T begin, T end, K keyFunc, int mod){
     std::vector<int> Counting(10);
     std::vector<typename T::value_type> tmp(end-begin);

     for(int i = 0; i<10; i++) {
        Counting[i] =0;
     }
     for(int i = 0; i<(end-begin); i++){
	int bucket = (keyFunc(*(begin+i))/mod) % 10;
        Counting[bucket]++;
     }
     for(int i = 1; i <10; i++){
	Counting[i] += Counting[i-1];
     }

     for(int i = (end-begin) -1; i >=0; i--){
	int index = (keyFunc(*(begin+i))/mod)%10;
	Counting[index]--; 
	tmp[Counting[index]] = *(begin+i);
     }
     
     for(int i = 0; i<(end-begin); i++) {
        *(begin+i) = tmp[i];
     }
} 


template<typename T,typename K>
void radixSort(T begin,T end,K keyFunc){
  int sz = end - begin;
  int maxElem = 0;
  for (int i = 0; i < sz; i++) {
     if( keyFunc(*(begin+i)) > maxElem) {maxElem = keyFunc(*(begin+i));} 
  } 

  for(int mod = 1; maxElem/mod>0; mod*=10){
     countSort(begin, end, keyFunc, mod);
  } 
}
