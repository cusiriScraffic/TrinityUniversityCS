#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <tuple>

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::rand;
using std::cout;
using std::pair;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::sort;

tuple<double,vector<tuple<int,int> > > sidewalkPlan(const vector<tuple<double, double> > &buildingLocations);
tuple<double,vector<tuple<int,int> > > sidewalkPlan1(const vector<tuple<double, double> > &buildingLocations);
tuple<double,vector<tuple<int,int> > > sidewalkPlan2(const vector<tuple<double, double> > &buildingLocations);

int system(const char *args) {
    cout << "Dont use system.\n";
}

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);

	vector<tuple<double,double> > locs1 = {make_tuple(0,0),make_tuple(1,0),make_tuple(-1,0),make_tuple(0,2),make_tuple(0,-2)};
	auto ans1 = sidewalkPlan(locs1);
	sort(get<1>(ans1).begin(),get<1>(ans1).end(),[] (const tuple<int,int> &e1,const tuple<int,int> &e2) { return get<0>(e1) < get<0>(e2) || (get<0>(e1)==get<0>(e2) && get<1>(e1)<get<1>(e2)); });
	vector<tuple<int,int> > correct1 = {make_tuple(0,1),make_tuple(0,2),make_tuple(0,3),make_tuple(0,4)};
	if(abs(get<0>(ans1)-6.0)>1e-8 || get<1>(ans1)!=correct1) {
		cout << "Failed test 1" << endl;
		return -1;
	}
	vector<tuple<double,double> > locs2 = {make_tuple(0,0),make_tuple(1,0),make_tuple(-1,0),make_tuple(0,2),make_tuple(0,-2),make_tuple(0.5,2),make_tuple(3,0),make_tuple(3,1)};
	auto ans2 = sidewalkPlan(locs2);
	sort(get<1>(ans2).begin(),get<1>(ans2).end(),[] (const tuple<int,int> &e1,const tuple<int,int> &e2) { return get<0>(e1) < get<0>(e2) || (get<0>(e1)==get<0>(e2) && get<1>(e1)<get<1>(e2)); });
	vector<tuple<int,int> > correct2 = {make_tuple(0,1),make_tuple(0,2),make_tuple(0,3),make_tuple(0,4),make_tuple(1,6),make_tuple(3,5),make_tuple(6,7)};
	if(abs(get<0>(ans2)-9.5)>1e-8 || get<1>(ans2)!=correct2) {
		cout << "Failed test 2" << endl;
		return -1;
	}

	for(int i=0; i<100; ++i) {
		vector<tuple<double,double> > locs;
		for(int j=0; j<200; ++j) {
			locs.push_back(make_tuple(rand()%1000,rand()%1000));
		}
		auto yourAns = sidewalkPlan(locs);
		auto myAns = sidewalkPlan2(locs);
		if(abs(get<0>(yourAns)-get<0>(myAns))>1e-6) {
			cout << "Failed random test " << i << endl;
			return -1;
		}
	}

	vector<tuple<double,double> > bigLocs1;
	for(int i=0; i<20000; ++i) {
		bigLocs1.push_back(make_tuple(rand()%100000,rand()%100000));
	}

	// Do Timing
	cout << "Start timing tests." << endl;
	double start = clock();

	auto yourAns1 = sidewalkPlan(bigLocs1);

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	// check
	auto myAns1 = sidewalkPlan2(bigLocs1);
	sort(get<1>(yourAns1).begin(),get<1>(yourAns1).end(),[] (const tuple<int,int> &e1,const tuple<int,int> &e2) { return get<0>(e1) < get<0>(e2) || (get<0>(e1)==get<0>(e2) && get<1>(e1)<get<1>(e2)); });
	sort(get<1>(myAns1).begin(),get<1>(myAns1).end(),[] (const tuple<int,int> &e1,const tuple<int,int> &e2) { return get<0>(e1) < get<0>(e2) || (get<0>(e1)==get<0>(e2) && get<1>(e1)<get<1>(e2)); });
	cout << "your " << get<0>(yourAns1) << endl;
	cout << "my " << get<0>(myAns1) << endl;
	cout << "diff " << get<0>(yourAns1)-get<0>(myAns1) << endl;
	if(abs(get<0>(yourAns1)-get<0>(myAns1))>1e-6 || get<1>(yourAns1)!=get<1>(myAns1)) {
		cout << "Failed big test" << endl;
		return -1;
	}

	return 0;
}