#ifndef BST_MAP
#define BST_MAP

#include <iostream>
#include <cstdlib>
#include <utility> 
#include <string>

using std::pair;
using std::cout;
using std::string;
using std::endl;

template<typename K,typename V>
class BSTMap {
    struct Node 
    {
        pair<K,V> data;// Which stores a key value pair
        Node* left; // Point to left node
        Node* right;// Point to right node
        Node* parent;// Point to parent node
        Node(const pair<K,V> &d, Node* l, Node* r, Node* p): data(d), left(l), right(r), parent(p){}
        Node(const pair<K,V> &d):data(d),left(nullptr),right(nullptr),parent(nullptr){};
    };
    //Helper Function
    void destroyAll(Node* n)
    {
        if(n == nullptr) return;
        if (numElems != 0)
        {
            destroyAll(n->left);
            destroyAll(n->right);
        }
        delete n;
    } 
    void transplant(Node* u, Node* v)
    {
        if(u->parent == nullptr)
        {
            root = v;
        }
        else if(u == u->parent->left )
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        if(v!= nullptr)
        {
            v->parent = u->parent;
        }
    }
    Node* treeMinimum(Node* x) const
    {
        while(x->left != nullptr)
        {
            x = x->left;
        }
        return x;
    }
    void myInsert(Node* n) 
    {
    if (n!=nullptr) {
      insert(n->data);
      myInsert(n->left);
      myInsert(n->right);
    }
  }
    Node* root; // can be set to nullptr which makes it the default value of the tree
    unsigned int numElems;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        Node* iter;
        bool atEnd;
        //Need to be able to go back from end, i.e. --end() should 
        //give last element.
        //One approach is to keep a Node* and a bool that tells me if 
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the 
        //maximum element. But to get the maximum element, we need to 
        //store information about the tree, e.g. the root pointer, as member.
    public:
        friend class const_iterator;
        iterator(Node* n, bool a)  : iter(n), atEnd(a) {}
        iterator(const const_iterator& i) : iter(i.iter), atEnd(i.atEnd) {}
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const 
        {
            return iter == i.iter && atEnd == i.atEnd;
        }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() 
        {
            return iter-> data;
        }
        iterator &operator++() 
        {
            if (iter->right!=nullptr) 
            {
            iter = iter->right;
            while (iter->left!=nullptr) 
            {
              iter=iter->left;
            }
            return *this;
            }
            // If it does have a right child. Non of these have right children
            Node* tmp(iter->parent);
            while (tmp!=nullptr && iter==tmp->right) 
            {
                iter = tmp;
                tmp = tmp->parent;
            }
            if (tmp==nullptr) // if there is no parent then it must be the root
            {
                while (iter->right!=nullptr) iter = iter->right;
                atEnd=true;
            } 
            else 
            {
                iter = tmp;
            }
            return *this;
        }
        iterator &operator--() 
        {
            if (atEnd) 
            {
                atEnd = false;
                return *this;
            }
            if (iter->left!=nullptr) 
            {
                iter = iter->left;
                while (iter->right!=nullptr) 
                {
                  iter=iter->right;
                }
            return *this;
          }
          Node* tmp(iter->parent);
          while (tmp!=nullptr && iter==tmp->left) 
          {
            iter = tmp;
            tmp = tmp->parent;
          }
          if (tmp==nullptr) 
          {
            while (iter->left!=nullptr) iter = iter->left;
            atEnd=true;
          } else 
          {
            iter = tmp;
          }
          return *this;
            
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
        Node* iter;
        bool atEnd;
        // TODO: iterator data
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node* i, bool a): iter(i), atEnd(a) {};
        // TODO: Other constructors as needed.
        const_iterator(const iterator &i):iter(i.iter),atEnd(i.atEnd){};

        bool operator==(const const_iterator &i) const 
        {
            return iter == i.iter && atEnd == i.atEnd;
        }
        bool operator!=(const const_iterator &i) const 
        {
            return !(*this==i);
        }
        const std::pair<K,V> &operator*() 
        {
            return iter -> data;
        }
        const_iterator &operator++() 
        {
            if (iter->right!=nullptr) 
            {
            iter = iter->right;
            while (iter->left!=nullptr) 
            {
              iter=iter->left;
            }
            return *this;
            }
            // If it does have a right child. Non of these have right children
            Node* tmp(iter->parent);
            while (tmp!=nullptr && iter==tmp->right) 
            {
                iter = tmp;
                tmp = tmp->parent;
            }
            if (tmp==nullptr) // if there is no parent then it must be the root
            {
                while (iter->right!=nullptr) iter = iter->right;
                atEnd=true;
            } 
            else 
            {
                iter = tmp;
            }
            return *this;
        }
        const_iterator &operator--() { 
            if (atEnd) 
            {
                atEnd = false;
                return *this;
            }
            if (iter->left!=nullptr) 
            {
                iter = iter->left;
                while (iter->right!=nullptr) 
                {
                  iter=iter->right;
                }
            return *this;
          }
          Node* tmp(iter->parent);
          while (tmp!=nullptr && iter==tmp->left) 
          {
            iter = tmp;
            tmp = tmp->parent;
          }
          if (tmp==nullptr) 
          {
            while (iter->left!=nullptr) iter = iter->left;
            atEnd=true;
          } else 
          {
            iter = tmp;
          }
          return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

     BSTMap(): numElems(0), root(nullptr) {};
    ~BSTMap() 
    {
        clear();
    };
    BSTMap(const BSTMap<K,V> &that) 
    {
        root = nullptr;
        numElems = 0;
        myInsert(that.root);
    } // When you are creating a new object then COPY

    BSTMap &operator=(const BSTMap<K,V> &that) 
    {
        clear();
        myInsert(that.root);
        return *this;
    }// Object already exists and COPYING Objects

    bool empty() const { return(numElems == 0);}

    unsigned size() const { return numElems; }

    iterator find(const key_type& k)
    {
        Node* x = root;
        if(x == nullptr)
            {
                return end();
            }// Tree is empty  
         while(x != nullptr && k != x->data.first)
         {
            if(k < x->data.first) 
            {
                x = x-> left;
            }// Cause you only want it to happen once   
            else if (k > x->data.first) 
            {
                x = x-> right;
            } 
         } 
         if(x==nullptr)
         {
            return end(); // not found
         }
         else
         {
    
            return iterator(x,false);   
         }
         
         
    };

    const_iterator find(const key_type& k) const
    {
        Node* x = root;
        if(x == nullptr)
            {
                return end();
            }// Tree is empty  
         while(x != nullptr && k != x->data.first)
         {
            if(k < x->data.first) 
            {
                x = x-> left;
            }// Cause you only want it to happen once   
            else if (k > x->data.first) 
            {
                x = x-> right;
            } 
         } 
         if(x== nullptr)
         {
            return end(); // not found
         }
         else
         {
            return const_iterator(x,false);   
         }
    };

    unsigned int count(const key_type& k) const
    {
        if(find(k)== end()){return 0;}
        return 1;
    };

    std::pair<iterator,bool> insert(const value_type& val)
    {
        Node* y = nullptr; // This keeps reference to the parent of the nodes
        Node* x = root; // Insert always starts from root node
        while(x != nullptr)
        {
            y = x; //Destination - Source
            if (val.first == x->data.first) 
            {
                    return std::make_pair(find(val.first),false);
            }
            if(val.first < x->data.first)
            {
                x = x->left;
            }
            else 
            {
                x = x->right;
            }
        }
        Node* z = new Node(val, nullptr, nullptr,y); 
        if(y == nullptr)
        {
            root = z;
        }
        else if (z->data.first < y->data.first )
        {
            y->left = z;
        }
        else 
        {
            y->right = z;
        }
        numElems++;
        return std::make_pair(find(val.first),true);
    };

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position)
    {
        Node* z = position.iter;
        iterator iter = find(z->data.first);
        ++iter;
        if(z->left == nullptr)
        {
            transplant(z,z->right);
        }
        else if(z->right==nullptr)
        {
            transplant(z,z->left);
        }
        else
        {
            Node* y = treeMinimum(z->right);
            if (y->parent != z)
            {
                transplant(y, y->right);
                y->right= z->right;
                y->right->parent = y;
            }
            transplant(z,y);
            y->left = z->left;
            y->left->parent = y;
        }
        numElems--;
        delete z;
        return iter;
    };

    unsigned int erase(const key_type& k)
    {
        auto iter = find(k);
        if (iter==end())return 0;
        erase(iter);
        return 1;
    };

    void clear()
    {
        destroyAll(root);
        numElems = 0;
        root = nullptr;
    };

    mapped_type &operator[](const K &key)
    {
     // Gets the first element of the pair which is the key  
          if (find(key) != end()) // Check to see if this is in a collection
          {
            return (*find(key)).second;
          }
          else 
        {
            pair<K,V> p;
            p.first = key;
            auto inpair = insert(p);
            return (*(inpair.first)).second;
        } 
     //  Gets the first element of the pair which is the key
    };

    bool operator==(const BSTMap<K,V>& rhs) const
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

    bool operator!=(const BSTMap<K,V>& rhs) const
    {
        return !(operator==(rhs));
    };

    iterator begin() 
    { 
        //Smallest Element, Therefore inorder traversal
        Node* tmp = root;
        if (numElems==0) return iterator(tmp,true);
        if(tmp!= nullptr)
        {
           while(tmp->left != nullptr)
            {
                tmp = tmp->left;
            }
        }
        return iterator(tmp,false);
    }

    const_iterator begin() const 
    {
         Node* tmp = root;
        if(tmp!= nullptr)
        {
            while(tmp->left != nullptr)
            {
                tmp = tmp->left;
            }
        }
        if (numElems==0) return const_iterator(tmp,true);
        return const_iterator(tmp,false);
    }
    const_iterator cbegin() const 
    { 
         Node* tmp = root;
        if(tmp!= nullptr)
        {
          while(tmp->left != nullptr)
            {
                tmp = tmp->left;
            }
        }
        if (numElems==0) return const_iterator(tmp,true);
        return const_iterator(tmp,false);
    }
    // One past the End
    iterator end() 
    { 
        Node* tmp = root; 
        if(numElems==0) return iterator(tmp,true);
            while(tmp->right!=nullptr) // I do not want to go one past the end. 
            {
                tmp = tmp->right;
            }  
        return iterator(tmp,true); 
    }

    const_iterator end() const 
    { 
        Node* tmp = root; 
        if(numElems==0) return iterator(tmp,true);
            while(tmp->right!=nullptr) // I do not want to go one past the end. 
            {
                tmp = tmp->right;
            }  
        return const_iterator(tmp,true); 
    }

    const_iterator cend() const 
    { 
        Node* tmp = root; 
        if(numElems==0) return iterator(tmp,true);
            while(tmp->right!=nullptr) // I do not want to go one past the end. 
            {
                tmp = tmp->right;
            }  
        return const_iterator(tmp,true); 
    }
};

#endif