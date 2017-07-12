#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
//#include <numerics> 

using std::fabs;
using std::cout;
using std::swap;
using std::vector;

using matrix = vector< vector<double> >;

void multiply(const matrix& m1, const matrix& m2, matrix& ret) {
    assert(m1[0].size() == m2.size()); 
    ret.resize(m1.size(), vector<double>(m2[0].size(), 0));
    for(int i = 0; i < m1.size(); ++i)
        for(int j = 0; j < m2[0].size(); ++j)
            for(int k = 0; k < m1[0].size(); ++k)
                ret[i][j] += m1[i][k] * m2[k][j];
}

void transpose(const matrix& m, matrix& ret) 
{
    const int r = m.size();
    const int c = m[0].size();
    ret.resize(c, vector<double>(r)); // MxN -> NxM
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            ret[j][i] = m[i][j];
}

void LUP(matrix& A, vector<int>& pi) {
    const int n = A.size();
    pi.resize(n, 0);
    std::iota(pi.begin(), pi.end(), 0);
    for(int k = 0; k < n; ++k) {
        double p = 0;
        int kp = k;
        for(int i = k; i < n; ++i)
            if(fabs(A[i][k]) > p) {
                p = fabs(A[i][k]);
                kp = i;
            }
        if(p == 0) {
            std::cout << "singular matrix";
            return;
        }
        if(kp != k) swap(pi[kp], pi[k]);
        for(int i = 0; i < n; ++i) swap(A[k][i], A[kp][i]);        
        for(int i = k + 1; i < n; ++i) {
            A[i][k] = A[i][k] / A[k][k];
            for(int j = k + 1; j < n; ++j)
                A[i][j] -= (A[i][k] * A[k][j]);
        }
    }
}

void LUPInvert(const matrix& A, const vector<int>& p, const int n, matrix& iA) {
    iA.resize(A.size(), vector<double>(A[0].size(), 0));
    for(int j = 0; j < n; ++j) {
        for(int i = 0; i < n; ++i) {
            if(p[i] == j) iA[i][j] = 1.0;
            for(int k = 0; k < i; ++k)
                iA[i][j] -= A[i][k] * iA[k][j];
        }
        for(int i = n-1; i >= 0; --i) {
            for(int k = i+1; k < n; ++k)
                iA[i][j] -= A[i][k] * iA[k][j];
            iA[i][j] = iA[i][j] / A[i][i];
        }
    }
}

template<class T, class F>
vector<double> fitFuncs(const vector<T>& data, const vector<F>& functions) {
    //fills y
    matrix y(data.size(), vector<double>(1));
    for(int i = 0; i < data.size(); ++i) y[i][0] = data[i].y;

    //fills A with f(x)'s
    //check if this fills it ccorrectly
    matrix A = matrix(data.size(), vector<double>(functions.size()));
    for(int x = 0; x < data.size(); ++x)
        for(int y = 0; y < functions.size(); ++y)
            A[x][y] = functions[y](data[x].x);
    
    matrix At;
    transpose(A, At); //transpose A
    matrix AtA;       
    multiply(At, A, AtA); //multiply A by its transpose 
    
    vector<int> p;
    LUP(AtA, p);          //get LUP decomp for AtA
    matrix AtAi;
    LUPInvert(AtA, p, AtA.size(), AtAi); //Invert AtA

    matrix Aty;
    multiply(At, y, Aty); //multiply y by A's transpose
    
    matrix coef;
    multiply(AtAi, Aty, coef);  //multiply AtA inverse by  Aty to get coef
    
    vector<double> ret;
    for(auto v : coef) {
        ret.push_back(v[0]);    //put coefficients in a vector
    }
    return ret; //return the coefficients. 
}
