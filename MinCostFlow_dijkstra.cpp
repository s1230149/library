#include<bits/stdc++.h>
using namespace std;

template<typename T, T INF>
class MinCostFlow{
public:
  typedef long long ll;
  //辺を表す構造体(行き先、容量、コスト、逆辺)
  struct edge{
    int to;
    ll cap;
    T cost;
    int rev;
    edge();
    edge(int to,ll cap,T cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
  };
  
  int V;                          //頂点数
  vector<vector<edge> > G;        //グラフの隣接リスト表現
  vector<T> dist;             //最短距離
  vector<int> prevv,preve;        //直前の頂点と辺
  vector<T> h;                //ポテンシャル
  MinCostFlow():V(-1){}
  MinCostFlow(int V):V(V), G(V), dist(V), prevv(V), preve(V){};
  
  // fromからtoへ向かう容量cap、コストcostの辺をグラフに追加する。
  void add_edge(int from,int to,ll cap ,T cost){
    assert(from>=0 && to >= 0);
    assert(from<V && to<V);
    G[from].push_back((edge){to,cap,cost,(int)G[to].size()});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1});
  }
  
  //sからtへの流量fの最小費用流を求める。
  T flow(int s, int t, ll f){
    typedef pair<T, int> P; //firstは最短距離、secondは頂点の番号
    T res = 0;
    h.clear();
    h.resize( V, 0 );
    while(f > 0){
      //ダイクストラ法を用いてhを更新する。
      priority_queue <P, vector<P>, greater<P> > que;
      vector<int> visited(V, 0);
      dist.clear();
      dist.resize(V, INF);
      dist[s] = 0;
      que.push(P(0,s));
      while(!que.empty()){
	P p = que.top(); que.pop();
	int v= p.second;
	if(visited[v]++) continue;
	if(dist[v] < p.first) continue;
	for(int i=0; i<(int)G[v].size() ;i++){
	  edge &e = G[v][i];
	  if(visited[e.to] == 0 && e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
	    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
	    prevv[e.to] = v;
	    preve[e.to] = i;
	    que.push(P(dist[e.to],e.to));
	  }
	}
      }
      if(dist[t]==INF) return -1; //これ以上流せない
      for(int v=0; v<V ;v++) h[v] += dist[v];
      
      //s−t間最短路に沿って目一杯流す。
      ll d = f;
      for(int v=t; v!=s ;v=prevv[v]) 
	d = min(d, (ll)G[prevv[v]][preve[v]].cap);
    
      f -= d;
      res += d * h[t];
      for(int v=t; v!=s; v=prevv[v]){
	edge &e = G[prevv[v]][preve[v]];
	e.cap -= d;
	G[v][e.rev].cap += d;
      }
    }
    return res;
  }
};
