#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

#include "craigOrderStat.h"

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::cout;
using std::rand;

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);
	// Make ints
	vector<int> nums1(1000000);
	for(auto iter=nums1.begin(); iter!=nums1.end(); ++iter) *iter = rand();
	// Make strings
	vector<string> strings1(100000);
	for(auto iter=strings1.begin(); iter!=strings1.end(); ++iter) {
		for(int i=0; i<6; ++i) *iter += (char)('a'+rand()%26);
	}
	vector<int> indices;
	for(int i=0; i<100; i++) indices.push_back(rand()%nums1.size());
	vector<int> resultNumRand;
	vector<int> resultNumLinear;
	vector<string> resultStringRand;
	vector<string> resultStringLinear;

	cout << "Start timing" << endl;
	double start = clock();
	for(int i:indices) {
		vector<int> nums2{nums1};
		resultNumRand.push_back(*randomOrderStat(nums2.begin(),nums2.end(),[] (const int i1,const int i2) { return i1>i2; },i));
		resultNumLinear.push_back(*linearOrderStat(nums2.begin(),nums2.end(),[] (const int i1,const int i2) { return i1<i2; },i));
		if(i<strings1.size()) {
			vector<string> strings2{strings1};
			resultStringRand.push_back(*randomOrderStat(strings2.begin(),strings2.end(),[] (const string &i1,const string &i2) { return i1>i2; },i));
			resultStringLinear.push_back(*linearOrderStat(strings2.begin(),strings2.end(),[] (const string &i1,const string &i2) { return i1<i2; },i));
		}
	}
	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	// check
	cout << "Check correctness." << endl;
	std::sort(nums1.begin(),nums1.end(),[] (int i1,int i2) { return i1>i2; });
	std::sort(strings1.begin(),strings1.end(),[] (const string &s1,const string &s2) { return s1>s2; });
	for(vector<int>::size_type i=0,j=0; i<indices.size(); ++i) {
		if(resultNumRand[i]!=nums1[indices[i]]) {
			cout << "Wrong index for ints, reverse order, " << i << endl;
			cout << "Expected " << nums1[indices[i]] << " at index " << indices[i] << " got " << resultNumRand[i] << endl;
			return 2;
		}
		if(indices[i]<strings1.size()) {
			if(resultStringRand[j]!=strings1[indices[i]]) {
				cout << "Wrong index for strings, reverse order, " << i << endl;
				cout << "Expected " << strings1[indices[i]] << " at index " << indices[i] << " got " << resultStringRand[i] << endl;
				return 2;
			}
			++j;
		}
	}
	std::sort(nums1.begin(),nums1.end(),[] (int i1,int i2) { return i1<i2; });
	std::sort(strings1.begin(),strings1.end(),[] (const string &s1,const string &s2) { return s1<s2; });
	for(vector<int>::size_type i=0,j=0; i<indices.size(); ++i) {
		if(resultNumLinear[i]!=nums1[indices[i]]) {
			cout << "Wrong index for ints, normal order, " << i << endl;
			cout << "Expected " << nums1[indices[i]] << " at index " << indices[i] << " got " << resultNumLinear[i] << endl;
			return 2;
		}
		if(indices[i]<strings1.size()) {
			if(resultStringLinear[j]!=strings1[indices[i]]) {
				cout << "Wrong index for strings, normal order, " << i << endl;
			cout << "Expected " << strings1[indices[i]] << " at index " << indices[i] << " got " << resultStringLinear[i] << endl;
				return 2;
			}
			++j;
		}
	}
	return 0;
}
