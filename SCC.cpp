#include <bits/stdc++.h>
using namespace std;

class SCC{
public:
  int V,K;                      //頂点数, scc後の頂点数
  vector<vector<int> > G;       //グラフの隣接リストの表現
  vector<vector<int> >rG;       //辺の向きを逆にしたグラフ
  vector<vector<int> >DAG;      //scc後のグラフの隣接リストの表現
  vector<vector<int> >rDAG;     //scc後の辺の向きを逆にしたグラフ
  vector<int> vs;               //帰りがけ順の並び
  vector<int>used;              //すでに調べたか
  vector<int> cmp;              //属する強連結成分のトポロジカル順
  vector<vector<int> > member;  //scc後の同じグループのノードの集合
  int ok;                       //buildされているか。
  SCC(){V = K = -1;}
  SCC(int V):V(V),G(V),rG(V),used(V,0),cmp(V),ok(0){}
  
  void add_edge(int from,int to){
    assert(from<V && to<V);
    G[from].push_back(to);
    rG[to].push_back(from);
  }

  void dfs(int v){
    used[v]=true;
    for(int nx:G[v]) if(!used[nx]) dfs(nx);
    vs.push_back(v);
  }

  void rdfs(int v,int k){
    used[v]=true;
    cmp[v]=k;
    for(int nx:rG[v]) if(!used[nx]) rdfs(nx,k);
  }

  int build(bool makeDAG = 0){ //DAGのグラフも作りたかったらmakeDAGを1にする
    ok = true;
    used.clear(); used.resize(V,0);
    vs.clear();
    for(int v=0;v<V;v++) if(!used[v]) dfs(v);
    
    used.clear(); used.resize(V,0);
    int &k= K = 0;
    for(int i=vs.size()-1;i>=0;i--)if(!used[vs[i]]) rdfs(vs[i],k++);

    member.clear();
    member.resize(k);
    for(int i=0;i<V;i++) member[cmp[i]].push_back(i);
    
    if(makeDAG) DAG = getDAG(G), rDAG = getDAG(rG); //O(ElogE)
    
    return k;
  }

  bool same(int u, int v){assert(ok);return cmp[u] == cmp[v];}

private:
  vector<vector<int> > getDAG(const vector<vector<int> > &G){
    assert(K>=0);
    vector<vector<int> >res(K);
    for(int from=0;from<V;from++)
      for(int to:G[from]) if(cmp[from]!=cmp[to]) res[cmp[from]].push_back(cmp[to]);
    
    for(int i=0;i<K;i++){
      sort(res[i].begin(),res[i].end());
      res[i].erase(unique(res[i].begin(),res[i].end()),res[i].end());
    }
    return res;
  }
};
