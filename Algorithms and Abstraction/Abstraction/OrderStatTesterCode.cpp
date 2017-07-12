#include <iostream>
#include <string>
#include <utility>
#include <iterator>
#include "OrderStat.h"
#include <list>

using std::string;
using std::cout;
using std::cin;
using std::list;
using std::advance;
int main(){

	OrderStat<int> tree1;
    list<int> list1;
	  
    //testing push_front
    for(int i  = 0; i < 10; ++i){
		int r = rand()%100;
        tree1.push_front(r);
        list1.push_front(r);
	}
    
    if(tree1.size() != list1.size())
        cout<<"Wrong size after push_front.\n";
    else if(tree1.front() != list1.front() || tree1.back() != list1.back())
        cout<<"Wrong front/back after push_front\n";
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong push_front.\n";
                break;
            }
            ++tmpi;
        }
        cout<<"Passed push_front()\n";
    }
    //testing push_back
	for(int i  = 0; i < 30; ++i){
		int r = rand()%100;
        tree1.push_back(r);
        list1.push_back(r);
	}
    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after push_back.\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after push_back\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after push_back\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong push_back.\n";
                break;
            }
            ++tmpi;
        }
        cout<<"Passed push_back()\n";
    }
   
    //testing operator[]
    unsigned currentSize = tree1.size();
    bool bracket = true;
    auto biter = list1.begin();
    for(int i = 0; i < currentSize; ++i){
        if(tree1[i] != *biter){
            cout<<"Wrong operator[]\n";
            cout<<"Tree["<<i<<"] is: "<<tree1[i]<<", should be: "<<*biter<<"\n";
            bracket = false;
        }
        ++biter;
    }
    if(bracket){cout<<"Passed operator[]\n";}

    //testing erase begin()
    for(int i  = 0; i < 5; ++i){
        int r = rand()%100;
        tree1.erase(tree1.begin());
        list1.erase(list1.begin());
    }

    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after erase begin().\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after erase begin()\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after erase begin()\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong erase begin().\n";
                cout<<"Tree's current node is: "<<*i<<", should be: "<<list1.back()<<"\n";
                //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
                
                break;
            }
            ++tmpi;
        }
        cout<<"Passed erase begin()\n";
    }

    //testing erase ++begin()
    for(int i  = 0; i < 5; ++i){
        int r = rand()%100;
        tree1.erase(++tree1.begin());
        list1.erase(++list1.begin());
    }

    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after erase ++begin().\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after erase ++begin()\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after erase ++begin()\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong erase ++begin().\n";
                cout<<"Tree's current node is: "<<*i<<", should be: "<<list1.back()<<"\n";
                //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
                
                break;
            }
            ++tmpi;
        }
        cout<<"Passed erase ++begin()\n";
    }

    //testing erase --end()
    for(int i  = 0; i < 5; ++i){
        int r = rand()%100;
        tree1.erase(--tree1.end());
        list1.erase(--list1.end());
    }

    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after erase --end().\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after erase --end()\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after erase --end()\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong erase --end().\n";
                cout<<"Tree's current node is: "<<*i<<", should be: "<<list1.back()<<"\n";
                //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
                
                break;
            }
            ++tmpi;
        }
        cout<<"Passed erase --end()\n";
    }

    

    //testing clear()
    tree1.clear();
    list1.clear();

    if(tree1.size() != list1.size()){
        cout<<"Wrong size after clear.\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong clear.\n";
                cout<<"Tree's current node is: "<<*i<<", should be: "<<list1.back()<<"\n";
            }
            ++tmpi;
        }
        cout<<"Passed clear\n";
    }


    //testing insert(--end())
    tree1.push_back(100);
    list1.push_back(100);
    for(int i  = 0; i < 10; ++i){
        int r = rand()%100;
        tree1.insert(--(tree1.end()), r);
        list1.insert(--(list1.end()), r);
    }

    auto printOut = [tree1, list1](){
        cout<<"Printing out the tree in order: \n";
        for(auto i: tree1){
            cout<<i<<"\n";
        }
        cout<<"Printing out the list in order: \n";
        for(auto i: list1){
            cout<<i<<"\n";
        }
    };
    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after insert --end().\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after insert --end()\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
        cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
        bool p;
        cin>>p;
        if(p) printOut();
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after insert --end()\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
        cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
        bool p;
        cin>>p;
        if(p) printOut();
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong insert --end().\n";
                cout<<"Tree's current node is: "<<*i<<", should be: "<<list1.back()<<"\n";
                cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
                bool p;
                cin>>p;
                if(p) printOut();
                break;
            }
            ++tmpi;
        }
        cout<<"Passed insert --end()\n";
    }

    //testing insert ++begin()

    for(int i  = 0; i < 10; ++i){
        int r = rand()%100;
        tree1.insert(++(tree1.begin()), r);
        list1.insert(++(list1.begin()), r);
    }

    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after insert ++begin().\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after insert ++begin()\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after insert ++begin()\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
        //cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong insert ++begin().\n";
                cout<<"Tree's current node is: "<<*i<<", should be: "<<list1.back()<<"\n";
                cout<<"Do you want the tree and list printed out? 1 for yes & 0 for no\n";
                
                break;
            }
            ++tmpi;
        }
        cout<<"Passed insert ++begin()\n";
    }
    
	OrderStat<int>tree2(tree1);
	//tree2.pop_front();
	if(tree1.size() != list1.size()){
        cout<<"Wrong size after copy constructor.\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after copy constructor\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after copy constructor\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong copy constructor.\n";
                break;
            }
            ++tmpi;
        }
        cout<<"Passed copy constructor()\n";
    }
	
    //testing list insert
    tree1.clear();
    tree1.insert(tree1.begin(), tree2.begin(), tree2.end());

    if(tree1.size() != list1.size()){
        cout<<"Wrong size after list insert.\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after list insert\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after list insert\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong list insert.\n";
                break;
            }
            ++tmpi;
        }
        cout<<"Passed list insert\n";
    }
    
    if(tree1 == tree2){cout<<"Passed operator==()\n";}

    //testing pop_back()
    for(int i  = 0; i < 10; ++i){
        int r = rand()%100;
        tree1.pop_back();
        list1.pop_back();
    }
    
    if(tree1.size() != list1.size()){
        cout<<"Wrong size after pop_back.\n";
        cout<<"Tree's size is: "<<tree1.size()<<", should be: "<<list1.size()<<"\n";
    }
    else if(tree1.front() != list1.front()){
        cout<<"Wrong front after pop_back\n";
        cout<<"Tree's front is: "<<tree1.front()<<", should be: "<<list1.front()<<"\n";
    }
    else if(tree1.back() != list1.back()){
        cout<<"Wrong back after pop_back\n";
        cout<<"Tree's back is: "<<tree1.back()<<", should be: "<<list1.back()<<"\n";
    }
    else{
        auto tmpi = list1.begin();
        for(auto i = tree1.begin(); i != tree1.end(); ++i){
            if(*i !=  *tmpi){
                cout<<"Wrong pop_back.\n";
                break;
            }
            ++tmpi;
        }
        cout<<"Passed pop_back()\n";
    }
}