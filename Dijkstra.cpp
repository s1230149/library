#include <bits/stdc++.h>
using namespace std;

class Dijkstra{
public:
  
  typedef tuple<int,int> T;
  long long INF = 1LL<<55;
  int V;
  vector<vector<T> > G;
  
  
  Dijkstra():V(-1){}
  Dijkstra(int V):V(V),G(V){}
  
  void add_edge(int a,int b,int c){
    assert(a >= 0 && b >= 0);
    assert(a < V && b < V);
    G[a].push_back(T(b,c));
    G[b].push_back(T(a,c));
  }

  vector<int> dijkstra(int start){
    vector<int> D(V,INF);
    vector<int> visited(V,0);
    priority_queue<T,vector<T>,greater<T> > Q;
    Q.push(T(0,start));
    D[start] = 0;
    while(!Q.empty()){
      int cost, pos;
      tie(cost,pos) = Q.top(); Q.pop();

      assert(!visited[pos] || D[pos] <= cost);
      if(visited[pos]++) continue;

      for(auto t:G[pos]){
        int to = get<0>(t);
        int ncost = cost + get<1>(t);
        if(D[to] <= ncost) continue;
        D[to] = ncost;
        Q.push(T(ncost,to));
      }
    }
    return D;
  }
};
