#ifndef QUICK_SORT
#define QUICK_SORT
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template<typename T,typename C> T mpar(T begin, T end, const C &lt){
    T tmp = end-1;
    T i = begin;
        for(auto j = begin;j != end; ++j ){
            if (lt(*j,*tmp)){
               std::swap(*i, *j);
                i = i+1;
            }
        }
   std::swap(*i, *tmp);
    return i;
    }

template<typename T,typename C> void quicksort(T begin, T end,const C &lt){
   //find the lenght between begin and end make it greater than 1
   if(std::distance(begin, end) > 1){
    T tmp = mpar(begin, end, lt);
    quicksort(begin, tmp, lt);
    quicksort(tmp+1, end, lt);
    }
}
#endif
