#ifndef ARRAYLIST
#define ARRAYLIST
#include <iostream>

using std::cout;

template<typename T>

class ArrayList 
{
    private:
        T* container; // Pointer of type T pointing to and array containers
        int num; // Number of elements within the array list 
        int length; // length of list

    public:
        // Custom Functions
        void GrowContainer()
        {
            T* tmp ; // creating a new pointer to a list of type T
            tmp = new T[length*2]; // expanding the length of the list
            for(int i = 0; i < num ; ++i) 
            {
                tmp[i] = container[i];
            }
            delete [] container;
            container = tmp;
            length = length*2;
        }
    
    class iterator
    {
        private:
            T* iter; // Jiang said it behaves like a pointer, so treat like one
        public:
            iterator(T *l) : iter(l){};
            iterator() : iter(nullptr){}; 
            iterator(const iterator &i) : iter(i.iter){}; // Iterator copy constructor 

             T &operator*()
             {
                return *iter; // Dereferencing operator returns information on the current object
             };
            bool operator==(const iterator &i) const 
            {
                return i.iter == iter;
            };
            bool operator!=(const iterator &i) const 
            {   
                return  i.iter != iter;
            };
            iterator &operator=(const iterator &i)
            {
                iter = i.iter;
                return *this;
            };
            iterator &operator++()
            {
                ++iter; // This is the current iterator that you are working on this.next()
                return *this;
            };
            iterator &operator--()
            {
                --iter; // This is the current iterator that you are working on this.next()
                return *this;
            };
            iterator operator++(int)
            {
                auto tmp = *this; // returning what I have currently 
                ++iter;
                return tmp;
            };
            iterator operator--(int)
            {
                auto tmp = *this ;// returning what I have currently
                --iter;
                return tmp;
            };
    };// iterator
    
    class const_iterator // Used when printing. Iterator doesn't change values
    {
        private:
            T* iter;
        public: 
            const_iterator(T *l) : iter(l){};
            const_iterator() : iter(nullptr){}; 
            const_iterator(const const_iterator &i) : iter(i.iter){}; // Const iterator copy constructor

             const T &operator*()
             {
                return *iter; // Just returns *iter
             };
            bool operator==(const const_iterator &i) const 
            {
              return i.iter == iter;
            };
            bool operator!=(const const_iterator &i) const 
            {   
                 return i.iter != iter;
            };
            const_iterator &operator=(const const_iterator &i)
            {
                iter = i.iter; // left hand side is the pointer and right hand side is the const iterator
                return *this;
            }; // return current opject
            const_iterator &operator++()
            {
                ++iter; // This pointer to iterator obejct, 
                return *this; // To return the current object
            };
            const_iterator &operator--()
            {
                -- iter;
                return *this;// To return the current object
            };
            const_iterator operator++(int)
            {
                auto tmp = *this;// Must be *this because im making a copy of myself
                ++iter; 
                return tmp;
            };
            const_iterator operator--(int)
            {
                auto tmp = *this;// Must be *this because im making a copy of myself
                --iter; 
                return tmp;
            };   
    };// const_iterator
        
        // General Methods
        ArrayList() : container(new T[10]),num(0),length(10) {}; // Default Constructor , initializing the constructor(basically a container with no values)
        
        ArrayList(const ArrayList &that) : container(new T[that.length]), num(that.num), length(that.length)
        {
            for(int i = 0; i < num ; ++i) 
            {
                container[i] = that.container[i];
            }
        }; // copy constructor
        
        //operators,        
        ArrayList<T> &operator=(const ArrayList<T> &al)
        {
            delete [] container ;
            container = new T[al.length]; // Albert how does this desstruct
            length = al.length;
            num = al.num;
            for( int i = 0; i < num ; ++i)
            {
                container[i] = al.container[i];      
            }          
        }; // Copy assignment operator
        
        ~ArrayList() 
        { 
           delete [] container; 
        }; // Destructor

        bool isEmpty() 
        {
            if(num == 0)
            {
                cout << "List is empty \n" ;
                return true;
            }
            else 
            {
                cout<< "Not empty\n";
                return false;
            }
            
        }

        void push_back(const T &t)
        {
            if(num == length) // check if its full
            {
                GrowContainer();
            }
            container[num]= t;
            num++;

        }; // add to the end.
        
        void pop_back()
        {
            num -- ;
        };              // remove last element.

        int size() const 
        {
            return num; // Just returns the number of elements
        };

        void clear()
        {
            num = 0;
        };

        void insert(const T &t,int index) 
        {   // insert this element before the given index.
        // If you would like to insert into an array at a given position, the item originally at the given index must be moved up one position and all items after that must shuffle up
            if(num == length)
            {
                GrowContainer();
            }
            for(int position = num ; position > index; position --) // Make room for new element by shifiting all itmes at postion >= index towards the end of the list to the right
            {
                container[position] = container[position-1];
            }
            container[index] = t;// This inserts the new elements into position index
            num++;
        };
        
        const T &operator[](int index) const
        {
            return container[index];
        }; // get the element at index.

        T &operator[](int index)
        {
            return container[index]; // Just returns the index
        };             // get the element at index.

        void remove(int index)
        {
            if(index < 0 || index > num)
            { 
                cout<<"No current element\n";
            }
            else { 
                
                for(int i = index; i < num-1; i++)
                {
                    container[i] = container[i+1]; // Shifts everything to the left
                }
                    num -- ; // Reduce the size of elements
            }
        };               // remove the item at the given index.

        iterator begin()
        {
            return &container[0]; // This just returns the first element in the conatiner
        };

        iterator end()
        {
            return &container[0] + num;// Need to return the address beyond the last element which is data + number of elements
        };
         const_iterator begin() const
        {
            return &container[0]; // This just returns the first element in the conatiner
        };

        const_iterator end() const
        {
            return &container[0] + num;// Need to return the address beyond the last element which is data + number of elements
        };

        const_iterator cbegin() const
        {
            return &container[0]; // This just returns the first element in the conatiner
        };

        const_iterator cend() const
        {
            return (&container[0]) + num; // Need to return the address beyond the last element which is data + number of elements
        };
};  
#endif
