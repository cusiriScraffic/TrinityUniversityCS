#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility> 
#include <time.h>
#include <string>

#ifndef HASH_MAP
#define HASH_MAP

using std::hash;
using std::pair;
using std::cout;

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash container and the number of elements.
    unsigned int numElems; // Keep track of number of elements, unisigned means it cant be negative
    std::vector<std::vector<std::pair<K,V> >> container; // Using 2D vector beacuse of collision

    public:

        typedef K key_type;
        typedef V mapped_type;
        typedef std::pair<K,V> value_type;

        class const_iterator;

        class iterator {
            // NOTE: These might be different depending on how you store your container.
            decltype(container.begin()) mainIter;
            decltype(container.begin()) mainEnd;
            decltype(container[0].begin()) subIter;

    public:
        friend class const_iterator;

        // NOTE: These might be different depending on how you store your container.
        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your container.
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
        // NOTE: These might be different depending on how you store your container.
        decltype(container.cbegin()) mainIter;
        decltype(container.cbegin()) mainEnd;
        decltype(container[0].cbegin()) subIter;
    public:
        // NOTE: These might be different depending on how you store your container.
        const_iterator(const decltype(container.cbegin()) mi,const decltype(container.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your container.
        const_iterator(const decltype(container.begin()) mi,
            const decltype(container.begin()) me,
            const decltype(container[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        // NOTE: These might be different depending on how you store your container.
        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {

        }

        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf): numElems(0), hashFunction(hf)
    {
        container.resize(5000);
    }; // Default constructor
    HashMap(const HashMap<K,V,Hash> &that): numElems(that.numElems), container(that.container), hashFunction(that.hashFunction)
    {
        container.resize(that.container.capacity());
    }; // Only if needed. Copy constructor
    // Might need a hash funciton, not sure 
    // Might even jsut comment out
    HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.
    // Might even jsut comment out
    bool empty() const
    {
        if(numElems==0)
        {
            cout<<"empty"<<"\n";
            return true;
        }
        else
        {
            cout<<"Not empty"<<"\n";
            return false;
        }
    };

    unsigned int size() const
    {
        return numElems;
    };

    iterator find(const key_type& k)
    {
        int index = keyToIndex(k);
        for(auto i = container[index].begin(); i != container[index].end(); i++)
        {
            if((*i).first == k) // *i givers key value pair, k compares different keys not index
            {
                return iterator(container.begin()+index, container.end(),i);
            }   
        }
        return end();

    }; // Takes in a key type returns an iterator (Key type is any type)

    const_iterator find(const key_type& k) const
    {
        int index = keyToIndex(k);
        for(auto i = container[index].cbegin(); i != container[index].cend(); i++)
        {
            if((*i).first == k) // *i givers key value pair, k compares different keys not index
            {
                return const_iterator(container.cbegin()+index, container.cend(),i);
            }   
        }       
        
        return cend(); 
       
    }; 

    int count(const key_type& k) const
    {
    
        int index = keyToIndex(k); // Specific key
        for (int i = 0; i < container[index].size(); ++i) 
        {
          if (container[index][i].first == k) 
            { 
                return 1; 
            } // Using first because it returns the key, but before it return a pair
        } // Unordered map does not allow duplicates at the same key, there only 1s and 0s are possible
        return 0; 
        
        
    };// Meant to return the number of items in a vector

    pair<iterator,bool> insert(const value_type& val)
    {
        // printf("Starting Insert method bool");
        clock_t tStart = clock();
        if (numElems > container.capacity() / 2) 
            {
                growcontainerAndRehash();
            }

        if (count(val.first) == 1) 
            { 
                return std::make_pair(find(val.first),false); 
            }
        container[keyToIndex(val.first)].push_back(val);

        numElems++;
        // printf("Time taken for Insert Bool method: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        // printf("Insert method finished");
        return std::make_pair(find(val.first), true); // u  -   the values to construct the pair from Return value
        

    };

    template <class InputIterator>
    
    void insert(InputIterator first, InputIterator last) 
    {
        // printf("Insert method void");
        clock_t tStart = clock();
        for(auto i = first; i!=last; i++)
        {
            insert(*i);
        }// From first to last, insert all the items i is an iterator, we want value
        // printf("Time taken for Insert Void method: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        // printf("Insert method void");
    }// This is a ranged insert

    iterator erase(const_iterator position)
    {
    
        erase((*position).first); // Erase value of *position just like a pointer
        return find((*position++).first);

    }; // Takes an iterator and erases at that spot
    int erase(const key_type& k)
    {
        int index = keyToIndex(k);
        for (auto i = container[index].begin(); i != container[index].end(); ++i) 
        {
          if ((*i).first == k) 
          {
            container[index].erase(i);
            numElems--;
            return 1;
          }
        }
        return 0;
    }; // Takes a key and erases at that spot

    void clear()
    {
        numElems = 0;
        container.clear();
        container.resize(10000); // And not clear(), for optimization
    }; // Not calling new so no need to worry about a destructor, not putting anything on the heap

    mapped_type &operator[](const K &key)
    {
        if (count(key) == 0) 
        {
          pair<K,V> p;
          p.first = key;
          auto inpair = insert(p);
          return (*(inpair.first)).second;
        } 
        else 
        {
            // printf("Time taken for Operator [] method: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
            return (*find(key)).second; // second meaning the value not the key
        }
     // Gets the first element of the pair which is the key
    };

    bool operator==(const HashMap<K,V,Hash>& rhs) const
    {
        if(rhs.size() != numElems)
        {
            return false;
        }
        // First make size that sizes are the same
        auto iterl = begin(); 
        // Create an iterator from my locale class
        for(auto iter = rhs.begin(); iter!= rhs.end(); iter++)
        {
            if(*iterl != *iter)
            {
                return false;
            }
            iterl ++;
        }
        return true;
    }; 

    bool operator!=(const HashMap<K,V,Hash>& rhs) const
    {
        return !(operator==(rhs));
    };

    iterator begin()
    {
        return iterator(container.begin(),container.end());
    };

    const_iterator begin() const
    {
        return const_iterator(container.begin(),container.end());
    };

    iterator end()
    {
        return iterator(container.end(),container.end());
    };

    const_iterator end() const
    {
        return const_iterator(container.end(),container.end());
    };

    const_iterator cbegin() const
    {
        return const_iterator(container.begin(),container.end());
    };

    const_iterator cend() const
    {
        return const_iterator(container.end(),container.end());
    };

private:
    void growcontainerAndRehash()
    {
        clock_t tStart = clock();
        std::vector<std::vector<pair<K,V> >> tmp = container;
        container.clear(); // must clear first
        container.resize(container.capacity() * 2 + 1); // Resize the container
        for (auto i = iterator(tmp.begin(), tmp.end()); i != iterator(tmp.end(), tmp.end()); ++i)
        {
              K key = (*i).first;
              V value = (*i).second;

         container[keyToIndex(key)].push_back(std::make_pair(key, value));
        } // Rehashing   
        // printf("Time taken for growcontainerAndRehash method: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    };
    int keyToIndex(const key_type& k) const 
    {
        return hashFunction(k)%container.capacity(); 
    } // This takes in a key type, hashes it then returns the index. 
    //Needed because it will be called alot and we need it to fix in our vector
};
#endif