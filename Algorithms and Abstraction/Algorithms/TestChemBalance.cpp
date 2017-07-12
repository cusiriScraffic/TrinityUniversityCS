#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <set>
#include <tuple>
#include <cmath>

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

vector<double> LUPSolve(const vector<vector<double>> &A,const vector<int> &pi,const vector<double> &b);
vector<int> LUPDecomposition(vector<vector<double>> &A);
tuple<vector<int>,vector<int>> chemBalance(const string &equ);

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);

	auto b1 = chemBalance("CH4+O2=H2O+CO2");
	vector<int> l1{1,2};
	vector<int> r1{2,1};
	if(b1!=make_tuple(l1,r1)) {
		cout << "Failed test 1" << endl;
		return 1;
	}

	/*
	auto b2 = chemBalance("C2H6+O2=H2O+CO2");
	vector<int> l2{2,7};
	vector<int> r2{6,4};
	if(b2!=make_tuple(l2,r2)) {
		cout << "Failed test 2" << endl;
		return 1;
	}
	*/

	vector<string> elems{"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar"};

	// Do Timing
	cout << "Start timing tests." << endl;
	double start = clock();

	for(int i=0; i<395;) {
		int left = elems.size()/2+3;
		int right = elems.size()-left+1;
		vector<vector<double>> mat(elems.size(),vector<double>(elems.size(),0.0));
		vector<int> ansLeft;
		vector<int> ansRight;
		string str;
		vector<int> cnt(elems.size());
		for(int j=0; j<left; ++j) {
			if(j>0) str += "+";
			int coef = rand()%5+1;
			ansLeft.push_back(coef);
			int numElems = rand()%7+2;
			for(int k=0; k<numElems; ++k) {
				int elem = rand()%elems.size();
				int num = rand()%15+1;
				cnt[elem] += num*coef;
				str += elems[elem]+std::to_string(num);
				mat[elem][j] += num;
			}
		}
		str+="=";
		bool flag = true;
		for(int j=0; j<right-1 && flag; ++j) {
			if(str[str.size()-1]=='+') flag = false;
			else {
				if(j>0) str += "+";
				int coef = rand()%5+1;
				ansRight.push_back(coef);
				int numElems = rand()%7+2;
				for(int k=0; k<numElems; ++k) {
					int elem = rand()%elems.size();
					if(cnt[elem]>=coef) {
						int num = rand()%15+1;
						if(cnt[elem]<num*coef) num=cnt[elem]/coef;
						cnt[elem] -= coef*num;
						str += elems[elem]+std::to_string(num);
						mat[elem][j+left] -= num;
					}
				}
			}
		}
		if(flag) {
			vector<vector<double>> mat2(mat);
			vector<int> pi = LUPDecomposition(mat);
			if(pi.size()>0) {
//				cout << "Test input matrix is:\n";
//				for(auto &r:mat2) {
//					for(auto x:r) cout << x << " "; cout << "\n";
//				}
				str += "+";
				ansRight.push_back(1);
				vector<double> y;
				for(unsigned int j=0; j<elems.size(); ++j) {
					if(cnt[j]>0) str += elems[j]+std::to_string(cnt[j]);
					y.push_back(cnt[j]);
				}
//				cout << str << endl;
				auto ans = chemBalance(str);
				if(ans!=make_tuple(ansLeft,ansRight)) {
					vector<double> x = LUPSolve(mat,pi,y);
					bool flag = true;
					for(unsigned int i=0; i<x.size() && flag; ++i) if(x[i]<0) flag = false;
					if(flag) {
						cout << "Failed big test " << i << endl;
						cout << "Answer expected: ";
						cout << "Left: ";
						for(int i:ansLeft) cout << i << " ";
						cout << endl;
						cout << "Right: ";
						for(int i:ansRight) cout << i << " ";
						cout << endl;
						cout << "LUP: ";
						for(double d:x) cout << d << " ";
						cout << endl;
						cout << "Answer given:\n";
						for(auto a:get<0>(ans)) cout << a << " "; cout << "\n";
						for(auto a:get<1>(ans)) cout << a << " "; cout << "\n";
						return 1;
					} else {
						cout << "That test sucks. On to the next one.\n";
					}
				}
				++i;
			}
		}
	}

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	// check


	return 0;
}
