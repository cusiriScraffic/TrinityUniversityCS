#ifndef Order_Stat
#define Order_Stat

#include <iostream>
#include <cstdlib>
#include <utility> 
#include <string>

using std::endl;
using std::pair;
using std::cout;
using std::string;

// An order statistics tree is simply a augmented tree which holds
// Additional information. Augmented red black tree with size which
// Is the size of the nodes within the subtree
template<typename T>
class OrderStat {
    struct Node 
    {
        T data;
        int size;
        bool color;
        Node* left;
        Node* right;
        Node* parent;
        Node(const T &d, int s, Node* l, Node* r, Node* p): data(d),size(s), left(l), right(r), parent(p){};
        Node(Node* l, Node* r, Node* p, bool c):left(l),right(r),parent(p),color(c){}
    };

    Node* Sentinel;
    Node* root;
    int numElems;

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
    y->size = x->size; // O(1) to update therefore insert is still log(n)
    x->size = x->left->size + x->right->size + 1;
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
    y->size = x->size; // O(1) to update therefore insert is still log(n)
    x->size = x->left->size + x->right->size + 1;
};

Node* osSelect(Node* x, int i)
{
    int rank = x->left->size + 1;
    // x->left.size is the number of numbers the come before x in inorder walk 
    if(i == rank)
    {
        return x;
    }
    else if(i<rank)
    {
        return osSelect(x->left,i);
    }
    else
    {
        return osSelect(x->right,i-rank);
    } 
};// Returns a pointer to the ith smallest key in the subtree at x
// Search is porportional to the height of the tree so worst time O(Log(n)
int osRank(Node* x)
{
    Node* y;
    int rank = x->left->size + 1;
    y = x;
    while(y != root)
    {
        if(y == y->parent->right)
        {
            rank = rank + y->parent->left->size + 1;
        }
        y = y->parent;
    } 
    return  rank;
};// O(log(n))
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
    typedef T value_type;

    class const_iterator;

    class iterator {
        bool atEnd;
        Node* iter;
        Node* Sentinel;
    public:
        friend class const_iterator;
        // TODO: constructors
        iterator(Node* n, Node* s, bool a):iter(n),atEnd(a),Sentinel(s){}
        iterator(const iterator &i):iter(i.iter),atEnd(i.atEnd),Sentinel(i.Sentinel){}

        bool operator==(const iterator &i) const 
        {
            return (iter == i.iter && atEnd == i.atEnd && Sentinel == i.Sentinel);
        }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        T &operator*() 
        { 
            return iter->data;
        }
        iterator &operator++() {
            // TODO
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
        iterator &operator--() {
            // TODO
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
        // TODO: iterator data
        bool atEnd;
        Node* Sentinel;
        Node* iter;
    public:
        friend class OrderStat<T>;
        // TODO: constructors
        const_iterator(Node* n, Node* s, bool a):iter(n),atEnd(a),Sentinel(s){}
        const_iterator(const iterator &i):iter(i.iter),atEnd(i.atEnd),Sentinel(i.Sentinel){}

        bool operator==(const const_iterator &i) const 
        {
            return (iter == i.iter && atEnd == i.atEnd && Sentinel == i.Sentinel);
        }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        
        const T &operator*() 
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

    OrderStat(): Sentinel(new Node(nullptr,nullptr,nullptr,false)),root(Sentinel){}
    OrderStat(const OrderStat<T> &that) 
    {
        numElems = 0;
        Sentinel = new Node(nullptr,nullptr,nullptr,false); // Sentinel doesnt exists yet
        root = Sentinel;
        insert(that.begin(),that.end());
    }//Create new object then copy
    ~OrderStat() 
    {
        clear();
        delete Sentinel;
    }

    OrderStat &operator=(const OrderStat<T> &that) 
    {
        clear();
        numElems = 0;
        root = Sentinel;
        insert(that.begin(),that.end());
        return *this;
    }// Object already exists, you just copy over

    bool empty() const 
    {
        return (numElems == 0);
    }

    unsigned size() const {return numElems;}

    value_type &front()
    {
        return *(begin());
    };
    const value_type &front() const
    {
        return *(cbegin());
    };
    value_type &back()
    {
        return *(--end());
    };
    const value_type &back() const
    {
        return *(--cend());
    };

    iterator insert(const_iterator position,const value_type& val)
    {
        Node* y = Sentinel;
        Node* x = root;
        Node* z = new Node(val,1, Sentinel, Sentinel,y,true); // Check this, could be incorrect
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
        insertFix(z);    // This restore the r-b properties
        return iterator(++position)
    }

    template <class InputIterator>
    void insert(const_iterator position,InputIterator first, InputIterator last)
    {
        for(auto iter = first; iter!=last; ++iter) 
        {
            insert(position,*iter);
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

    void clear()
    {
        destroyAll(root);
        numElems = 0;
        root = Sentinel;
    };

    value_type &operator[](int index)
    {
        return osSelect(root,index);   
    };

    void push_front(const value_type& val)
    {
        Node* prev = Sentinel;
        Node* tmp = root;
        while(tmp)
        {
            prev = tmp;
            tmp = tmp->left;
        }
        Node* n = new Node(Sentinel, Sentinel, prev,false);
        n->data = val;
        if (!tmp) tmp = n;
        if (prev) prev->left = n;
        insertFix(n);
    };
    void pop_front()
    {
        erase(begin());
    };
    void push_back(const value_type& val)
    {   
        // Go all the way right, add to right child resize
        Node* prev = Sentinel;
        Node* rover = root;
        while (rover){
          prev = rover;
          rover = rover->right;
        }
        Node* n = new Node(Sentinel, Sentinel, prev,false);
        n->data = val;
        if (!root) root = n;
        if (prev) prev->right = n;
        insertFix(n);
    };
    void pop_back()
    {
        erase(--end()); // This erases the furthest to the right
    };

    bool operator==(const OrderStat<T>& rhs) const
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

    bool operator!=(const OrderStat<T>& rhs) const
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