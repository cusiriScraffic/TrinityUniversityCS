#include <iostream>
#include <string>

#include <utility>
#include <functional>
#include "HashMap.h"
#include <vector>

using std::cout;
using std::string;
using std::hash;
using std::pair;

// empty, size, count, non-ranged insert, find, 

int main(void) {
  int ts = 300;

  std::hash<int> ihash;
  HashMap<int,int,std::function<int(int)>> hashmap(ihash);
  HashMap<int,int,std::function<int(int)>> hash2(ihash);

  hashmap.empty();
  for (int i = 0; i < ts; i++) {
    hashmap.insert(std::make_pair(i,i));
    hash2.insert(std::make_pair(i,i));
    if (hashmap.count(i) != 1) cout << "error";
  }
  hashmap.empty();
  cout << "size=" << hashmap.size() << "\n";
  hashmap.erase(0);
  cout<<"Got here 1"<<"\n";
  hashmap.insert(hash2.begin(), hash2.end());
  cout<<"Got here 1"<<"\n";
  hashmap.erase(hashmap.begin());
  cout<<"Got here 1"<<"\n";
  hashmap.insert(hashmap.erase(hashmap.begin()), hashmap.end());
  cout<<"Got here 1"<<"\n";
  hashmap.empty();
  for (int i = 0; i < ts - 1; ++i) {
    hashmap.erase(i);
  }
  hashmap.empty();
  cout<<"Got here 2"<<"\n";
  for (int i = ts; i < 2*ts; ++i) {
    hashmap.insert(std::make_pair(i,i));
  }
  hashmap.empty();
  cout<<"Got here 3"<<"\n";
  for (auto i = hashmap.begin(); i != hashmap.end(); ++i) {
    cout << (*i).first << ",";
    cout << " second ";
    cout << (*i).second << "," << "\n";
  }
  hashmap.empty();
  cout<<"Got here 4"<<"\n";
  cout << "\n";
  hash2.clear();
  hash2[69] = 420;
  cout << "\n";

  if (hash2 == hashmap) {
    cout << "equal\n";
  }
  hashmap.empty();
  hashmap.clear();
  hashmap.empty();

  cout << "size=" << hashmap.size() << "\n";
  HashMap<int,int,std::function<int(int)>> hCopy = hashmap;
  if (hCopy != hashmap) {
    cout << "not equal error\n";
  }
cout<<"Finish"<<"\n";
  return 0;
}