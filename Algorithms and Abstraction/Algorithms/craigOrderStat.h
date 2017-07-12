//Problem 3
//Team H
#include <cstdlib>
#include <ctime>
#include <iostream>

template<typename T>
void debugPrint(T begin, T end) {
    for(auto iter = begin; iter!=(end+1); iter++) {
        std::cout<<*iter<<',';
    }
    std::cout<<'\n';
}

//srand must be called first
int randomNum(int i, int j) {
    int r = rand();
    return i + r%(j-i);
}

template<typename T, typename C>
bool lessOrEqual(T a, T b, C lt) {
    if(lt(*a,*b)) {
        return true;
    } else {
        bool ret = !lt(*a,*b) && !lt(*b,*a);
        return ret;
    }    
}

template<typename T>
void exchange(T a, T b) {
    auto tmp = *a;
    *a = *b;
    *b = tmp;
    
}

template<typename T, typename C>
T part(T p, T r, const C &lt) {
    //std::cout<<"Calling part";
    //debugPrint(p,r);
    //std::cout<<"Part2: ";
    //debugPrint(p,r);
    T x = r;
    T i = p-1;
    for(auto j = p; j!=r; j++) {
        if(lessOrEqual(j,x,lt)) {
            i++;
            std::swap(*i,*j);
        }
    }
    exchange(i+1,r);
    //std::cout<<"Part3: ";
    //debugPrint(p,r);
    return i+1;
}

template<typename T, typename C>
T randomPartition(T begin, T last, C lt) {
    //std::cout<<"Calling randomPartition";
    //debugPrint(begin,last);
    srand(time(NULL));
    //std::cout<<"Part1: ";
    //debugPrint(begin,last);
    int i = randomNum(0,(last-begin));
    std::swap(*(begin+i), *last);
    T ret = part(begin, last, lt);
    return ret;
}

template<typename T, typename C, typename S>
T randomizedSelect(T p, T r, C lt, S index) {
    //std::cout<<"Calling randomizedSelect: ";
    //debugPrint(p, r);
    if(p>=r) {
        return p;
    }
    T q = randomPartition(p,r,lt);
    S k = (q-p);
    //std::cout<<"*p = " << *p << '\n';
    //std::cout<<"k = " << k << '\n';
    //std::cout<<"*q = " << *q <<'\n';
    //std::cout<<"i = " << index << '\n';
    if(index==k) {
        return q;
    } else if(index<k) {
        return randomizedSelect(p, q-1, lt, index);
    } else {
        return randomizedSelect(q+1, r, lt, index-(k+1));
    }
}


template<typename T, typename C, typename S>
T randomOrderStat(T begin, T end, C lt, S index) {
    return randomizedSelect(begin, end-1, lt, index);
}


template<typename T, typename C, typename S>
T linearOrderStat(T begin, T end, C lt, S index) {
    return randomOrderStat(begin,end,lt,index);
}


