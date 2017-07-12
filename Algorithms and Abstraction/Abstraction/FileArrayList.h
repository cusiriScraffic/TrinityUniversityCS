#ifndef FILEARRAYLIST
#define FILEARRAYLIST

#include <cstdio> // C Standard Input Output Library
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
/*
This library uses what are called streams to operate with 
physical devices such as keyboards, printers, terminals or 
with any other type of files supported by the system. Streams 
are an abstraction to interact with these in an uniform way; 
All streams have similar properties independently of the 
individual characteristics of the physical media they are 
associated with.
*/
/*
Streams are handled in the cstdio library as pointers to FILE 
objects. A pointer to a FILE object uniquely identifies a stream, 
and is used as a parameter in the operations involving that stream.
*/
template<typename T>

class FileArrayList {
        // Basically saying that these operations are not allowed
    FileArrayList(const FileArrayList<T> &that) = delete;
    FileArrayList<T> operator=(const FileArrayList<T> &that) = delete; //asignment opertor
    
    private: 
    
        int numElems;
        FILE* file; // Pointer to a file object could be = fopen("hello.bin","w+"); // w+ because it doesnt exist 

        // TODO - Private helper functions. (Maybe file IO with an index.)
    public:

        inline static T readElem(int i,FILE* file)
        {
            fseek(file,sizeof(int) + i*sizeof(T),SEEK_SET); // SEEK_SET means begining of file, This locations that postition of the object
            // would be 2* size if i kept a capacity          
            T tmp; // Pointer to a block of memeory
            fread(&tmp,sizeof(T),1,file); // This reads block of data from the stream
            return tmp; // Returns the data, cant have a reference to memory using a file, deref 
        }
        inline void writeElem(const T& t,int index)
        {
            fseek(file, sizeof(int) + index*sizeof(T),SEEK_SET);
            fwrite(&t,sizeof(T),1,file);
        }
        inline void changeSize()
        {
            fseek(file,0,SEEK_SET);
            fwrite(&numElems,sizeof(int),1,file);
        }

        typedef T value_type;

        class const_iterator {
               int index;
               FILE* file;

                // TODO - Your private data.
                public:
                // Const_iterator constructors
                const_iterator(int i,FILE *f):index(i),file(f){};
                const_iterator(const const_iterator &i):index(i.index),file(i.file){};
                T operator*()
                {
                    return readElem(index,file);// I should be able to do this here because readElems is static
                };// Returns the current element. make readElem() static and pass File*
                
                bool operator==(const const_iterator &i) const
                {
                    return ((index==i.index)&&(file==i.file));
                };
                bool operator!=(const const_iterator &i) const
                {
                    return((index!=i.index)||(file!=i.file));
                };
                const_iterator &operator=(const const_iterator &i)
                {
                    index=i.index;
                    return *this;
                };
                const_iterator &operator++()
                {
                    ++index;
                    return *this;
                };
                const_iterator &operator--()
                {
                    --index;
                    return *this;
                };
                const_iterator operator++(int)
                {
                    const_iterator tmp = *this;
                    ++index;
                    return tmp;
                };
                const_iterator operator--(int)
                {  
                    const_iterator tmp = *this;
                    --index;
                    return tmp;
                };

                friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname)
        {
             file = fopen(fname.c_str(),"r+b");
            if(file==nullptr)
            {
                cout<<"File does not exsits\n"<<endl;
                file = fopen(fname.c_str(),"w+b");
                numElems = 0;
                changeSize();
            }else
            {
                fread(&numElems,sizeof(int),1,file);
                changeSize();
            }
        };//Constructor

        template<typename I>  // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
            file = fopen(fname.c_str(),"w+b");
            numElems=0;
            changeSize();
            for(I i = begin;  i!= end; i++) 
            {
                push_back(*i);
            }
        }
        ~FileArrayList()
        {
            fclose(file);
        }; // Destructor

        void push_back(const T &t)
        {
            writeElem(t,numElems);
            numElems++;
            changeSize();
            // insert(numElems,t); // Insert(numElements) is the end of the array?
        };

        void pop_back()
        {
            numElems--;
            changeSize();
        };

        int size() const
        {
            return numElems;
        };

        void clear()
        {
            numElems = 0;e
            changeSize();
        };

        const_iterator insert(const_iterator position, const T &t)
        {
        
            for(int i = numElems; i >= position.index + 1; i--)
                {
                    writeElem(readElem(i-1,file),i); // Shifts everything to the right from right to left
                }
            writeElem(t,position.index);
            numElems++;
            changeSize();
            return position;
        };

        T operator[](int index) const
        {
            return readElem(index,file);
        };// Returns the current object at position index

        const_iterator erase(const_iterator position)
        {
            for(int i = position.index; i < numElems-1; i++)
                {
                    writeElem(readElem(i+1,file),i);
                }
            numElems--;
            changeSize();
            return position; 
        }; // Goes left to right shifting everything to the right

        void set(const T &value,int index) 
        {
            writeElem(value,index);
        }; // Need a set now becuase it is file based. call readElem

        const_iterator begin()
        {
            return const_iterator(0,file);
        };
        const_iterator begin() const
        {
           return const_iterator(0,file);
        };
        const_iterator end()
        {
            return const_iterator(numElems,file);
        };
        const_iterator end() const
        {
          return const_iterator(numElems,file);
        };
        const_iterator cbegin() const
        {
         return const_iterator(0,file);
        };
        const_iterator cend() const
        {
        return const_iterator(numElems,file);
        };
    };
#endif