#include <bits/stdc++.h>
#ifdef LOCAL_DEBUG
#define DEBUG 1
#define CERR if(DEBUG) cerr
#define MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define pr(...) CERR<<MACRO(__VA_ARGS__,pr10,pr9,pr8,pr7,pr6,pr5,pr4,pr3,pr2,pr1)(__VA_ARGS__)<<endl
#define pr1(a) (#a)<<"="<<(a)<<" "
#define pr2(a,b) pr1(a)<<pr1(b)
#define pr3(a,b,c) pr1(a)<<pr2(b,c)
#define pr4(a,b,c,d) pr1(a)<<pr3(b,c,d)
#define pr5(a,b,c,d,e) pr1(a)<<pr4(b,c,d,e)
#define pr6(a,b,c,d,e,f) pr1(a)<<pr5(b,c,d,e,f)
#define pr7(a,b,c,d,e,f,g) pr1(a)<<pr6(b,c,d,e,f,g)
#define pr8(a,b,c,d,e,f,g,h) pr1(a)<<pr7(b,c,d,e,f,g,h)
#define pr9(a,b,c,d,e,f,g,h,i) pr1(a)<<pr8(b,c,d,e,f,g,h,i)
#define pr10(a,b,c,d,e,f,g,h,i,j) pr1(a)<<pr9(b,c,d,e,f,g,h,i,j)
#define prArr(a){CERR<<(#a)<<"={";int i=0;for(auto t:(a))CERR<<(i++?", ":"")<<t;CERR<<"}"<<endl;}
#else
#define DEBUG 0
#define pr(...)
#define prArr(a)
#endif
using namespace std;
using Int = long long;
using _int = int;
using ll = long long;
using Double = long double;
const Int INF = (1LL<<60)+1e9; // ~ 1.15 * 1e18
const Int mod = (1e9)+7;
const Double EPS = 1e-8;
const Double PI = 6.0 * asin((Double)0.5);
using P = pair<Int,Int>;
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}
template<class T1, class T2> ostream& operator<<(ostream& o,pair<T1,T2> p){return o<<"("<<p.first<<","<<p.second<<")";}
template<class T1, class T2, class T3> ostream& operator<<(ostream& o,tuple<T1,T2,T3> t){return o<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")";}
template<class T1, class T2> istream& operator>>(istream& i,pair<T1,T2> &p){return i>>p.first>>p.second;}
template<class T> ostream& operator<<(ostream& o,vector<T> a){Int i=0;for(T t:a)o<<(i++?" ":"")<<t;return o;}
template<class T> istream& operator>>(istream& i,vector<T> &a){for(T &t:a)i>>t;return i;}
//INSERT ABOVE HERE

template<typename D, int useAssert = 1>
class RSQ{
public :
  struct T{ //遅延データ
    int type; //0 - empty, 1 - add, 2 - update
    D value;
    T():type(0){}
    T(int type, D value):type(type), value(value){}
  };

  int n, n_;
  vector<D> dat;
  vector<T> td;

  RSQ(){n=-1;}
  RSQ(int n_):n_(n_){
    n=1;
    while(n<n_) n *= 2;
    td.resize(2*n-1, T());
    dat.resize(2*n-1, 0);
  }

  //目的データのマージ
  inline D mergeD(D l, D r){return l + r;}

  //遅延データのマージ
  inline T mergeT(const T &from, const T &to){
    if(to.type == 0) return from; //to->empty
    if(from.type == 0) return to; //from->empty
    if(to.type == 1) return to;   //to->update
    return T(from.type, from.value + to.value);
  }

  //目的データに遅延データを反映
  inline void apply(D &a, const T &b, int len){
    if(b.type == 0) return;             //empty
    if(b.type == 1) a = b.value * len;  //update
    else a += b.value * len;                 //add
  }

  D dfs(int a, int b,const T x, int k, int l, int r){
    if(r <= a || b <= l) return x.type == 0? 0 : dat[k];
    if(a <= l && r <= b){
      td[k] = mergeT(td[k], x);
      apply(dat[k], x, r - l);
      return dat[k];
    }
    int kl = k * 2 + 1, kr = k * 2 + 2;
    { //遅延を子に反映
      td[kl] = mergeT(td[kl], td[k]);
      td[kr] = mergeT(td[kr], td[k]);
      apply(dat[kl], td[k], (r - l)/2);
      apply(dat[kr], td[k], (r - l)/2);
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

  //[l,r)の値をxに変更　update(l,r,x)
  void add(int l,int r, D x){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    dfs(l, r,  T(2, x), 0, 0, n);
  }

  //[l,r)の総和を得る　get(l,r);
  D get(int l,int r){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    return dfs(l, r, T(), 0 , 0 ,n);
  }
};


class Rand{
public:
  typedef long long ll;
  random_device rnd;//毎回異なる乱数
  mt19937_64 mt; //unsigned 64bitメルセンヌ_ツイスタ [0, 2^66]

  Rand():mt(rnd()){}

  ll get(){return mt()>>1;} //[0, (2^63)-1]
  ll get(ll l,ll r){ //[l, r]
    assert(l <= r);
    return l + get() % (r - l + 1);
  }
};

void test(){
  Rand rnd;
  const int N = rnd.get(1, 10000);
  vector<int> A(N);
  RSQ<int> B(N);
  auto update=[&](int l, int r, int x){for(int i=l;i<r;i++) A[i] = x;};
  auto add=[&](int l, int r, int x){for(int i=l;i<r;i++) A[i] += x;};
  auto get=[&](int l, int r){
    if(l == r) return 0;
    int res = 0;
    for(int i=l;i<r;i++) res += A[i];
    return res;
  };

  int M = N * 100;
  cout<<"start: N="<<N<<endl;
  while(M--){
    int type = rnd.get(0, 2);
    int l = rnd.get(0, N-1);
    int r = rnd.get(l, N);
    int x = rnd.get(-1e8, 1e8);
    if(type == 0){
      int a = get(l, r);
      int b = B.get(l, r);
      assert(a == b);
    }
    if(type == 1) update(l, r, x), B.update(l, r, x);
    if(type == 2) add(l, r, x), B.add(l, r, x);
  }
}
signed main(){
  while(1) test();
  return 0;
}
