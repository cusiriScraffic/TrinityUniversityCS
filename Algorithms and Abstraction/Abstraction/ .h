#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>

using std::cout;
template<typename T>

class LinkedList 
{
    private:        
            struct Node 
            {
                Node(Node* n, Node* p) : next(n),prev(p){};
                Node(const T& d, Node* y, Node* z ): data(d),next(y),prev(z){}; // Tmp Node constructor, Creates list nodes
                Node* prev; // Node has pointer to predecessor 
                Node* next; // Node has pointer to successor 
                T data;     // Element of type T
            };
            
            int numNodes; // Size or number of Nodes
            Node* Sentinel; // How do I create the node
    public:
            typedef T value_type; 

                // Public Funtions
            class iterator {
                private: 
                    Node* iter;
                public:
                    //Iterator Constructors
                    iterator():iter(nullptr){}; 
                    iterator(Node* l ):iter(l){};
                    iterator(const iterator &i): iter(i.iter){};//Copy Constructor 
                    T &operator*() {return iter -> data;}; // Dereferencing iterator returns info on current node,  fetch data referenced by an iterator

                    //Iterators Operations
                    bool operator==(const iterator &i) const 
                    {
                        return iter == i.iter;
                    }
                    bool operator!=(const iterator &i) const 
                    {
                        return iter != i.iter;
                    }
                    iterator &operator=(const iterator &i) 
                    {   
                        iter = i.iter;
                        return *this; 
                    }
                    iterator &operator++() 
                    {
                        iter = iter-> next;
                        return *this;
                    }// Prefix, iterate and return curent object ++it
                    iterator &operator--() 
                    {
                        iter = iter-> prev;
                        return *this;
                    }// Prefix, iterate and return curent object --it
                    iterator operator++(int) 
                    {
                        iterator tmp = *this; // iterator tmp = *this  
                        iter = iter -> next;
                        return tmp;
                    } // Post fix save object, iterate, return object before it++
                    iterator operator--(int) 
                    {
                        iterator tmp = *this; // iterator tmp = *this
                        tmp = tmp -> prev;
                        return tmp;
                    }// Post fix save object, iterate, return object before it--
                    friend class const_iterator;
                    friend class LinkedList;
                        
                    };
        class const_iterator {
                Node* iter;
                        // Data
                public:
                    //Iterator Constructors    
                    const_iterator(Node* l ): iter(l){};
                    const_iterator():iter(nullptr){};
                    const_iterator(const const_iterator &i): iter(i.iter){};//Copy Constructor
                    const T &operator*()  
                    {
                    return iter -> data;
                    }; // Dereferencing iterator returns info on current node
            
                    bool operator==(const const_iterator &i) const 
                    {
                        return iter = i.iter;
                    }
                    bool operator!=(const const_iterator &i) const 
                    {
                        return iter!=i.iter;
                    }
                    const_iterator &operator=(const const_iterator &i) 
                    {
                        iter = i.iter;
                        return *this;
                    }// Dereferneces and returns the current values
                    const_iterator &operator++() 
                    {
                        iter = iter-> next;
                        return *this;
                    }
                    const_iterator &operator--() 
                    {
                        iter = iter -> prev;
                        return *this;
                    }
                    const_iterator operator++(int) 
                    {
                     const_iterator tmp = *this;
                     iter = iter -> next;
                     return tmp;
                    }
                    const_iterator operator--(int) 
                    {
                        const_iterator tmp = *this;
                        iter = iter -> prev;
                        return tmp;
                    }
                    
                    friend class iterator;
                    friend class LinkedList;
    };              


    LinkedList():numNodes(0),Sentinel((new Node(nullptr,nullptr)))//inline construction
    {
        Sentinel->next = Sentinel;
        Sentinel->prev = Sentinel;
    };
    //Constructors
    LinkedList(const LinkedList &that) :numNodes(0),Sentinel((new Node(nullptr,nullptr))) /*numNodes(0),Sentinel(that.Sentinel) */
    {    
        // All we need to do is create an empty list
        Sentinel->next = Sentinel;
        Sentinel->prev = Sentinel;

        for (T d : that) 
            { 
                push_back(d); 
            }
    } 

    LinkedList &operator=(const LinkedList &al) 
    {
        clear();
        for (T d : al) { push_back(d); }
        numNodes = al.numNodes;
        return *this;
    } //Copy assignment operator 
    ~LinkedList() 
    {
        clear();
        delete Sentinel;
    } // Destructors

     void push_back(const T &t)
    {
        insert(end(),t);
    }// add to the end.
    void pop_back()
    {
        erase(--end());
    }// remove last element.
    int size() const
    {
        return numNodes;
    }
     void clear()
    {
        while(!isEmpty())
        {
            pop_back();
        }
        numNodes = 0;
    }
    bool isEmpty()
    {
        return (numNodes == 0);
    }
    inline iterator insert(iterator position,const T &t)
    {   
        Node* tmp  = new Node(t,Sentinel->prev,Sentinel->next); // refeerence to the node before 
        tmp -> prev = position.iter->prev;
        tmp -> next = position.iter;
        position.iter->prev->next = tmp;
        position.iter->prev = tmp;

        numNodes++;
        return iterator(tmp); // returns address of type t

    };    // insert this element before the given index.
    const T &operator[](int index) const
    {
        Node* tmp ;
        tmp = Sentinel->next;
        for(int i = 0; i< index; i++)
        {
            tmp = tmp-> next;
        }
        return tmp->data;
    };// get the element at index.
    T &operator[](int index)
    {
        Node* tmp;
        tmp = Sentinel->next;
        for (int i = 0; i < index; i++) 
        {
        tmp = tmp->next;
        }
    return tmp->data;
    };// get the element at index.
    inline iterator erase(iterator position)
    {
        Node* tmp = position.iter -> next;
        position.iter -> prev -> next = position.iter -> next;
        position.iter -> next->prev = position.iter->prev;
        delete position.iter;
        numNodes --;
        return iterator(tmp);
    };               // remove the item at the given index. Place delete inside the erase

    iterator begin()
    {
        return iterator(Sentinel->next);
    };
    iterator end()
    {
        return iterator(Sentinel);
    };
    const_iterator begin() const
    {
        return const_iterator(Sentinel->next);
    };
    const_iterator end() const
    {
        return const_iterator(Sentinel);
    };
    const_iterator cbegin() const
    {
        return const_iterator(Sentinel->next);
    };
    const_iterator cend() const
    {
        return const_iterator(Sentinel);
    };
        void printArray() 
        {
             Node* n = Sentinel->next;   
            for (int i = 0; i < size(); i++) 
            {    
                cout<<n->data<<": next ="<<n-> next-> data<< ": prev"<< n-> prev -> data<<"\n";
                n = n -> next;
            }

        }
        
};
#endif