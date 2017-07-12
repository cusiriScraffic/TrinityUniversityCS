#include <iostream>
#include <string>
#include "FileArrayList.h"

using std::cout;
using std::string;


 void printString(string s)
{
  cout<<s<<"\n";
}
 void printInt(int i)
{
  cout<<i<<","<<"\n";
}

int main() 
{
  FileArrayList<int> lst{"filename.bin"};
  FileArrayList<string> lst2{"file.bin"};

  lst.clear();
  lst2.clear();
  printString("Begun Unit Testing");
  for (int i = 0; i <= 10; i++) {
    lst.push_back(i);
  }
  printInt(lst.size()); 
  lst.insert(lst.begin(), 42);
  printString("Printing Size after insert");
  printInt(lst.size());
  printString("Printing Size after erase");
  lst.erase(lst.begin());
  printInt(lst.size());
  printInt(lst.size());
  printInt(lst.size());
  lst.set(69, 3);
  printString("Printing Size after set");
  printInt(lst.size());
  printString("Printing Size after erase and end()");
  lst.erase(lst.end());
  printInt(lst.size());
  printString("Before For loop\n");
  for (auto i : lst) {
    cout << i << ",";
  }
  printString("After for loop\n");
  printInt(lst.size());
  for (int i = 0; i < 10; i++) {
    lst.pop_back();  
  }
  cout << lst.size() << "lstsize\n";
  lst.clear();
  printString("Testing clear");
  printInt(lst.size());
  printString("Finished Unit Testing");
  printString("Testing for the Thousands");
  for (int i = 0; i <= 1000; i++) {
    lst.push_back(i);
  }
  printString("Push back to the thousands");
  for (auto i : lst) {
    cout << i << ",";
  }
  printString("Testing for 1000 pop back");
  for (int i = 0; i <= 1000; i++) {
    lst.pop_back();
  }
  lst.clear();
  printString("Finished The Thousands");
  
  struct test0{

  };
  printString("Testing different cases");
  for (int i = 0; i <= 1000; i++) {
    lst2.push_back("i");
  }
   for (auto i : lst2) {
    cout << i << ",";
  }
 struct Struct{
  int a;
  double d;
  char c;
};
  FileArrayList<Struct> f1{"Struct.bin"};
  
  Struct stack{1,2.0,'a'};

  for(int i = 0; i < 50; ++i)
  {
      f1.push_back(stack);
  }

  f1.clear();

  printString("Complete testing");

  return 0;
};