#include <bits/stdc++.h>
using namespace std;

class HLD{
public:
  int V;                     //ノード数
  int root;                  //根の頂点番号
  vector<vector<int> > G;    //Grapth
  vector<int> par;           //parent: par[元の頂点番号]->元の頂点番号
  vector<int> Hchild;        //各ノードから伸びるHeavy Childの頂点番号: Hedge[元の頂点番号]->元の頂点番号
  vector<int> number;        //各ノードに割り当てなおした頂点番号: number[元の頂点番号]->振り直した頂点番号
  vector<int> id;            //割り当て直した数字の元のノード番号: id[振り直した頂点番号]->元の頂点番号
  vector<int> group;         //各ノードが所属するグループ番号: group[元の頂点番号]->元の頂点番号
  vector<int> depth;         //根からの各ノードの深さ: depth[元の頂点番号]
  bool ok;                   //build()が済んでいるか
  
  HLD(){root = V = -1;}
  HLD(int V):V(V), root(0), G(V), par(V,-1), Hchild(V,-1), 
             number(V,-1),id(V,-1),group(V,-1),depth(V,0),ok(false){}
  
  void add_edge(int a,int b){
    assert(a < V && b < V);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  void build(int _root = 0){
    root = _root;
    int num = 0;
    ok = true;
    dfs1(); numbering(num); dfs2();
  }

  int dfs1(int pos = -1,int pre = -1){
    if(pos == -1) pos = root;
    int mx = -1, weight = 1;
    for(int to:G[pos]){
      if(to == pre) continue;
      int cweight = dfs1(to,pos);
      weight += cweight;
      if(mx < cweight) Hchild[pos] = to, mx = cweight;
    }
    return weight;
  }
  
  void dfs2(int pos = -1,int pre = -1,int dep = 0,int g = -1){
    if(pos == -1) pos = g = root;
    par[pos] = pre;
    depth[pos] = dep;
    group[pos] = g;
    for(int to:G[pos]) if(to!=pre) dfs2(to,pos,dep+1,Hchild[pos]==to? g:to);
  }
  
  void numbering(int &cnt,int pos = -1,int pre = -1){
    if(pos == -1) pos = root;
    number[pos] = cnt++;
    id[number[pos]] = pos;
    if(Hchild[pos]>=0) numbering(cnt,Hchild[pos],pos);
    for(int to:G[pos])if(to!=pre && to!=Hchild[pos]) numbering(cnt,to,pos);
  }
  
  typedef pair<int,int> P;
  vector<P> paths;  //[u,v]間の経路をいくつかの「閉区間の連番の経路」に分解する。(最大logN個に分解される)
  vector<P> Ledges; //paths同士を結ぶライトエッジ
  
  //より浅い区間から追加される。つまりpaths[0].first = number[lca(u,v)];
  void buildPaths(int u,int v){
    if(depth[group[u]] < depth[group[v]]) swap(u,v);// 深い方のノードから処理する。
    int nu=number[u], nv=number[v];
    if(same(u,v)){ paths.push_back(P(min(nu,nv),max(nu,nv)));return;} 

    int gu = group[u];
    buildPaths(par[gu],v);

    paths.push_back(P(number[gu], number[u]));
    Ledges.push_back(P(number[par[gu]], number[gu]));
  }
  
  //lca(元の頂点番号,元の頂点番号) -> 元の頂点番号
  int lca(int u,int v){
    assert(ok && "Please Build");
    if(depth[group[u]] < depth[group[v]]) swap(u,v);
    if(same(u,v)) return depth[u] < depth[v]? u:v;
    return lca(par[group[u]],v);
  }
  
  //getPath(元の頂点番号,元の頂点番号) -> 振り直した頂点番号
  pair<vector<P>, vector<P> > getPath(int u,int v){
    assert(ok && "Please Build");
    paths.clear();
    Ledges.clear();
    buildPaths(u,v);
    return make_pair(paths,Ledges);
  }

  /*(元の頂点番号,元の頂点番号)*/ 
  bool same(int a,int b){return group[a] == group[b];}
};


signed main(){
  
  int n;
  cin>>n;

  HLD hld(n);
  for(int i=0;i<n;i++){
    int k;
    cin>>k;
    for(int j=0;j<k;j++) {
      int c;
      cin>>c;
      hld.add_edge(i, c);
    }
  }
  hld.build();
  
  /*
  RSAQ A(n);

  auto query0=[&](int u,int w){
    auto path = hld.getPath(0,u).first;
    path[0].first++;
    for(auto p:path){
      int l = p.first;
      int r = p.second;
      A.add(l,r+1,w);
    }
  };

  auto query1=[&](int u){
    auto path = hld.getPath(0,u).first;
    path[0].first++;
    int res = 0;
    for(auto p:path){
      int l = p.first;
      int r = p.second;
      res += A.sum(l,r+1);
    }
    return res;
  };
  
  int q;
  cin>>q;
  while(q--){
    int cmd;
    cin>>cmd;

    if(cmd == 0){
      int v,w;
      cin>>v>>w;
      query0(v, w);
    }
    if(cmd == 1){
      int u;
      cin>>u;
      int ans = query1(u);
      cout<<ans<<endl;
    }

  }
  */
  return 0;
}
