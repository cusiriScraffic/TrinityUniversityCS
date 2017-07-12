#include <iostream>
#include <string>
#include "LinkedList.h"

using std::cout;
using std::string;

  LinkedList<int> lst;
  LinkedList<string> lst1;


 void printInt(int i)
{
	cout<<i<<",";
}

 void printString(string s)
{
	cout<<s<<"\n";
}

int main()
{
 
//push_back() pop_back() and operator[]
  for (int i = 1; i <= 1000; i++) {
    lst.push_back(i);
  }

  // pop_back() still broken
  int sz = lst.size();

  for ( int i = 0; i < 1000; ++i) {
    printInt(i);
    lst.pop_back();
    printInt(lst.size());
  }
  for (int i = 1; i <= 1000; i++) {
    lst.push_back(i);
  }
  lst.clear();
  printString("Testing Clear");
// size()
  printInt(lst.size());
  printString("size");
  printString("Testing Clear");
//Copy constructor, operator=
  LinkedList<int> lstCopy{lst};
  LinkedList<int> lstEquals; //try with elements
  lstEquals = lst;
//erase()
  for (int i = 1; i <= 10; i++) {
    lst.push_back(i);
  }
  lst.printArray();
  for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
    const auto &x = *iter;
  }
  lst.insert(lst.begin(), 1000);
  lst.printArray();
for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
    cout << *iter << "\n";
  }
  printInt(lst.size());
  printString("size");
  lst.erase(++lst.begin());
  for (auto iter = lst.cbegin(); iter != lst.cend(); iter++) {
    cout << *iter << "\n";
  }
  lst.isEmpty();
  lst.clear();
  for (int i = 0; i <= 10; i++) {
    lst1.push_back("i");
  }
  lst1.printArray();
  for (int i = 0; i <= 10; i++) {
    lst1.pop_back();
  }
  lst1.isEmpty();
  lst1.clear();
  printString("End");
  return 0;

};