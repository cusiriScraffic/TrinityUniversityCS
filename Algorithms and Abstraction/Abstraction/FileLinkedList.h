
#include <stdio.h>
#include <cstdio> // C Standard Input Output Library
#include <string>
#include <iostream>
using std::string;
using std::cout;


template<typename T>
class FileLinkedList {
  FileLinkedList(const FileLinkedList<T> &that) = delete;
  FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;
  
    private:
        FILE* file; // ptr to file object
        int numElems;  // number of elements within file
        int free; // pointer to first free node 
        char buf[BUFSIZ];
  
    public:
    int getNext(int index) const 
    {
    fseek(file, 2*sizeof(int) + index*(2*sizeof(int) + sizeof(T)) + sizeof(int) + sizeof(T), SEEK_SET);
    int tmp;
    fread(&tmp, sizeof(int), 1, file);
    return tmp;
    }
    int getPrev(int index) const 
    {
    fseek(file, 2*sizeof(int) + index*(2*sizeof(int) + sizeof(T)) + sizeof(T), SEEK_SET);
    int tmp;
    fread(&tmp, sizeof(int), 1, file);
    return tmp;
    }
    void writeNext(int index, int next) 
    {
    fseek(file, 2*sizeof(int) + index*(2*sizeof(int) + sizeof(T)) + sizeof(int) + sizeof(T), SEEK_SET);
    fwrite(&next, sizeof(int), 1, file);
    }
    void writePrev(int index, int prev) 
    {
    fseek(file, 2*sizeof(int) + index*(2*sizeof(int) + sizeof(T))+ sizeof(T), SEEK_SET);
    fwrite(&prev, sizeof(int), 1, file);
    }
    void writeElems(int index, const T &t) 
    {
    fseek(file, 2*sizeof(int) + index*(2*sizeof(int) + sizeof(T)), SEEK_SET);
    fwrite(&t, sizeof(T), 1, file);
    }
    static T readElems(int index,FILE* file) 
    {
    fseek(file, 2*sizeof(int) + index*(2*sizeof(int) + sizeof(T)), SEEK_SET);
    T tmp;
    fread(&tmp, sizeof(T), 1, file);
    return tmp;
    }
    void changeFile() 
    {
    fseek(file, 0, SEEK_SET);
    fwrite(&numElems, sizeof(int), 1, file);
    fseek(file, sizeof(int), SEEK_SET);
    fwrite(&free, sizeof(int), 1, file);
    }
    
    typedef T value_type;

    class const_iterator 
    {
    private: 
        int index;
        FILE* file;
    public:
        const_iterator(int i, FILE* f) : index(i), file(f) {}
        const_iterator(const const_iterator &i) : index(i.index), file(i.file) {}
        T operator*()
        {
            return readElems(index,file);
        }
        bool operator==(const const_iterator &i) const
        {
            return ((index==i.index)&&(file == i.file));
        };
        bool operator!=(const const_iterator &i) const
        {
            return ((index!= i.index)||(file!=i.file));
        };
        const_iterator &operator=(const const_iterator &i)
        {
            index = i.index;
            file = i.file;
            return *this;
        };
        const_iterator &operator++()
        {
        fseek(file, 2*sizeof(int) + index * (2*sizeof(int) + sizeof(T)) + sizeof(int) + sizeof(T), SEEK_SET);
        fread(&index, sizeof(int), 1, file);
        return *this;
        }
        const_iterator &operator--()
        {
        fseek(file, 2*sizeof(int) + index * (2*sizeof(int) + sizeof(T)) + sizeof(T), SEEK_SET);
        fread(&index, sizeof(int), 1, file);
        return *this;
        }
        const_iterator operator++(int) 
        {
        int tmp = index;
        fseek(file, 2*sizeof(int) + index * (2*sizeof(int) + sizeof(T)) + sizeof(int)+ sizeof(T), SEEK_SET);
        fread(&index, sizeof(int), 1, file);
        return const_iterator(tmp, file);
        }
        const_iterator operator--(int) 
        {
        int tmp = index;
        fseek(file, 2*sizeof(int) + index * (2*sizeof(int) + sizeof(T)) + sizeof(T), SEEK_SET);
        fread(&index, sizeof(int), 1, file);
        return const_iterator(tmp, file);
        }

      friend class FileLinkedList;
  };

  // Constructors
  FileLinkedList(const std::string &fname)
  {
    file = fopen(fname.c_str(), "r+b");
    if (file == nullptr) 
    {
      file = fopen(fname.c_str(), "w+b");
      numElems = 0;
      free = -1;
      T tmp;
      writeElems(0,tmp);
      writeNext(0, 0);
      writePrev(0, 0);
      changeFile();
    } 
    else 
    {
      fseek(file, 0, SEEK_SET);
      fread(&numElems, sizeof(int), 1, file);
      fseek(file, sizeof(int), SEEK_SET);
      fread(&free, sizeof(int), 1, file);
    }
    setbuf(file,buf); // Buffer
  }

  template<typename I> // type I will be an iterator
  FileLinkedList(I begin, I end, const std::string &fname) 
  { 
  //essentially copy constructor
    file = fopen(fname.c_str(), "w+b");
    setbuf(file,buf); // Buffer
    numElems = 0;
    free = -1;
    changeFile();
    //for (auto i = end; i != begin; --i) {
    for (auto i = begin; i != end; i++) 
    {
      push_back(*i);
    }
    
    changeFile();
  }
  ~FileLinkedList() 
  {
    fclose(file);
  }
  //General Methods
    void push_back(const T &t)
    {
        insert(end(),t);
    }
    void pop_back()
    {
        erase(--end());
    }

    int size() const
    {
        return numElems;
    }
    void clear()
    {
        numElems = 0;
        free = -1; // Free is binary meaning if 0 then free space is at the end of the list if 1 then not at the end of the list
        changeFile();
        writeNext(0,0); // Setting up the sentinel and have it point at itself
        writePrev(0,0);
    }
    
    const_iterator insert(const_iterator position, const T &t)
    {
        int location = position.index; // where in list to go
        int index; // index in file
        if (free == -1) 
        {
           index = numElems+1;
        } 
        else 
        {
          index = free;
          free = getNext(free);
        }
        
        writeElems(index,t);
        writePrev(index, getPrev(location));
        writeNext(index, location);
        int locationPrev = getPrev(location);
        writePrev(location,index);
        writeNext(locationPrev,index);

        numElems++;
        changeFile();

        return const_iterator(location, file);
    };
    
    T operator[](int index) const 
    {
        const_iterator tmp{0, file};
        for (int i = 0; i <= index; i++) 
        {
            ++tmp;
        }
        return *tmp;
    }
    const_iterator erase(const_iterator position)
    {    
        int location = position.index; //where to erase
        int tmp = getNext(location);
        writeNext(getPrev(location), getNext(location));
        writePrev(getNext(location), getPrev(location));
        writeNext(location, free);
        
        free = location;
        --numElems;
        changeFile();
        return const_iterator(tmp, file);
    };
    
    void set(const T &value,int index)
    {
        int tmp = 0;
        for (int i = 0; i <= index; i++) 
        {
          tmp = getNext(tmp);
        }
        writeElems(tmp,value);
    }
    
    void set(const T &value,const_iterator position)
    {
        writeElems(position.index,value);
    };


    const_iterator begin()
    {
        return const_iterator(getNext(0),file);
    };
    const_iterator begin() const
    {
        return const_iterator(getNext(0),file);
    };
    const_iterator cbegin() const
    {
        return const_iterator(getNext(0),file);
    };
    const_iterator end()
    {
       return const_iterator(0,file); // Sentinel is at index 0
    };
    const_iterator end() const
    {
        return const_iterator(0,file); // Sentinel is at index 0
    };
    const_iterator cend() const
    {
        return const_iterator(0,file); // Sentinel is at index 0
    };
};
