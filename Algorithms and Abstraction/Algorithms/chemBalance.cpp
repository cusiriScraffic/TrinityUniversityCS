#include <vector>
#include <iostream>
#include <tuple>
#include <map>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <list>
#include <numeric>
#include <random>

using std::fabs;
using std::cout;
using std::swap;
using std::vector;
using std::tuple;
using std::string;
using std::map;
using std::string;

using matrix = vector<vector<double>>;

inline bool isUpper(char x) 
{
  return (x >= 'A' && x <= 'Z');
}

inline bool isLower(char x) 
{
  return (x >= 'a' && x <= 'z');
}

inline bool isDigit(char x) 
{
  return (x >= '0' && x <= '9');
}
void multiply(const matrix& m1, const matrix& m2, matrix& ret) 
{
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
void LUP(matrix& A, vector<int>& pi) 
{
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

inline void LUPInvert(const matrix& A, const vector<int>& p, const int n, matrix& iA) 
{
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
tuple<vector<int>, vector<int>> chemBalance(const string &equ) 
{
  int idx = 0;
  int currVar = 0;
  int sgn = 1;
  map<string, int> dict;
  vector<vector<double>> A;
  vector<vector<double>> b;
  int sz = equ.size();
  int eq_div = -1;
  while (idx < sz) 
  {
    string currElem;
    while(idx < sz && equ[idx] != '=' && equ[idx] != '+') 
    {
      if (isUpper(equ[idx])) {
        currElem = "";
        currElem = equ[idx];
        ++idx;
        if(idx << sz && isLower(equ[idx])) 
        {
          currElem += equ[idx];
          ++idx;
        }
        string c = "";
        int coef = 1;
        while (idx < sz && isDigit(equ[idx])) 
        {
          c += equ[idx];
          ++idx;
        }
        if (c != "") {
          coef = stoi(c);
        }
        int elem;
        if(dict.count(currElem)) 
        {
          elem = dict[currElem];
          A[elem].resize(currVar+1, 0);
        } else {
          A.push_back(vector<double>(currVar+1, 0));
          elem = A.size()-1;
          dict[currElem] = elem;
        }
        A[elem][currVar] += coef*sgn;
        } else {
          ++idx;
        }
      }
      if (idx < sz && equ[idx] == '=') 
      {
        sgn = -1;
        eq_div = currVar + 1;
      }
      ++idx;
    }

    assert(A.size() == A[0].size());
    vector<int> pi(A.size());
    LUP(A,pi);
    vector<double> res(A.size());

    LUPInvert(A, pi, b.size(), res);

    res.push_back(1);
    for(unsigned int i = 0; i < res.size(); ++i) 
    {
      res[i] = round(res[i]);
    }
    
    vector<int> v1 (res.begin(),res.begin()+eq_div);
    vector<int> v2 (res.begin()+eq_div,res.end());
    return make_tuple(std::move(v1), std::move(v2));
}