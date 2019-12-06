#include <bits/stdc++.h>
#define int long long
using namespace std;

/*Range Add Min(Max) Query*/
/*区間加算、区間Min,区間Max*/

template<typename D, int toMaxQuery = 0, int useAssert = 1>
class RMAQ{
public :
  struct T{ //遅延データ
    int type; //0 - empty, 1 - add
    D value;
    T():type(0){}
    T(int type, D value):type(type), value(value){}
  };
  int n, n_;
  D returnD;        //範囲外の時に返す値。
  vector<D> dat;
  vector<T> td;
  RMAQ(){n=-1;}
  RMAQ(int n_, D returnD):n_(n_), returnD(returnD){
    n=1;
    while(n<n_)n*=2;
    td.resize(2*n-1, T());
    dat.resize(2*n-1, 0);
  }

  //目的データのマージ
  inline D mergeD(D l, D r){return toMaxQuery? max(l, r):min(l, r);}

  //遅延データのマージ
  inline T mergeT(const T &from,const T &to){
    if(from.type == 0) return to;
    if(to.type == 0) return from;
    return T(1, from.value + to.value);
  }

  //目的データに遅延データを反映
  inline void apply(D &a, const T &b){
    if(b.type == 0) return;
    a += b.value;
  }

  D dfs(int a, int b,const T x, int k, int l, int r){
    if(r <= a || b <= l) return x.type == 0? returnD:dat[k];
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

  //[l,r)の値にx加算　add(l,r,x)
  void add(int l,int r, D x){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    dfs(l, r,  T(1, x), 0, 0, n);
  }

  //[l,r)の最小値を得る　get(l,r);
  D get(int l,int r){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    return dfs(l, r, T(0, returnD), 0 , 0 ,n);
  }
};


signed main(){
  int n,q;
  cin>>n>>q;
  RMAQ <long long> rmaq(n, 1LL<<55);
  while(q--){
    int ord;
    cin>>ord;
    if(ord == 0){
      int s,t,x;
      cin>>s>>t>>x;
      rmaq.add(s,t+1,x);
    }
    if(ord == 1){
      int s,t;
      cin>>s>>t;
      cout<<rmaq.get(s,t+1)<<endl;
    }
  }

  return 0;
}
