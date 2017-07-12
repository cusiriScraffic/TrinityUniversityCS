#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
using std::cout;
using std::min;
using std::vector;
using std::tuple;
using std::get;

void print(const vector<vector<int>>& x){
  for (auto vec : x){
    for (auto num : vec){
      cout << num << "\t";
    }
    cout << "\n";
  }
}

vector<vector<int>> makePi(const vector<vector<int>>& difficulties){
  vector<vector<int>> pi(difficulties);
  int n = difficulties.size();
  for (auto i = 0; i < n; ++i){
    for (auto j = 0; j < n; ++j){
      if (i == j || difficulties[i][j] >= 1000000000){
        pi[i][j] = -1;
      }else{
        pi[i][j] = i;
      }
    }
  }
  return pi;
}

tuple<vector<vector<int>>, vector<vector<int>> > crossCountryChallenge(const vector<vector<int>> &difficulties){//Floyd-Warshall pdf page 716
  int n = difficulties.size();
  vector<vector<int>> pi( makePi(difficulties) );
  vector<vector<int>> d(difficulties);

  for (int k=0; k < n; ++k){
    vector<vector<int>> dK(d);
    vector<vector<int>> piK(pi);
    for (int i=0; i < n; ++i){
      for (int j = 0; j < n; ++j){
        dK[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        if (d[i][j] > d[i][k] + d[k][j]) piK[i][j] = pi[k][j];
      }
    }
    d = dK;
    pi = piK;
  }
  
 return tuple< vector<vector<int>>, vector<vector<int>> > (d, pi);
}

// int main(void){
//   int inf = 1000000000;
//   vector<int> v0{0, 3,8,inf,-4};
//   vector<int> v1{inf, 0, inf, 1, 7};
//   vector<int> v2{inf, 4, 0, inf, inf};
//   vector<int> v3{2, inf, -5, 0, inf};
//   vector<int> v4{inf, inf, inf, 6, 0};
//   vector<vector<int>> diff{v0, v1, v2, v3, v4};

//   tuple<vector<vector<int>>, vector<vector<int>>> ret( crossCountryChallenge(diff) );
//   vector<vector<int>> d( get<0>(ret) );
//   vector<vector<int>> pi( get<1>(ret) );

//   print(d);
//   cout << "\n";
//   print(pi);

//   return 0;
// }