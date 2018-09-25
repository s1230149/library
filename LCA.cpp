#include<bits/stdc++.h>
using namespace std;

class LCA{
public:
  typedef pair<int,int> P;
  int LOG_V=20;                       //log V (自分で決めて)
  int V;                              //言わずもがな頂点数
  vector<vector<P> > G;               //グラフの隣接リストの表現
  int root;                           //根のノード番号
  vector<vector<int> > parent;        //親を2^k回辿って到達する頂点(根を通りすぎる場合は-1とする)
  vector<int> depth;                  //根からの深さ
  vector<int> D;                      //根からの距離
  int ok;
  
  LCA():V(-1){}
  LCA(int V,int root = 0)
    :V(V),G(V),root(root),parent(LOG_V,vector<int>(V)),depth(V), D(V,0),ok(0){}
  
  void add_edge(int a, int b,int c = 1){
    assert(a >= 0 && b >= 0);
    assert(a < V && b < V);
    G[a].push_back(P(b,c));
    G[b].push_back(P(a,c));
  }
  
  void dfs(int v,int p,int d,int c){
    assert(v < V);
    parent[0][v] = p;
    depth[v] = d;
    D[v] = c;
    for(auto to:G[v]) 
      if(to.first != p) dfs(to.first, v, d+1, c + to.second);
  }
  
  //vからn個上の祖先
  int getAnc(int v,int n){
    for(int k=0; k<LOG_V ;k++) if((v != -1) && (n>>k&1)) v=parent[k][v];
    return v;
  }

  //初期化
  void build(){
    ok = 1;
    //parent[0]とdepthを初期化する。
    dfs(root,-1,0,0);
    //parentを初期化する
    for(int k=0; k+1<LOG_V ;k++)
      for(int v=0; v<V ;v++)
        if(parent[k][v] < 0)parent[k+1][v] = -1;
        else parent[k+1][v] = parent[k][parent[k][v]];
  }

  //uとvのLCAを求める
  int lca(int u,int v){
    assert(ok);
    assert(u >= 0 && v >= 0);
    assert(u < V && v < V);
    if(depth[u]>depth[v]) swap(u,v);
    v = getAnc(v, depth[v] - depth[u]);
    
    if(u==v) return u;
    //二分探索でLCAを求める
    for(int k=LOG_V-1; k>=0 ;k--)
      if(parent[k][u] != parent[k][v]){
        u = parent[k][u];
        v = parent[k][v];
      }
    return parent[0][u];
  }

  int getDis(int u,int v){
    assert(u >= 0 && v >= 0);
    assert(u < V && v < V);
    return D[u] + D[v] - 2 * D[lca(u, v)];
  }
};

int main(){
  int n;
  cin>>n;
  LCA lca(n);
  
  for(int i=0;i<n;i++){
    int k;
    cin>>k;
    for(int j=0;j<k;j++){
      int c;
      cin>>c;
      lca.add_edge(i,c);
    }
  }

  lca.build();

  int q;
  cin>>q;
  while(q--){
    int u,v;
    cin>>u>>v;
    cout<<lca.lca(u,v)<<endl;
  }
  return 0;
}
