#include <iostream>
#include "FileLinkedList.h"
#include <string>
#include <time.h>
#include <stdio.h>

using std::cout; 
using std::string;

FileLinkedList<int> container{"container.bin"}; 

void printArray()
{
    cout<<"\n"<<"Array Printing"<<"\n";
    for (int i = 0; i < container.size(); i++) 
    {
      cout << container[i] << ",";
    }
    cout<<"\n"<<"Array Printing Complete"<<"\n";
}

// int main(void) {
  
//     clock_t tStart = clock();
    
    
//     container.clear();

//     container.insert(container.begin(),70);  
//     container.insert(container.begin(),60);  
//     container.insert(container.begin(),50);  
//     container.insert(container.begin(),40);  
//     container.insert(container.begin(),30);  
//     container.insert(container.begin(),20);  
//     container.insert(container.begin(),10);  
//     container.insert(container.begin(),5);  
//     container.pop_back();
//     container.pop_back();
//     container.pop_back();
//     container.push_back(10);
//     container.push_back(10);
//     container.push_back(10);
//     container.erase(--(container.end()));
//     container.erase(--(container.end()));
//     container.erase(--(container.end()));
//     printArray();
//     container.clear();
//     for(int i = 0; i <= 2000; i++)
//     {
//         container.push_back(i);
//     }
//     printArray();

//     for(int i = 0; i <= 2000; i++)
//     {
//         container.push_back(i);
//     }
//     printArray();
//     for(int i = 0; i <= 2000; i++)
//     {
//         container.push_back(i);
//     }



int main(void) {
  int ts = 25;
  FileLinkedList<int> fal{"/tmp/fal"};
  fal.insert(fal.begin(), 69);
  for (int i = 0; i <= ts; i++) {
    fal.push_back(i);
  }
  
  cout << "elements: ";
  for (int i = 0; i < fal.size(); i++) {
    cout << fal[i] << ",";
  }
  cout << "\n";
  
  fal.pop_back();

  cout << "elements: ";
  for (int i = 0; i < fal.size(); i++) {
    cout << fal[i] << ",";
  }
  cout << "\n";

  cout << fal.size() << "size\n";
  fal.insert(fal.begin(), 69);
  fal.erase(fal.begin());
  fal.erase(fal.begin());
  fal.set(420, 3);
  fal.set(1337, fal.begin());

  cout << "elements: ";
  for (int i = 0; i < fal.size(); i++) {
    cout << fal[i] << ",";
  }
  cout << "\n";
  cout << fal.size() << "size\n";


  FileLinkedList<int> fCopy{fal.begin(), fal.end(), "/tmp/fCopy"};

  struct tester {
    int i;
    int ii;
    double asdf;
  };

     FileLinkedList<tester> fTester{"/tmp/fTester"};


    printArray();
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    return 0;
  
}



  
