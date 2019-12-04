#include <bits/stdc++.h>
using namespace std;

/*Range Sum Update Query*/

template<typename D, int useAssert = 1>
class RSUQ{
public :
  struct T{ //遅延データ
    int type; //0 - empty, 1 - update
    D value;
    T():type(0){}
    T(int type, D value):type(type), value(value){}
  };

  int n, n_;
  vector<D> dat;
  vector<T> td;

  RSUQ(){n=-1;}
  RSUQ(int n_):n_(n_){
    n=1;
    while(n<n_) n *= 2;
    td.resize(2*n-1, T());
    dat.resize(2*n-1, 0);
  }

  //目的データのマージ
  inline D mergeD(D l, D r){return l + r;}

  //遅延データのマージ
  inline T mergeT(const T &from, const T &to){
    if(to.type == 0) return from;
    return to;
  }

  //目的データに遅延データを反映
  inline void apply(D &a, const T &b, int len){
    if(b.type == 0) return;
    a = b.value * len; //update
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

  //[l,r)の総和を得る　get(l,r);
  D get(int l,int r){
    if(useAssert) assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    return dfs(l, r, T(), 0 , 0 ,n);
  }
};


signed main(){
  int n,q;
  cin>>n>>q;

  RSUQ<int, 0> rsuq(n);

  while(q--){
    int cmd;
    cin>>cmd;
    if(cmd == 0){
      int s,t,x;
      cin>>s>>t>>x;
      rsuq.update(s,t+1,x);
    }

    if(cmd == 1){
      int s,t;
      cin>>s>>t;
      cout<<rsuq.get(s,t+1)<<endl;
    }
  }

  return 0;
}
