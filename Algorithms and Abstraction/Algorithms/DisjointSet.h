#ifndef Disjoint_Set
#define Disjoint_Set

template<typename T>
class DisjointSet 
{
    private: 
    	T data;
		DisjointSet* parent;
		int rank;

		DisjointSet* findSet()
		{
			if(parent != this) // If not at the root
			{
				parent = parent -> findSet();	
			}
			return parent;
		};
		void linkerFunction(DisjointSet* x, DisjointSet* y)
		{
			if(x->rank > y->rank)
			{
				y -> parent = x;
			}
			else
			{
				x -> parent = y;
				if(x->rank == y->rank)
				{
					y->rank = y->rank + 1;
				}
			} 
		};

    public:
        DisjointSet(const T &data)
        {
        	this -> data = data;
        	this -> parent = this; //This is the special name for pointer to itself
        	rank = 0;
        };// Constructor, each disjoint set is its own node. Creates a node that points to itself
        void unionSets(DisjointSet &ds)
        {			
        	linkerFunction(findSet(),ds.findSet());
        };// Combines two sets together
        const T &getMarker()
        {
        	return findSet() -> data ; // Getting data from the rep which we get from find set
        };// call find set and get data from result 
        // We compare if two things beling to the same set 
};

#endif