#include <bits/stdc++.h>
using namespace std;

/*Range Add Min(Max) Query*/
/*区間加算、区間Min,区間Max*/

class RSUQ{
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
  
  RSUQ(){n=-1;}
  RSUQ(int n_):n_(n_){
    n=1;
    while(n < n_) n *= 2;
    td.resize(2*n-1,T());
    dat.resize(2*n-1,D());
  }
  
  inline D merge(D a,D b){return a.value + b.value;}
  
  void delay(int k,int len){
    if(td[k].type==0) return;
    ll type = td[k].type;
    ll v = td[k].value;
    td[k].type = 0;
    td[k].value = 0;
    
    len /= 2;
    {
      int l = k*2+1;
      dat[l].value = v * len;
      td[l].type = type;
      td[l].value = v;
    }
    {
      int r = k*2+2;
      dat[r].value = v * len;
      td[r].type = type;
      td[r].value = v;
    }
  }

  D write(int k, D x, int len){
    dat[k].value = x.value * len;
    td[k].type = 1;
    td[k].value = x.value;
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

  //[l,r)の値をx変更　query(l,r,x)
  void update(int l,int r,ll x){
    assert(l <= r);
    assert(0 <= l && l <= n);
    assert(0 <= r && r <= n);
    dfs(l, r, D(x), true, 0, 0, n);
  }
  
  //[l,r)の合計値を得る　find(a,b);
  ll find(int l,int r){
    assert(l <= r);
    assert(0 <= l && l <= n);
    assert(0 <= r && r <= n);
    D res = dfs(l, r, D(), false, 0, 0, n);
    return res.value;
  }
};


signed main(){
  int n,q;
  cin>>n>>q;
  
  RSUQ rsuq(n);

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
      cout<<rsuq.find(s,t+1)<<endl;
    }
  }
  
  return 0;
}
