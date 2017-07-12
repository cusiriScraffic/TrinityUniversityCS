#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
using std::cout;
using std::queue;
using std::min;
using std::vector;
using std::tuple;
using std::get;// get<index>(tupleName)

int c(int u, int v, const vector<tuple<int,int,int>>& capacities){
  for (auto edge : capacities){
    if ( get<0>(edge)==u && get<1>(edge)==v ) return get<2>(edge);
  }
  return -1;
}

tuple<int, vector<int>> bfs(vector<vector<int>>& C, vector<vector<int>>& E, vector<vector<int>>& F, int t){
  //cout << "started bfs\n";
  int s = 0;
  int n = C.size();
  vector<int> P(n, -1);
  P[s] = -2;
  vector<int> M(n, 0);
  M[s] = INT_MAX;
  queue<int> Q;
  Q.push(s);
  while (Q.size() > 0){
    int u = Q.front();
    Q.pop();
    for (auto v : E[u]){
      if (C[u][v] - F[u][v] > 0 && P[v] == -1){
        P[v] = u;
        M[v] = min(M[u], C[u][v] - F[u][v]);
        if (v != t){
          Q.push(v);
        }else{
          return tuple<int, vector<int>>(M[t], P);
        }
      }
    }
  }
  //cout << "ended bfs\n";
  return tuple<int, vector<int>>(0, P);
}

vector<tuple<int,int,int>> courierLoads(const vector<int>& orders, const vector<tuple<int,int,int>>& capacities){//pdf page 745
  int numNodes = orders.size();// also sink index

  //make cap
  vector<vector<int>> cap(numNodes+1, vector<int>(numNodes+1, -1));//+1 is the universal sink  (n+1)^2
  for (auto tup : capacities) cap[get<0>(tup)][get<1>(tup)] = get<2>(tup);
  for (int i = 0; i < numNodes; ++i) cap[i][numNodes] = orders[i];
  
  //make neighbors
  vector<vector<int>> neighbors;
  for (int i = 0; i < numNodes; ++i){
    vector<int> tmp;
    for (int j = 0; j < numNodes; ++j){
      if (cap[i][j] != -1) tmp.push_back(j);
    }
    tmp.push_back(numNodes);
    neighbors.push_back(tmp);
  }

  int maxFlow = 0;
  vector<vector<int>> f(numNodes+1, vector<int>(numNodes+1, 0));
  while (true){
    //cout << "started main while\n";
    auto tup = bfs(cap, neighbors, f, numNodes);
    auto m = get<0>(tup);
    auto P = get<1>(tup);
    if (m == 0) break;
    maxFlow += m;
    auto v = numNodes;
    while (v != 0){
      //cout << "started inner while\n";
      auto u = P[v];
      if (cap[u][v] >0){
        f[u][v] += m;
      }else{
        f[v][u] -= m;
      }
      v = u;
      //cout << "ended inner while\n";
    }
  }
    //cout << "ended main while\n";

  //f has been populated
  int orderSum=0;
  for (auto num : orders) orderSum += num;
  vector<tuple<int,int,int>> emptyRet;
  //cout << "orderSum=" << orderSum << "\nmaxFlow=" << maxFlow << "\n";
  if (orderSum > maxFlow) return emptyRet;
  vector<tuple<int,int,int>> ret(capacities);
  for (auto i = 0; i < ret.size(); ++i){
    get<2>(ret[i]) = f[get<0>(ret[i])][get<1>(ret[i])];
  }
  return ret;
}

// int main(void){
//   vector<int> orders{0,0,10,20,15};
//   tuple<int,int,int> tup0(0, 1, 30);
//   tuple<int,int,int> tup1(0, 2, 25);
//   tuple<int,int,int> tup2(1, 3, 50);
//   tuple<int,int,int> tup3(2, 4, 30);
//   vector<tuple<int,int,int>> capacities{tup0, tup1, tup2, tup3};
//   vector<tuple<int,int,int>> ret(courierLoads(orders,capacities));
//   for (auto tup : ret){
//     cout << get<0>(tup) << "," << get<1>(tup) << "," << get<2>(tup) << "\n";
//   }

//   return 0;
// }