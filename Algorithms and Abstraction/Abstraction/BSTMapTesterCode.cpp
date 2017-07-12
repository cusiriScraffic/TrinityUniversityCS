#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include "BSTMap.h"

using std::cout;
using std::string;
using std::pair;
using std::make_pair;


int main(void) {
  int ts = 50;

  struct tester {
    int n;
    char w;
    double k;
  };
  BSTMap<int,int> map0;
  BSTMap<int,int> map1;
  BSTMap<int,tester>mapBig;
  BSTMap<int,std::string>mapString;

    map0.insert(make_pair(69,420));
    map0.insert(make_pair(10,42));
    map0.insert(make_pair(1,422));
    map0.insert(make_pair(100,422));
    map0.insert(make_pair(691,4202));
    map0.insert(make_pair(123,4122));
    for (auto i = map0.begin(); i != map0.end(); ++i) 
    {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }
    cout<<"Test"<<"\n";
    map0.erase(map0.begin());
    cout<<"Testing"<<"\n";
    map0.erase(2);
    cout<<"Test 3"<<"\n";
    map0.erase(3);
    cout<<"Got here 1"<<"\n";
   for (auto i = map0.begin(); i != map0.end(); ++i) 
   {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }
    cout<< map0.size()<<"\n";
    cout<<"Got here 2 "<<"\n";
  if (map0.find(69)==map0.end()) cout << "69error\n";
  // cout<<"Got here of course 1"<<"\n";
  if (map0.count(69)==0) cout << "counterror\n";
  cout<<"Got here of course 2"<<"\n";
  for (int i = 1; i <= ts; i++) {
    map0.insert(std::make_pair(i,i));
    map1.insert(std::make_pair(i,i));
    mapString.insert(make_pair(i,"sajfdd"));
  if (map0.count(i)==0) cout << "counterror\n";
    cout<<"Got here of course"<<"\n";
     for (auto i = map0.begin(); i != map0.end(); ++i) 
   {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }
    for (auto i = map1.begin(); i != map1.end(); ++i) 
   {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }
    for (auto i = mapString.begin(); i != mapString.end(); ++i) 
   {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }
    if (map0[i] != i) cout << "[]error\n";
  }
  map0.insert(make_pair(1234,4321));
  map0[88] = 666;
  map0.erase(4);
  map0.erase(map0.begin());
  map1.insert(map0.begin(), map0.end());
  for (auto i = map0.begin(); i != map0.end(); ++i) {
    if ( map0[(*i).first] != (*i).second) cout << "error\n";
  }
  map1 = map0;
  if (map0!=map1) cout << "not equal\n";

  BSTMap<int,int> map3(map0);

  map0.erase(0);
  map0.insert(map1.begin(), map1.end());
  map0.erase(map0.begin());
  map0.insert(map0.erase(map0.begin()), map0.end());
  for (int i = 0; i < ts - 1; ++i) {
    map0.erase(i);
  }
  for (int i = ts; i < 2*ts; ++i) {
    map0.insert(std::make_pair(i,i));
  }
   for (auto i = map0.begin(); i != map0.end(); ++i) 
   {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }
  map1.clear();

  map0.clear();
  
   for (auto i = map0.begin(); i != map0.end(); ++i) 
   {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
    }

    cout<< "End"<<"\n";

  return 0;

};