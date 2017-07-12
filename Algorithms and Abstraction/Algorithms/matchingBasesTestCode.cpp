#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::rand;
using std::cout;
using std::pair;

int matchingBases(string strand);
// int myMatchingBases(string strand);

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);

	int ans1 = matchingBases("CCACUGAACAGUG");
	if(ans1!=5) {
		cout << "Failed first test. " << ans1 << endl;
		return -1;
	}
	int ans2 = matchingBases("ACGUGCCACGAUUCAACGUGGCACAG");
	if(ans2!=11) {
		cout << "Failed second test. " << ans2 << endl;
		return -1;
	}
	int ans3 = matchingBases("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
	if(ans3!=0) {
		cout << "Failed third test. " << ans3 << endl;
		return -1;
	}
	int ans4 = matchingBases("AAAAAGAAAAAAAAAAAGAAAAGGAAAAAAAAAAAAAGGGAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGGGGAAAAAAAAAAAAAAAAAAGGAAAAAAAAAAAAAAAAAAAAUUUUUUUUUUGGGGUUUUUUUUUUUUUUUUUUUUUGGGUUUUUUUUUUUUUUUUUUUUUGGUUUUUUUUGGGUUUUUUUUUUUUUUUUUUGGUUUUUUUUUUUUUUUUUUUUUUGG");
	if(ans4!=100) {
		cout << "Failed fourth test. " << ans4 << endl;
		return -1;
	}
	int ans5 = matchingBases("UACCCCAU");
	if(ans5!=1) {
		cout << "Failed fifth test. " << ans5 << endl;
		return -1;
	}

	string str;
	string bases = "ACGU";
	for(int i=0; i<40000; ++i) {
		str.push_back(bases[rand()%4]);
	}
	// Do Timing
	double start = clock();
	int ans = matchingBases(str);
	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	// check
	// double myans = myMatchingBases(str);
	// if(ans!=myans) {
	// 	cout << ans << " != " << myans << endl;
	// 	return -1;
	// }

	return 0;
}