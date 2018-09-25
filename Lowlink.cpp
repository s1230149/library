#include <bits/stdc++.h>
using namespace std;

//橋と関節点の判定:  構築:O(V + E) 判定:O(1)
class Lowlink{
public:
  int V;
  vector<vector<int> > G;
  vector<int> ord;           //ord[i] := ノードiに訪れた順番
  vector<int> low;           //low[i] := ノードiから訪れることができる最小のord[j]の値。
  vector<int> articulation;
  int ok;
  
  Lowlink():V(-1),ok(false){};
  Lowlink(int V):V(V),G(V),ok(false){};
  
  void add_edge(int a,int b){
    ok = false;
    assert(a < V && b < V);
    assert(a >=0 && b >= 0);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  void build(int root = 0){
    ok = true;
    ord.clear(); ord.resize(V,-1);
    low.clear(); low.resize(V,-1);
    articulation.clear(); articulation.resize(V,0); /*関節点用*/
    
    int cnt = 0;
    function<int(int,int)> dfs=[&](int pos,int pre){
      ord[pos] = low[pos] = cnt++;
      for(int to:G[pos]) {
        if(to == pre) continue; 
        if(ord[to] != -1) low[pos] = min(low[pos], ord[to]);
        else {
          low[pos] = min(low[pos], dfs(to, pos));
	  
	  /*関節点用*/
	  if(pos == root) articulation[pos]++;
	  else articulation[pos] |= ord[pos] <= low[to];
	  
	}
      }
      return low[pos];
    };
    
    dfs(root , -1);
    articulation[root] = articulation[root] >= 2; /*関節点用*/
  }

  int isBridge(int a,int b){
    assert(ok);
    assert(a < V && b < V);
    assert(a >= 0 && b >= 0);
    if(ord[a] > ord[b]) swap(a, b);
    return ord[a] < low[b];
  }
  
  int isArticulation(int a){
    assert(ok);
    assert(a >= 0 && a < V);
    return articulation[a];
  }
};


signed main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  auto verifyBridge=[&]{
    int V, E;
    cin>>V>>E;
  
    Lowlink A(V);
    for(int i=0;i<E;i++){
      int a,b;
      cin>>a>>b;
      A.add_edge(a,b);
    }
    
    A.build();
    
    typedef pair<int,int> P;
    vector<P> ans;
    for(int i=0;i<V;i++)
      for(int to:A.G[i]) if(i < to && A.isBridge(i, to)) ans.push_back(P(i, to));
    
    sort(ans.begin(),ans.end());
    for(auto a:ans) cout<<a.first<<" "<<a.second<<endl;
  };

  auto verifyArticulationPoint=[&]{
    int V, E;
    cin>>V>>E;
  
    Lowlink A(V);
    for(int i=0;i<E;i++){
      int a,b;
      cin>>a>>b;
      A.add_edge(a,b);
    }
    A.build();
    for(int i=0;i<V;i++) if(A.isArticulation(i)) cout<<i<<endl;

  };
  
  //verifyBridge();
  verifyArticulationPoint();
  return 0;
}
