#include <vector>
#include <iostream>

#include "LinearFit.h"



using std::cout;
using std::vector;

void printMatr(vector<vector<double>>& m) {
    for(const auto& r : m) {
        for(const double& i : r)
            cout << i << " ";
        cout << "\n";
    }
}

int main(void) {
    // test multiply
    vector<vector<double>> m1 {
        {1,2,0},
        {3,4,4},
        {5,6,3}
    };
    vector<vector<double>> m2 {
        {3},
        {7},
        {8}
    };
    vector<vector<double>> poop;
    multiply(m1, m2, poop);
    printMatr(poop);

    
    vector<vector<double>> fina = m1;
    vector<int> p;
    cout << "LU: " << "\n";
    LUP(m1, p);
    printMatr(m1);
    cout << "\n" << "Permutation: " << "\n";
    //for(int i : p) cout << i << "\n";

    vector<vector<double>> m3;
    //vector<int> pi {2,1,0};
    LUPInvert(m1, p, m1.size(), m3);

    vector<vector<double>> prod2;
    multiply(fina, m3, prod2);    

    cout << "\n" << "inverse: " << "\n";
    printMatr(m3);

    cout << "\n" << "orig * inverse" << "\n";
    printMatr(prod2);





    /*vector< vector<double> > mult;
    multiply(m1, m2, mult);

    //test transpose.
    vector< vector<double> > trans;
    transpose(mult, trans);
        
    printMatr(mult);
    printMatr(trans);

    vector<int> p(0);
    LUP(mult, p);
    vector<vector<double>> in;
    LUPInvert(mult, p, mult.size(), in);


    vector<vector<double>> prod;
    printMatr(in);
    multiply(in, mult, prod); 
    printMatr(prod);
*/

    return 0;
}
