#include <bits/stdc++.h>
using namespace std;

class EulerTour{
public:
  int V;                     //ノード数
  int root;                  //根の頂点番号
  vector<vector<int> > G;    //Grapth
  vector<int> L,R;           //[L,R]
  bool ok;
  EulerTour():V(-1),ok(0){};
  EulerTour(int V,int root):V(V),root(root),G(V),L(V),R(V),ok(0){}

  void add_edge(int a,int b){
    assert(a >= 0 && b >= 0);
    assert(a < V && b < V);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  void build(){
    ok = 1;
    int cnt = 0;
    function<void(int,int)> dfs = [&](int pos,int pre){
      L[pos] = cnt;
      for(int to:G[pos]) if(to != pre) cnt++, dfs(to, pos);
      R[pos] = cnt;
    };
    dfs(root,-1);
  }

  //オイラーツアー上のvの添字を返す。
  int getIdx(int v){assert(ok && v < V); return L[v];}

  //vを根とする部分木をvを含み[l, r]の区間で返す。
  pair<int, int> get(int v){assert(ok && v < V); return make_pair(L[v],R[v]);}
};




/********************************************/
/*        ここから下は動作確認用のコード        */
/********************************************/
class RSAQ{
public:
  typedef long long ll;
  //マージ可能な主データ型
  struct D{
    ll value;
    D():value(0){} /*適切な値にする!!!!!!*/
    D(ll value):value(value){}
    bool operator < (D a)const {return value < a.value;}
  };

  //遅延用の型
  struct T{
    int type; //0 - empty   , 1 - update
    ll value;
    T():type(0),value(0){}
    T(int type,ll value):type(type),value(value){}
  };


  int n, n_;
  vector<D> dat;
  vector<T> td;
  D returnD = D(0); // 範囲外の時に返す値。

  RSAQ(){n=-1;}
  RSAQ(int n_):n_(n_){
    n=1;
    while(n < n_) n *= 2;
    td.resize(2*n-1,T());
    dat.resize(2*n-1,D());
  }

  inline D merge(const D a,const D b)const{return a.value + b.value;}

  void delay(int k,int len){
    if(td[k].type==0) return;
    ll type = td[k].type;
    ll v = td[k].value;
    td[k].type = 0;
    td[k].value = 0;
    len /= 2;
    {
      int l = k*2+1;
      dat[l].value += v * len;
      td[l].type = type;
      td[l].value += v;
    }
    {
      int r = k*2+2;
      dat[r].value += v * len;
      td[r].type = type;
      td[r].value += v;
    }
  }

  D write(int k, D x, int len){
    dat[k].value += x.value * len;
    td[k].type = 1;
    td[k].value += x.value;
    return dat[k];
  }

  D dfs(int a, int b, D x, bool flag, int k, int l, int r){
    if(r <= a||b <= l) return flag? dat[k]:returnD;
    if(a <= l && r <= b) return flag? write(k, x, r - l):dat[k];
    delay(k, r - l);
    D vl = dfs(a, b, x, flag, k*2+1, l, (l+r)/2);
    D vr = dfs(a, b, x, flag, k*2+2, (l+r)/2, r);
    return flag? (dat[k] = merge(vl, vr)):merge(vl, vr);
  }

  //[l,r)の値にx加算
  void add(int l,int r,ll x){
    assert(l <= r);
    assert(0 <= l && l <= n);
    assert(0 <= r && r <= n);
    dfs(l, r, D(x), true, 0, 0, n);
  }

  //[l,r)の合計値を得る
  ll get(int l,int r){
    assert(l <= r);
    assert(0 <= l && l <= n);
    assert(0 <= r && r <= n);
    D res = dfs(l, r, D(), false, 0, 0, n);
    return res.value;
  }
};

void AOJ_GRL_5_D(){
  int n;
  cin>>n;
  EulerTour et(n, 0);
  for(int i=0;i<n;i++){
    int k;
    cin>>k;
    for(int j=0;j<k;j++){
      int c;
      cin>>c;
      et.add_edge(i, c);
    }
  }
  et.build();
  RSAQ seg(n);

  int q;
  cin>>q;
  while(q--){
    int cmd;
    cin>>cmd;
    if(cmd == 0){
      int v, w;
      cin>>v>>w;
      int l, r; tie(l, r) = et.get(v);
      seg.add(l, r+1, w);
    }
    if(cmd == 1){
      int u;
      cin>>u;
      int idx = et.getIdx(u);
      int ans = seg.get(idx, idx+1);
      cout<<ans<<endl;
    }
  }
}

void abc138_d(){
  int N, Q;
  cin>>N>>Q;

  EulerTour et(N, 0);
  for(int i=0;i<N-1;i++){
    int a, b;
    cin>>a>>b; a--, b--;
    et.add_edge(a, b);
  }
  et.build();

  RSAQ seg(N);
  while(Q--){
    int p, x;
    cin>>p>>x; p--;
    int l, r; tie(l, r) = et.get(p);
    seg.add(l, r+1, x);
  }

  for(int i=0;i<N;i++){
    int idx = et.getIdx(i);
    long long ans = seg.get(idx, idx+1);
    if(i) cout<<" ";
    cout<<ans;
  }
  cout<<endl;
}

int main(){
  //AOJ_GRL_5_D();
  abc138_d();
  return 0;
}
