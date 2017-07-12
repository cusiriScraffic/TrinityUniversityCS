#include<fstream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<utility>
#include<set>

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::rand;
using std::cout;
using std::pair;
using std::set;

vector<set<int> > drivingLegal(const vector<vector<int> > &roadTo);
vector<set<int> > myDrivingLegal(const vector<vector<int> > &roadTo);

int system(const char *args) {
	cout << "Dont use system.\n";
}

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);

	vector<vector<int> > roads1 = {{1},{2,4,5},{3,6},{2,7},
									{0,5},{6},{5,7},{7}};
	vector<set<int> > comps = drivingLegal(roads1);
	sort(comps.begin(),comps.end(),[] (const set<int> s1,const set<int> s2)
		{ return *s1.begin()<*s2.begin(); });
	vector<set<int> > ans1 = {{0,1,4},{2,3},{5,6},{7}};
	if(comps!=ans1) {
		cout << "Failed book example." << endl;
		return -1;
	}
	vector<vector<int> > roads2 = {{1},{2},{3},{0,5},
									{5,1,2,6,7},{6},{7},{5}};
	vector<set<int> > comps2 = drivingLegal(roads2);
	sort(comps2.begin(),comps2.end(),[] (const set<int> s1,const set<int> s2)
		{ return *s1.begin()<*s2.begin(); });
	vector<set<int> > ans2 = {{0,1,2,3},{4},{5,6,7}};
	if(comps2!=ans2) {
		cout << "Failed small 2." << endl;
		return -1;
	}
	cout << "Small tests passed" << endl;
	vector<vector<int> > bigRoads1(150000);
	int tot = 0;
	for(unsigned int i=0; i<bigRoads1.size() && tot<1000000000; ++i) {
		unsigned int start = rand()%1000;
		while(start<bigRoads1.size() && tot<1000000000) {
			if(start!=i) bigRoads1[i].push_back(start/100*100+i%100);
			++tot;
			start += rand()%1000+100;
		}
	}
	cout << tot << " roads." << endl;
	tot = 0;
	vector<vector<int> > bigRoads2(1000000);
	for(unsigned int i=0; i<bigRoads2.size() && tot<1000000000; ++i) {
		unsigned int s = i/100*100;
		for(unsigned int j=s; j<s+100; ++j) {
			if(j!=i) bigRoads2[i].push_back(j);
			++tot;
		}
	}
	cout << tot << " roads." << endl;
	tot = 0;
	vector<vector<int> > bigRoads3(10000);
	for(unsigned int i=0; i<bigRoads3.size() && tot<1000000000; ++i) {
		unsigned int start = rand()%10;
		while(start<bigRoads3.size() && tot<1000000000) {
			if(start!=i) bigRoads3[i].push_back(start);
			++tot;
			start += rand()%10+1;
		}
	}
	cout << tot << " roads." << endl;

	// Do Timing
	cout << "Start timing tests." << endl;
	double start = clock();

	cout << "big1" << endl;
	vector<set<int> > yourAnswer1 = drivingLegal(bigRoads1);
	cout << "big2" << endl;
	vector<set<int> > yourAnswer2 = drivingLegal(bigRoads2);
	cout << "big3" << endl;
	vector<set<int> > yourAnswer3 = drivingLegal(bigRoads3);

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	// check
	vector<set<int> > myAnswer1 = myDrivingLegal(bigRoads1);
	sort(yourAnswer1.begin(),yourAnswer1.end(),[] (const set<int> s1,const set<int> s2) { return *s1.begin()<*s2.begin(); });
	sort(myAnswer1.begin(),myAnswer1.end(),[] (const set<int> s1,const set<int> s2) { return *s1.begin()<*s2.begin(); });
	if(yourAnswer1!=myAnswer1) {
		cout << "Incorrect answer for big 1." << endl;
		return -1;
	}
	cout << "Passed big 1." << endl;
	vector<set<int> > myAnswer2 = myDrivingLegal(bigRoads2);
	sort(yourAnswer2.begin(),yourAnswer2.end(),[] (const set<int> s1,const set<int> s2) { return *s1.begin()<*s2.begin(); });
	sort(myAnswer2.begin(),myAnswer2.end(),[] (const set<int> s1,const set<int> s2) { return *s1.begin()<*s2.begin(); });
	if(yourAnswer2!=myAnswer2) {
		cout << "Incorrect answer for big 2." << endl;
		return -1;
	}
	cout << "Passed big 2." << endl;
	vector<set<int> > myAnswer3 = myDrivingLegal(bigRoads3);
	sort(yourAnswer3.begin(),yourAnswer3.end(),[] (const set<int> s1,const set<int> s2) { return *s1.begin()<*s2.begin(); });
	sort(myAnswer3.begin(),myAnswer3.end(),[] (const set<int> s1,const set<int> s2) { return *s1.begin()<*s2.begin(); });
	if(yourAnswer3!=myAnswer3) {
		cout << "Incorrect answer for big 3." << endl;
		return -1;
	}
	cout << "Passed big 3." << endl;

	return 0;
}