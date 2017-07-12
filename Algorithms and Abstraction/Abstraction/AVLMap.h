#ifndef AVL_Map
#define AVL_Map

#include <iostream>
#include <cstdlib>
#include <utility> 
#include <string>

using std::endl;
using std::pair;
using std::cout;
using std::string;


template<typename K,typename V>

class AVLMap {
    struct Node
    {
        pair<K,V> data;       
        Node* left;
        Node* right;
        Node* parent;
        bool color; //If red true, if false its black
        Node(const pair<K,V> &d, Node* l, Node* r, Node* p, bool c):data(d),left(l),right(r),parent(p),color(c){};
        Node(Node* l, Node* r, Node* p, bool c):left(l),right(r),parent(p),color(c){}
        // So whenever in insert should be red first then I check, in order to keep properties correct 
    };
//Change the pointer structure through rotation. Two type left rotation  Run in O(1)
// Left roatate assumes that x.right != nill meaning x has a right child
// Must also change the colors of the nodes inorder to ensure that they adhear to the properties of RB trees

    Node* Sentinel;
    Node* root;
    unsigned int numElems;

void leftRotate(Node* x)
{
//must have a right child
    if (!x) return;
    Node* y = x->right; // This sets Y as X's right child
    if(x==Sentinel || x->right == Sentinel) return;
    x->right = y->left; //turn y’s left subtree into X’s right subtree

    if(y->left != Sentinel)
    {
        y->left->parent = x;
    }
    y->parent = x->parent; // Links x's parent to y's parent
    if(x->parent == Sentinel)
    {
        root = y;
    }
    else if(x == x->parent->left )
    {
        x->parent->left = y;
    }
    else 
    {
        x->parent->right = y;
    }
        y->left = x;
        x->parent = y;
};

void rightRotate(Node* x)
{
    if (!x) return;
    Node* y = x->left; // This sets Y as X's right child
    if(x==Sentinel || x->left == Sentinel) return;
    x->left = y->right; //turn y’s left subtree into X’s right subtree
    if(y->right != Sentinel)
    {
        y->right->parent = x;
    }
    y->parent = x->parent; // Links x's parent to y's parent
    if(x->parent == Sentinel)
    {
        root = y;
    }
    else if(x == x->parent->right )
    {
        x->parent->right = y;
    }
    else 
    {
        x->parent->left = y;
    }
        y->right = x;
        x->parent = y;
};
void destroyAll(Node* n)
{
    if(n==Sentinel) return ;
    if(n != Sentinel)
    {
        destroyAll(n->left);
        destroyAll(n->right);
    }
    delete n;
    
};
void insertFix(Node* z)
{
    Node* y; // Tmp variable
    while(z->parent->color == true) // While z's parent's color is == red, if z's parent is root then z's parent must be black, either violates property 2 (z->parent is root and red) or 4 two reds
    {
        if(z->parent == z->parent->parent->left)
        {
             y = z->parent->parent->right; // This z's nucle, which is z's parents sibling
            if(y->color == true)   // CASE 1 , if z's uncle is red
            {
                z->parent->color = false; // recolors
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent; // Moves z's pointer up the tree to z's grandfather
            }
            else 
            {
                if(z == z->parent->right) //CASE 2, new z is the right child of z's parent
                {
                    z = z->parent; // moves the pointer to z's parent
                    leftRotate(z);  // left rotate in z's parent which is now z
                }
                else
                {
                    z->parent->color = false;        //CASE 3 z is the left child of its parent
                    z->parent->parent->color = true;
                    rightRotate(z->parent->parent);
                }
            }
        }
        else 
        if(z->parent == z->parent->parent->right)
        {
             y = z->parent->parent->left; // This z's nucle, which is z's parents sibling
            if(y->color == true)   // CASE 4 , if z's uncle is red
            {
                z->parent->color = false; // recolors
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent; // Moves z's pointer up the tree to z's grandfather
            }
            else 
            {
                if(z == z->parent->left) //CASE 5, new z is the right child of z's parent
                {
                    z = z->parent; // moves the pointer to z's parent
                    rightRotate(z);  // left rotate in z's parent which is now z
                }
                z->parent->color = false;        //CASE 6 z is the left child of its parent
                z->parent->parent->color = true;
                leftRotate(z->parent->parent);
            }
        } // Tree terminates because z's parent is black
    }
    root->color = false; // This ensures that property 2 holds at termination
}
Node* treeMinimum(Node* x) const
{
     while(x->left != Sentinel)
        {
            x = x->left;
        }
        return x;
};// As long as there is a left, node to left branch take the left and go as far down as possible
void transplant(Node* u, Node* v) 
{
    if(u->parent == Sentinel)
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
    v->parent = u->parent;
};// Seems like transplant is the same in BST as it is with Red-Black trees
void deleteFix(Node* x) // This restores properties 1,2,4
{
   Node* w;
   while(x->parent && x != root && x->color == false) //This is meant to move the extra black up the tree until 1) x points to a node that we color is black  at the end 2) x points to root therefore just remove the extra black 
    // Node 3) Having performed suitable rotations and recoloring, we exit the loop
   {
        if(x->parent && x == x->parent->left)
        {
            w = x->parent->right;
            if(w == Sentinel) break; //break meaning break the while loop
            if(w->color == true)
            {
                w->color = false;// CASE 1 If X's sibling W is red, (They must be black), w and x.p swap colors and left rotation on x.p
                x->parent->color = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left && w->right && w->left->color == false && w->right->color == false)
            {
                w->color = true;//CASE 2 X's siblings w is black and both of W's children are black
                x = x->parent;
            }
            else 
            {
                if(w->right && w->right->color == false)
                {
                    w->left->color = false;//CASE 3 x’s sibling w is black, w’s left child is red, and w’s right child is black
                    w->color = true;
                    rightRotate(w);
                    w = x->parent->right;
                }              
                w->color = x->parent->color; // CASE 4 x’s sibling w is black, and w’s right child is red
                x->parent->color = false;
                leftRotate(x->parent);
                x = root;    
        
            }
        }
        else if(x->parent && x == x->parent->right)
        {
            w = x->parent->left;
            if(w == Sentinel) break; //break meaning break the while loop
            if(w->color == true)
            {
                w->color = false;// CASE 5
                x->parent->color = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->left && w->right && w->right->color == false && w->left->color == false)
            {
                w->color = true;//CASE 6
                x = x->parent;
            }
            else
            { 
                if(w->left && w->left->color == false)
                {
                    w->right->color = false;//CASE 7
                    w->color = true;
                    leftRotate(w);
                    w = x->parent->left;
                }
                    w->color = x->parent->color; // CASE 8
                    x->parent->color = false;
                    rightRotate(x->parent);
                    x = root;    
            }
        }   
   }
   x->color = false; 
};
void myInsert(Node* n) 
    
{
        if (n!=Sentinel) 
        {
          insert(n->data);
          insert(n->left);
          myInsert(n->right);
        }
}

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    void printRec(Node* n, string s)
    {
        if(n != Sentinel)
        {
        cout<<s<<n->data.first<<endl;
        cout<<s<<n->data.second<<endl;
        if(n->left != Sentinel && n->left->parent != n)
        {
            return;
        }
        else if(n->right != Sentinel && n->right->parent != n)
        {
            return;
        }
        printRec(n->left,s+ " ");
        printRec(n->right,s+" ");
        }
    }
    void printRecRoot()
    {
        printRec(root, " ");
    }

    class const_iterator;

    class iterator {
        Node* iter;
        bool atEnd;
        Node* Sentinel; 

    public:
        friend class const_iterator;
        iterator(const const_iterator &i):iter(i.iter),atEnd(i.atEnd),Sentinel(i.Sentinel){}
        iterator(Node* n, Node* s, bool a):iter(n),atEnd(a), Sentinel(s){}
        

        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const 
        {
            return (iter == i.iter && atEnd == i.atEnd && Sentinel == i.Sentinel);
        }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() 
        {
            return iter->data;
        }
        iterator &operator++() {
            if (iter->right!=Sentinel) 
            {
                iter = iter->right;
                while (iter->left!=Sentinel) 
                {
                    iter=iter->left;
                }
                return *this;
            }
            // If it does have a right child. Non of these have right children
            Node* tmp(iter->parent);
            while (tmp!=Sentinel && iter==tmp->right) 
            {
                iter = tmp;
                tmp = tmp->parent;
            }
            if (tmp==Sentinel) // if there is no parent then it must be the root
            {
                while (iter->right!=Sentinel) 
                {    
                    iter = iter->right;
                }   

                atEnd=true;
            } 
            else 
            {
                iter = tmp;
            }
            return *this;
        }
        iterator &operator--() {
            if (atEnd) 
            {
                atEnd = false;
                return *this;
            }
            if (iter->left!=Sentinel) 
            {
                iter = iter->left;
                while (iter->right!=Sentinel) 
                {
                  iter=iter->right;
                }
            return *this;
          }
          Node* tmp(iter->parent);
          while (tmp!=Sentinel && iter==tmp->left) 
          {
            iter = tmp;
            tmp = tmp->parent;
          }
          if (tmp==Sentinel) 
          {
            while (iter->left!=Sentinel) 
                {
                    iter = iter->left;
                }
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
        Node* Sentinel; 
    public:
        friend class AVLMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node* n, Node* s, bool a):iter(n),atEnd(a),Sentinel(s){}
        const_iterator(const iterator &i):iter(i.iter),atEnd(i.atEnd),Sentinel(i.Sentinel){}

        bool operator==(const const_iterator &i) const 
        {
            return (iter == i.iter && atEnd == i.atEnd && Sentinel == i.Sentinel);
        }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        
        const std::pair<K,V> &operator*() 
        { 
            return iter->data;
        }
        const_iterator &operator++() 
        {
            if (iter->right!=Sentinel) 
            {
                iter = iter->right;
                while (iter && iter->left != Sentinel) 
                {
                      iter=iter->left;
                }
                return *this;
            }
            // If it does have a right child. Non of these have right children
            Node* tmp(iter->parent);
            while (tmp!=Sentinel && iter==tmp->right) 
            {
                iter = tmp;
                tmp = tmp->parent;
            }
            if (tmp==Sentinel) // if there is no parent then it must be the root
            {
                while (iter->right!=Sentinel) 
                    {
                        iter = iter->right;
                    }
                atEnd=true;
            } 
            else 
            {
                iter = tmp;
            }
            return *this;
        }
        const_iterator &operator--()
        {
            if (atEnd) 
            {
                atEnd = false;
                return *this;
            }
            if (iter->left!=Sentinel) 
            {
                iter = iter->left;
                while (iter->right!=Sentinel) 
                {
                  iter=iter->right;
                }
            return *this;
          }
          Node* tmp(iter->parent);
          while (tmp!=Sentinel && iter==tmp->left) 
          {
            iter = tmp;
            tmp = tmp->parent;
          }
          if (tmp==Sentinel) 
          {
            while (iter->left!=Sentinel) 
                {
                    iter = iter->left;
                }
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



    AVLMap():numElems(0),Sentinel(new Node(nullptr,nullptr,nullptr,false)),root(Sentinel){};
    ~AVLMap() 
    {
        clear();
        delete Sentinel;
    };
    AVLMap(const AVLMap<K,V> &that) 
    {
        numElems = 0;
        Sentinel = new Node(nullptr,nullptr,nullptr,false); // Sentinel doesnt exists yet
        root = Sentinel;
        insert(that.begin(),that.end());
    }// When you are creating a new object then COPY

    AVLMap &operator=(const AVLMap<K,V> &that) 
    {
        clear();
        numElems = 0;
        root = Sentinel;
        insert(that.begin(),that.end());
        return *this;
    }// Object already exists and COPYING Objects

    bool empty() const { return (numElems == 0); }

    unsigned size() const { return numElems; }

    iterator find(const key_type& k)
    {
         Node* x = root;
        if(x == Sentinel)
            {
                return end();
            }// Tree is empty  
         while(x != Sentinel && k != x->data.first)
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
         if(x==Sentinel)
         {
            return end(); // not found
         }
         else
         {
    
            return iterator(x,Sentinel,false);   
         }
    };

    const_iterator find(const key_type& k) const
    {
         Node* x = root;
        if(x == Sentinel)
            {
                return end();
            }// Tree is empty  
         while(x != Sentinel && k != x->data.first)
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
         if(x == Sentinel)
         {
            return end(); // not found
         }
         else
         {
            return const_iterator(x,Sentinel,false);   
         }
    };

    unsigned int count(const key_type& k) const
    {
        if(find(k)==end())
        {
            return 0;
        }
        return 1;
    };

    std::pair<iterator,bool> insert(const value_type& val) // O(log(n)) and since it moves two level sup it never performs more that 2 rotations(case 2 or 3)
    {
        Node* y = Sentinel;
        Node* x = root;
        Node* z = new Node(val, Sentinel, Sentinel,y,true); // Check this, could be incorrect
        while(x != Sentinel)
        {
            y = x;
            if (z->data.first == x->data.first) 
            {
                    return std::make_pair(find(val.first),false);
            }
            if(z->data.first < x->data.first)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        z->parent = y;
        if(y == Sentinel)
        {
            root = z;
        }
        else if(z->data.first < y->data.first)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        z->left = Sentinel; // left and right set to nill in order to maintaint the properties of the tree
        z->right = Sentinel;
        z->color = true; // True meaning its red
        numElems++;
        // cout<<"Z's data-> first  " <<z->data.first<<endl;
        insertFix(z);    // This restore the r-b properties
        return std::make_pair(find(val.first),true);
        
    };

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) 
    {
        for(auto iter = first; iter!=last; ++iter) 
        {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position)
    {
        Node* z = position.iter;
        Node* y = z; // To keep track of z if deleted.
        Node* x; // Tmp variables 
        bool yColor = y->color; // This is a tmp vairbale that I am using towards my fuction       
        //instead of ++ position then having posTmp = psoition.iter
        Node* posTmp = (++position).iter; // now position points to the next iter
        
        if(root == Sentinel)
        {
            return end(); // Empty tree
        }
        if(z->left == Sentinel)
        {
            x = z->right;
            transplant(z,z->right);
        }// if z's left is does not exists, go z's right
        else if(z->right == Sentinel)
        {
            x = z->left;
            transplant(z,z->left);
        }// if z's right does not exists, go z's left
        else 
        {
            y = treeMinimum(z->right);
            yColor = y->color; // This is a tmp vairbale that I am using towards my fuction
            x = y->right;
            if(y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transplant(y,y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z,y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if(yColor == false)// If black then call the delete fix
        {
            deleteFix(x);
        }
        delete z;    
        numElems--;
        if(position == end())
        {
            return end();
        }
        else
        {
            return iterator(posTmp,Sentinel,false);  // This is supposed to return the value after the erase, therefore the ++ is needed
        }
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
        root = Sentinel;
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

    bool operator==(const AVLMap<K,V>& rhs) const
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

    bool operator!=(const AVLMap<K,V>& rhs) const
    {
        return !(operator==(rhs));
    };

    iterator begin() 
    { 
        Node* tmp = root;
        if(tmp!= Sentinel)
        {
            while(tmp->left != Sentinel)
            {
                tmp = tmp->left;
            }
        }
        if (numElems==0) return iterator(tmp,Sentinel,true);
        return iterator(tmp,Sentinel,false);
    }

    const_iterator begin() const 
    {
        Node* tmp = root;
        if(tmp!= Sentinel)
        {
            while(tmp->left != Sentinel)
            {
                tmp = tmp->left;
            }
        }
        if (numElems==0) return const_iterator(tmp,Sentinel,true);
        return const_iterator(tmp,Sentinel,false);
    }

    iterator end() 
    {
        Node* tmp = root; 
        if(numElems==0) return iterator(tmp,Sentinel,true);
            while(tmp->right!=Sentinel) // I do not want to go one past the end. 
            {
                tmp = tmp->right;
            }  
        return iterator(tmp,Sentinel, true);
    }

    const_iterator end() const 
    { 
     Node* tmp = root; 
        if(numElems==0) return const_iterator(tmp,Sentinel,true);
            while(tmp->right!=Sentinel) // I do not want to go one past the end. 
            {
                tmp = tmp->right;
            }  
        return const_iterator(tmp,Sentinel,true);
    }

    const_iterator cbegin() const 
    {
         Node* tmp = root;
        if(tmp!= Sentinel)
        {
          while(tmp->left != Sentinel)
            {
                tmp = tmp->left;
            }
        }
        if (numElems==0) return const_iterator(tmp,Sentinel,true);
        return const_iterator(tmp,Sentinel,false);
    }

    const_iterator cend() const 
    { 
         Node* tmp = root; 
        if(numElems==0) return const_iterator(tmp,Sentinel,true);
            while(tmp->right!=Sentinel) // I do not want to go one past the end. 
            {
                tmp = tmp->right;
            }  
        return const_iterator(tmp,Sentinel,true);
    }
};

#endif