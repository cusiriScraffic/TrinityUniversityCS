#include <list>
#include <vector>

template<typename T,typename K>
void bucketSort(T begin,T end,K keyFunc)
{
	 vector<list<typename T::value_type>> buckets(end-begin);
    for(T i = begin; i != end; i++)
    {
        int index = (int)(keyFunc(*i));
        buckets[index].push_back(*i);
    }
    for(unsigned int j = 0; j < buckets.size(); j++)
    {
        buckets[j].sort(
 	[&keyFunc](typename T::value_type t1, typename T::value_type t2){return keyFunc(t1) < keyFunc(t2);});
    }
    for(unsigned int k = 1; k < buckets.size(); k++)
    {
        buckets[0].splice(buckets[0].end(),buckets[k]);
    }
    for(T i = end-1; i != begin-1; i--)
    {
        *i = buckets[0].back();
        buckets[0].pop_back();
    }
};