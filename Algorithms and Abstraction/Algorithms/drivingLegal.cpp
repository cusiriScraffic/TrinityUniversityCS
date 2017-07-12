#include<vector>
#include<set>
#include<queue>
#include<iostream>
#include<unordered_map>
using std::unordered_map;
using std::pair;
using std::cout;
using std::vector;
using std::set;
using std::queue;
using std::priority_queue;

struct Node{
  int loc;
  char color;
  Node* parent;
  int d;
  int f;
  Node(int l): loc(l), color('w'), parent(nullptr), d(0), f(0) {}
};
struct lessThan{ bool operator()(Node* x, Node* y){ return (x->f < y->f);}};

void dfsVisit(const vector<vector<int>>& roadTo, Node* u, int& time, vector<Node*>& nodes){
  ++time;
  u->d = time;
  u->color = 'g';
  vector<int> adj(roadTo[u->loc]);// adjacent locations
  for (auto i : adj){
    Node* v(nodes[i]);
    if (v->color == 'w'){
      v->parent = u;
      dfsVisit(roadTo, v, time, nodes);
    }
  }
  u->color = 'b';
  ++time;
  u->f = time;
  //cout << "dfsVisit: location=" << u->loc << ", f=" << u->f << "\n";
}

vector<Node*> dfs(const vector<vector<int>>& roadTo){
  vector<Node*> nodes;
  for (auto i = 0; i < roadTo.size(); ++i) nodes.push_back(new Node(i));

  int time = 0;
  for (auto i = 0; i < roadTo.size(); ++i){
    Node* u(nodes[i]);
    if (u->color == 'w') dfsVisit(roadTo, u, time, nodes);
  }
  return nodes;
}

vector<Node*> dfsT(const vector<vector<int>>& roadTo, vector<Node*>& nodes){
  for (auto i : nodes){
    i->color = 'w';
    i->parent = nullptr;
  }
  int time = 0;

  // consider vertices in order of decreasing u.f
  priority_queue<Node*, vector<Node*>, lessThan> fMax;
  for (auto i = nodes.begin(); i != nodes.end(); ++i) fMax.push(*i);
  int sz = fMax.size();
  for (auto i = 0; i < sz; ++i){
    Node* u(fMax.top());
    fMax.pop();
    if (u->color == 'w') dfsVisit(roadTo, u, time, nodes);
  }
  return nodes;
}

vector<vector<int>> transpose(const vector<vector<int>>& roadTo){
  vector<vector<int>> ret;
  for (auto i = 0; i < roadTo.size(); ++i){
    vector<int> tmp;
    ret.push_back(tmp);
  }
  for (auto i = 0; i < roadTo.size(); ++i){
    for (auto j = 0; j < roadTo[i].size(); ++j){
      int val = roadTo[i][j];
      ret[val].push_back(i);
    }
  }
  return ret;
}


vector<set<int>> drivingLegal(const vector<vector<int>>& roadTo){
  vector<set<int>> clusters;

  vector<Node*> gNodes( dfs(roadTo) );
  vector<vector<int>> gT(transpose(roadTo));
  vector<Node*> gTNodes( dfsT(gT, gNodes) );

  unordered_map<int,set<int>*> map;
  for (auto node : gTNodes){
    if (!node->parent){
      //cout << "no parent: " << node->loc << "\n";
      map.insert(pair<int,set<int>*>( node->loc, new set<int>({node->loc}) ));
    }
  }
  for (auto node : gTNodes){
    if (node->parent){
      Node* rover(node->parent);
      while (rover->parent) rover = rover->parent;
      set<int>* mySet( (*map.find(rover->loc)).second );
      mySet->insert(node->loc);
      //cout << "parent: " << node->loc << " inserted into " << rover->loc << "\n";
    }
  }
  for (auto i : map){
    clusters.push_back(*i.second);
  }
  return clusters;
}