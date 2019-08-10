#include <bits/stdc++.h>
using namespace std;

//O(|V||E|)
template<typename ctype, ctype INF>
class BellmanFord{
public:
  double EPS = 1e-8;
  using T = tuple<int, int, ctype>;
  int V;
  vector<vector<int> > G, rG;
  vector<T> edge;
  BellmanFord():V(-1){}
  BellmanFord(int V):V(V), G(V), rG(V){}

  void add_edge(int from, int to,ctype cost){
    assert(0 <= from && from < V);
    assert(0 <= to && to < V);
    edge.push_back(T(from, to, cost));
    G[from].push_back(to);
    rG[to].push_back(from);
  }

  void add_bidirectional_edge(int a,int b,ctype cost){
    add_edge(a, b, cost);
    add_edge(b, a, cost);
  }

  //s番目の頂点から各頂点への最短距離を求める。
  //グラフに負閉路があれば{}を返す。
  vector<ctype> calcDistance(int start){
    assert(0 <= start && start < V);
    vector<ctype> D(V, INF);   //最短距離
    D[start] = 0;

    int cnt = 0;
    bool update = true;
    while(update){
      if(++cnt > V) return {}; //負の閉路
      update = false;
      for(auto e:edge){
        int from, to;
        ctype cost;
        tie(from, to, cost) = e;
        ctype ncost = D[from] + cost;
        if(abs(D[from] - INF) < EPS || ncost - D[to] > -EPS) continue;
        //if(D[from] == INF || ncost >= D[to]) continue;
        D[to] = ncost;
        update = true;
      }
    }
    return D;
  }


  //startからgoalへの最短距離を求める。
  //startからgoalの経路上に負閉路があるか判定する。
  ctype calcDistance(int start, int goal){
    assert(0 <= start && start < V);
    assert(0 <= goal && goal < V);

    vector<int> visited(V, 0); //goalから到達可能なノード
    function<void(int pos)> calcVisited = [&](int pos){
      if(visited[pos]) return;
      visited[pos] = 1;
      for(int to:rG[pos]) calcVisited(to);
    };
    calcVisited(goal);

    vector<ctype> D(V, INF);   //最短距離
    D[start] = 0;
    int cnt = 0;
    bool update = true;
    while(update){
      if(++cnt > V) return -INF; //負の閉路
      update = false;
      for(auto e:edge){
        int from, to;
        ctype cost;
        tie(from, to, cost) = e;
        ctype ncost = D[from] + cost;
        if(abs(D[from] - INF) < EPS || ncost - D[to] > -EPS || visited[to] == 0) continue;
        //if(D[from] == INF || ncost >= D[to] || visited[to] == 0) continue;
        D[to] = ncost;
        update = true;
      }
    }
    return D[goal];
  }
};

void ABC_137_E(){
  using Int = long long;
  const Int INF = 1LL<<55;
  int N, M, P;
  cin>>N>>M>>P;

  BellmanFord<Int, INF> bf(N);
  for(int i=0;i<M;i++){
    int a, b, c;
    cin>>a>>b>>c; a--, b--;
    bf.add_edge(a, b, -c + P);
  }
  Int ans = bf.calcDistance(0, N-1);
  if(ans == -INF) cout<<-1<<endl;
  else cout<<max(0LL, -ans)<<endl;

}

void AOJ_GRL_1_B(){
  int N, M, start;
  cin>>N>>M>>start;

  typedef long long ll;
  const ll INF = 1e18;
  BellmanFord <ll, INF> bf(N);
  for(int i=0;i<M;i++){
    int from, to, cost;
    cin>>from>>to>>cost;
    bf.add_edge(from, to, cost);
  }

  vector<ll> D = bf.calcDistance(start);
  if(D.empty()) cout<<"NEGATIVE CYCLE"<<endl;
  else {
    for(int i=0;i<N;i++)
      if(D[i] != INF) cout<<D[i]<<endl;
      else cout<<"INF"<<endl;
  }
}


signed main(){
  //ABC_137_E();
  //AOJ_GRL_1_B();
  return 0;
}
