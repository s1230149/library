#include <bits/stdc++.h>
using namespace std;
/*
  toMaxQuery == 0 -> 区間最小クエリ
  toMinQuery == 1 -> 区間最大クエリ
  update(l, r, x): [l, r)の区間をxに更新
  ifupdate(l, r, x): [l, r)の区間の値をxの方が(小さい/大きい)ければ更新
  get(l, r): [l, r)の区間の値の(最大/最小)を取得
*/

template<typename D, int toMaxQuery, int useAssert = 1>
class RMQ{
public :
  struct T{ //遅延データ
    int type; //0 - empty, 1 - update, 2 - ifUpdate
    D value;
    T():type(0){}
    T(int type, D value):type(type), value(value){}
  };

  int n, n_;
  D initValue;        //datの初期値と範囲外の時に返す値
  vector<D> dat;
  vector<T> td;
  int toMax;          //0 -> RangeMin 1->RangeMax;

  RMQ(){n=-1;}
  RMQ(int n_, D initValue):n_(n_), initValue(initValue){
    n=1;
    while(n<n_)n *= 2;
    td.resize(2*n-1, T());
    dat.resize(2*n-1, initValue);
  }

  //目的データのマージ
  inline D mergeD(D l, D r){return toMaxQuery? max(l, r):min(l, r);}

  //遅延データのマージ
  inline T mergeT(const T &from,const T &to){
    if(to.type == 0) return from;
    if(from.type == 0) return to; //from-empty
    if(to.type == 1) return to; //to-update;
    if(to.type == 2) return T(from.type, mergeD(from.value, to.value)); //to-ifupdate
    if(useAssert) assert(0);
    return T();
  }

  //目的データに遅延データを反映
  inline void apply(D &a, const T &b){
    if(b.type == 0) return;
    if(b.type == 1) a = b.value; //update
    else a = mergeD(a, b.value); // if-update
  }

  D dfs(int a, int b,const T x, int k, int l, int r){
    if(r <= a || b <= l) return x.type == 0? initValue : dat[k];
    if(a <= l && r <= b){
      td[k] = mergeT(td[k], x);
      apply(dat[k], x);
      return dat[k];
    }
    int kl = k * 2 + 1, kr = k * 2 + 2;
    { //遅延を子に反映
      td[kl] = mergeT(td[kl], td[k]);
      td[kr] = mergeT(td[kr], td[k]);
      apply(dat[kl], td[k]);
      apply(dat[kr], td[k]);
      td[k] = T();
    }
    D vl = dfs(a, b, x, kl, l, (l+r)/2);
    D vr = dfs(a, b, x, kr, (l+r)/2, r);
    return x.type == 0? mergeD(vl,vr) : (dat[k] = mergeD(vl, vr));
  }

  //[l,r)の値をxに変更　update(l,r,x)
  void update(int l,int r, D x){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    dfs(l, r,  T(1, x), 0, 0, n);
  }

  //[l,r)の値をもしもxの方が小さければ変更　ifupdate(l,r,x)
  //toMaxのときは[l,r)の値をもしもxの方が大きければ変更　ifupdate(l,r,x)
  void ifupdate(int l,int r, D x){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    dfs(l, r,  T(2, x), 0, 0, n);
  }

  //[l,r)の最小値を得る　get(l,r);
  D get(int l,int r){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    return dfs(l, r, T(0, initValue), 0 , 0 ,n);
  }
};

//ABC_140_E
//ABC_146_F
//ここから下は動作確認用
class Rand{
public:
  typedef long long ll;
  random_device rnd;//毎回異なる乱数
  mt19937_64 mt; //unsigned 64bitメルセンヌ_ツイスタ [0, 2^66]
  //mt19937 mt; //unsigned 32bitメルセンヌ_ツイスタ [0, 2^32]

  Rand():mt(rnd()){}
  //Rand():mt((unsigned int)time(NULL)){};

  ll get(){return mt()>>1;} //[0, (2^63)-1]
  ll get(ll l,ll r){ //[l, r]
    assert(l <= r);
    return l + get() % (r - l + 1);
  }
};

void test(){
  Rand rnd;
  const int toMax = rnd.get(0, 1);
  const int INF = toMax? -(1e9):1e9;
  const int N = rnd.get(1, 10000);
  vector<int> A(N, INF);
  RMQ<int, 0> B_min(N, INF);
  RMQ<int, 1> B_max(N, INF);
  auto update=[&](int l, int r, int x){for(int i=l;i<r;i++) A[i] = x;};
  auto ifupdate=[&](int l, int r, int x){for(int i=l;i<r;i++) A[i] = toMax? max(A[i], x):min(A[i], x);};
  auto get=[&](int l, int r){
    if(l == r) return INF;
    int res = A[l];
    for(int i=l;i<r;i++) res = toMax? max(res, A[i]):min(res, A[i]);
    return res;
  };
  int M = N * 100;
  cout<<"start: N="<<N<<" toMax="<<toMax<<endl;
  while(M--){
    int type = rnd.get(0, 2);
    int l = rnd.get(0, N-1);
    int r = rnd.get(l, N);
    int x = rnd.get(-1e8, 1e8);
    if(type == 0){
      int a = get(l, r);
      int b = toMax? B_max.get(l, r):B_min.get(l, r);
      assert(a == b);
    }
    if(type == 1) update(l, r, x), B_max.update(l, r, x), B_min.update(l, r, x);
    if(type == 2) ifupdate(l, r, x), B_max.ifupdate(l, r, x), B_min.ifupdate(l, r, x);
  }
}

signed main(){
  while(1) test();
  return 0;
}
