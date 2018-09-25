#include <bits/stdc++.h>
using namespace std;

//木の直径
class DiameterOfTree{
public:
  typedef pair<int,int> P;
  int V;
  vector<vector<P> > G; //(to, cost)
  vector<int> nodeCost; //ノードに重みがある場合
  int start, end, length;
  int ok;
  DiameterOfTree():V(-1){}
  DiameterOfTree(int V):V(V),G(V),nodeCost(V, 0),ok(false){};

  void add_edge(int a,int b,int c = 1){
    ok = false;
    assert(a < V && b < V);
    assert(a >= 0 && b >= 0);
    G[a].push_back( P(b, c) );
    G[b].push_back( P(a, c) );
  }
  
  //O(V + E);
  void build(int start=0){
    ok = true;
    assert(start < V);
    dfs(start);
    dfs(end);
  }
  
  void dfs(int pos,int pre = -1,int len = 0){
    if(pre == -1) start = pos, length = -1;
    len += nodeCost[pos];
    if(len > length) length = len, end = pos;
    for(P p:G[pos]) if(p.first != pre) dfs(p.first, pos, len+p.second);
  }

  //s-t間のパスを取得 : O(V + E)
  vector<int> getPath(int s,int t){
    assert(0 <= s && s < V);
    assert(0 <= t && t < V);
    
    vector<int> res;
    function<int(int,int)> dfs = [&](int pos,int pre){
      if(pos == s) {res.push_back(pos); return 1;}
      for(P p:G[pos]){
        int to = p.first;
        if(to != pre && dfs(to, pos)){res.push_back(pos); return 1;}
      }
      return 0;
    };

    dfs(t, -1); //{s, . . .,t}の順で入っている
    assert(res[0] == s && res.back() == t);
    return res;
  }
};

signed main(){
  int n;
  cin>>n;
  DiameterOfTree A(n);
  for(int i=0;i<n-1;i++){
    int a,b,c;
    cin>>a>>b>>c;
    A.add_edge(a,b,c);
  }

  A.build();
  int ans = A.length;
  cout<<ans<<endl;
  return 0;
}
