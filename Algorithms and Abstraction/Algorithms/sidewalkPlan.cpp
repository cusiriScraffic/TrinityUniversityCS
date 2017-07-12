#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cmath>
#include <limits>
#include "DisjointSet.h"


using std::vector;
using std::tuple;
using std::make_tuple;
using std::min;
using std::max;
using std::swap;
using std::move;
using std::numeric_limits;
using std::get;
using std::endl;
using std::cout;
using std::abs;
using std::sort;



// void shortenForLoop(vector<tuple<int,double>> nodes,const vector<tuple<double, double> > &buildingLocations,vector<int> visitedParents)
// {
// 	auto beginingIteration = nodes.begin();
// 	auto maxValueOfDouble = numeric_limits<double>::max();
// 	for(auto v = nodes.begin();v!= nodes.end();v++)
// 	{
// 		int j = get<0>(*v);
// 		const tuple<double,double> &locationNumber1 = buildingLocations[i];
// 		const tuple<double,double> &locationNumber2 = buildingLocations[j];
// 		auto distance1 = get<0>(locationNumber1) - get<0>(locationNumber2);
// 		auto distance2 = get<1>(locationNumber1) - get<1>(locationNumber2);
// 		auto totalDistance = sqrt((distance1*distance1)+ (distance2*distance2));
// 		if(totalDistance < get<1>(*v))
// 		{
// 			visitedParents[j] = i;
// 			get<1>(*v) = totalDistance;
// 		}
// 		if(get<1>(*v)< maxValueOfDouble)
// 		{
// 			maxValueOfDouble = get<1> (*v);
// 			beginingIteration = v;
// 		}
// 		if(beginingIteration != nodes.begin())
// 		{
// 			swap(*beginingIteration, nodes.front());
// 		}
// 	}
// };
double distance(double x1, double y1, double x2, double y2) 
{
	double xdis = pow((x2 -x1), 2);
	double ydis = pow((y2 -y1), 2);
	double totaldis = sqrt(xdis + ydis);
	return totaldis;
}

bool operator<(tuple<double,tuple<int,int>> &a, tuple<double,tuple<int,int>> &b) 
{
 	return get<0>(a) < get<0>(b);
}

//	returns length of sidewalks
tuple<double,vector<tuple<int,int> > > sidewalkPlan(const vector<tuple<double, double> > &buildingLocations) 
{
	double sum = 0;
	vector<DisjointSet<int>*> dS;
	for (auto i =0; i < buildingLocations.size(); ++i) {
		auto tmp = new DisjointSet<int>(i);
		dS.push_back(tmp);
	}
	//cout << dS[0].getMarker() << "\n";
	vector<tuple<double,tuple<int,int>>> edgeList;
	for (auto i = 0; i < dS.size(); ++i) {
 		for (auto j = i+1; j < dS.size(); ++j) {
 			//double weight = distance(get<0>(buildingLocations[i]), get<1>(buildingLocations[i]), get<0>(buildingLocations[j]), get<1>(buildingLocations[j]));
 			edgeList.push_back(make_tuple(2.1, make_tuple(i,j)));
 		}
 	}
 	sort(edgeList.begin(), edgeList.end());
 	for (auto a = 0; a < edgeList.size(); ++a) 
 	{
 		auto tmpA = get<0>(get<1>(edgeList[a]));
 		auto tmpB = get<1>(get<1>(edgeList[a]));
 		if ( dS.getMarker(tmpA) != dS.getMarker(tmpB) ) 
 		{

    	}
 	}
	//return make_tuple(sum, dS);
}

/*vector<tuple<double, tuple<int,int>>> makeEdges(const vector<tuple<double, double> > locations) {
 	vector<tuple<double,tuple<int,int> > > edgeList;	
 	for (auto i = 0; i < locations.size(); ++i) {
 		for (auto j = i+1; j < locations.size(); ++j) {
 			double weight = distance(get<0>(locations[i]), get<1>(locations[i]), get<0>(locations[j]), get<1>(locations[j]));
 			edgeList.push_back(make_tuple(weight, make_tuple(i,j)));
 		}
 	}
 	cout << edgeList.size() << "\n";
 	sort(edgeList.begin(), edgeList.end());
 	return edgeList;
}*/
// tuple<double,vector<tuple<int,int>>> sidewalkPlan(const vector<tuple<double, double> > &buildingLocations)
// {
// 	// Declarations, this uses prims algorithm to find the minimum spanning tree
// 	int numberOfBuildingLocations = buildingLocations.size();
// 	int returnTotalNumber = 0;
// 	vector<int> visitedParents(numberOfBuildingLocations, -1);
// 	vector<tuple<int,double>> nodes;
// 	vector<tuple<int,int>> reservationContainer;
// 	nodes.reserve(numberOfBuildingLocations); // Requests that vector capacity be enough to contain n elements
// 	nodes.push_back(make_tuple(0,0)); // Initializing nodes
// 	for(int i = 1; i < numberOfBuildingLocations; i++)
// 	{
// 		nodes.push_back(make_tuple(i,numeric_limits<double>:: max()));
// 	}
// 	while(nodes.size() > 0)
// 	{	
// 		auto n = nodes.front();
// 		swap(nodes.front(),nodes.back());
// 		nodes.pop_back();
// 		int i = get<0>(n);//Dr Jiang addtion
// 		if(visitedParents[i] != -1)
// 		{
// 			returnTotalNumber += get<1>(n);
// 			reservationContainer.push_back(make_tuple(((min(i,visitedParents[i]))), (max(i,visitedParents[i]))));
// 		}
// 		// shortenForLoop(nodes,buildingLocations,visitedParents,i);
// 		auto beginingIteration = nodes.begin();
// 		auto maxValueOfDouble = numeric_limits<double>::max();
// 		for(auto v = nodes.begin();v!= nodes.end();v++)
// 		{
// 			int j = get<0>(*v);
// 			const tuple<double,double> &locationNumber1 = buildingLocations[i];
// 			const tuple<double,double> &locationNumber2 = buildingLocations[j];
// 			auto distance1 = get<0>(locationNumber1) - get<0>(locationNumber2);
// 			auto distance2 = get<1>(locationNumber1) - get<1>(locationNumber2);
// 			auto totalDistance = sqrt((distance1*distance1)+ (distance2*distance2));
// 			if(totalDistance < get<1>(*v))
// 			{
// 				visitedParents[j] = i;
// 				get<1>(*v) = totalDistance;
// 			}
// 			if(get<1>(*v)< maxValueOfDouble)
// 			{
// 				maxValueOfDouble = get<1> (*v);	
// 				beginingIteration = v;
// 			}
// 			if(beginingIteration != nodes.begin())
// 			{
// 				swap(*beginingIteration, nodes.front());
// 			}

// 		}
		
// 	}
// 	return make_tuple(returnTotalNumber, move(reservationContainer));
// return = std::make_tuple(total, std::move(edges));
//};

int main()
{
	vector<tuple<double,double> > locs1 = {make_tuple(0,0),make_tuple(1,0),make_tuple(-1,0),make_tuple(0,2),make_tuple(0,-2)};
	auto ans1 = sidewalkPlan(locs1);
	sort(get<1>(ans1).begin(),get<1>(ans1).end(),[] (const tuple<int,int> &e1,const tuple<int,int> &e2) { return get<0>(e1) < get<0>(e2) || (get<0>(e1)==get<0>(e2) && get<1>(e1)<get<1>(e2)); });
	vector<tuple<int,int> > correct1 = {make_tuple(0,1),make_tuple(0,2),make_tuple(0,3),make_tuple(0,4)};
	if(abs(get<0>(ans1)-6.0)>1e-8 || get<1>(ans1)!=correct1) {
		cout << "Failed test 1" << endl;
		return -1;
	}
	// vector<tuple<double,double> > locs2 = {make_tuple(0,0),make_tuple(1,0),make_tuple(-1,0),make_tuple(0,2),make_tuple(0,-2),make_tuple(0.5,2),make_tuple(3,0),make_tuple(3,1)};
	// auto ans2 = sidewalkPlan(locs2);
	// sort(get<1>(ans2).begin(),get<1>(ans2).end(),[] (const tuple<int,int> &e1,const tuple<int,int> &e2) { return get<0>(e1) < get<0>(e2) || (get<0>(e1)==get<0>(e2) && get<1>(e1)<get<1>(e2)); });
	// vector<tuple<int,int> > correct2 = {make_tuple(0,1),make_tuple(0,2),make_tuple(0,3),make_tuple(0,4),make_tuple(1,6),make_tuple(3,5),make_tuple(6,7)};
	// if(abs(get<0>(ans2)-9.5)>1e-8 || get<1>(ans2)!=correct2) {
	// 	cout << "Failed test 2" << endl;
	// 	return -1;
	// }
	cout<<
}
