#include <bits/stdc++.h>
using namespace std;

class TSort{
public:
  int V;
  vector<unordered_set<int> > in,out;
  vector<int> tp;
  TSort():V(0){}
  TSort(int V):V(V),in(V),out(V){}
  
  void add_edge(int from,int to){
    assert(from >= 0 && to >= 0);
    assert(from < V && to < V);
    out[from].insert(to);
    in[to].insert(from);
  }

  vector<int> dfs(){
    vector<int> visited(V,0);
    
    function<void(int)> dfs = [&](int pos){
      if(visited[pos]++) return;
      for(int nx:out[pos]) dfs(nx);
      tp.push_back(pos);
    };
    
    tp.clear();
    for(int i=0;i<V;i++) dfs(i);
    reverse(tp.begin(),tp.end());
    return tp;
  }

  vector<int> bfs(){
    auto tmp = in;
    tp.clear();
    queue<int> Q;
    for(int i=0;i<V;i++)if(in[i].empty()) Q.push(i);
    
    while(!Q.empty()){
      int v = Q.front();Q.pop();
      tp.push_back(v);
      for(int nx:out[v]){
        if(in[nx].size() == 1) Q.push(nx);
        assert(in[nx].count(v));
        in[nx].erase(v);
      }     
    }
    for(int i=0;i<V;i++) if(!in.empty()) tp.clear(); // exist loop
    tmp = in;
    return tp;
  }
};


int main(){
  int n,m;
  cin>>n>>m;
  TSort A(n);
  
  for(int i=0,a,b;i<m;i++)cin>>a>>b,A.add_edge(a,b);
  
  A.dfs();
  for(int i=0;i<n;i++)cout<<A.tp[i]<<endl;
  return 0;
}
