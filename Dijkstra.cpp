#include <bits/stdc++.h>
using namespace std;

template<typename ctype, ctype INF>
class Dijkstra{
public:
  typedef tuple<int,ctype> T;  //for edge
  typedef tuple<ctype,int> T2; //for priority_queue
  int V;
  vector<vector<T> > G;
  vector<vector<T> > rG;
  
  Dijkstra():V(-1){}
  Dijkstra(int V):V(V),G(V),rG(V){}
  
  void add_edge(int a,int b,ctype c,int oneway = 0){
    assert(a >= 0 && b >= 0);
    assert(a < V && b < V);
    G[a].push_back(T(b, c));
    rG[b].push_back(T(a, c));
    if(!oneway) G[b].push_back(T(a, c)), rG[a].push_back(T(b, c));
  }

  vector<ctype> dijkstra(int start, int rev = 0){
    vector<ctype> D(V, INF);
    vector<int> visited(V,0);
    priority_queue<T2, vector<T2>, greater<T2> > Q;
    Q.push(T2(0, start));
    D[start] = 0;
    while(!Q.empty()){
      ctype cost;
      int pos;
      tie(cost,pos) = Q.top(); Q.pop();
      assert(!visited[pos] || D[pos] <= cost);
      if(visited[pos]++) continue;
      
      for(auto t:rev == 0? G[pos]:rG[pos]){
	int to = get<0>(t);
        ctype ncost = cost + get<1>(t);
        if(D[to] <= ncost) continue;
        D[to] = ncost;
        Q.push(T2(ncost, to));
      }
    }
    return D;
  }
  
  vector<vector<int> > getDAG(int start, int goal){
    auto DS = dijkstra(start, 0);
    auto DT = dijkstra(goal, 1);
    vector<vector<int> > DAG(V);
    vector<int> visited(V,0);
    queue<int> Q;
    Q.push(start);
    while(!Q.empty()){
      int pos; pos = Q.front(); Q.pop();
      if(visited[pos]++) continue;
      
      for(auto t:G[pos]){
        int to = get<0>(t);
        ctype cost = get<1>(t);
	if(DS[pos] + DT[to] + cost != DS[goal]) continue;
	Q.push(to);
	DAG[pos].push_back(to);
      }
    }
    return DAG;
  }
};


int main(){
  int V, E, r;
  cin>>V>>E>>r;
  Dijkstra <long long, 1LL<<55> dijkstra(V);
  for(int i=0;i<E;i++){
    int s, t, d;
    cin>>s>>t>>d;
    dijkstra.add_edge(s, t, d, 1);
  }

  auto ans = dijkstra.dijkstra(r);
  for(int i=0;i<V;i++) {
    if(ans[i] == 1LL<<55) cout<<"INF"<<endl;
    else cout<<ans[i]<<endl;
  }
}
