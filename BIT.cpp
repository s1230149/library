#include <bits/stdc++.h>
using namespace std;

class BIT{
public:
  typedef long long ll;
  ll n;
  vector<ll> bit;
  BIT():n(-1){};
  BIT(ll n_){
    n=1;
    while(n < n_+2) n *= 2;
    bit.resize(n+1, 0);
  }
  
  //[0, i]までの総和を得る
  ll sum(ll i){
    assert( i >= 0 && i <= n );
    i++;
    
    ll s=0;
    while(i>0){
      s = (s + bit[i]);
      i -= i & -i;
    }
    return s;
  }

  //i番目の要素にx加算(0 オリジン)
  void add(ll i,ll x){
    assert( i >= 0 && i <= n );
    i+=2;
    
    while(i <= n){
      bit[i] = (bit[i] + x);
      i += i & -i;
    }
  }
  
  ll sum(int l,int r){ //[l, r) 0オリジン
    assert(l <= r);
    assert( 0 <= l && l <= n);
    assert( 0 <= r && r <= n);
    return sum(r) - sum(l);
  }
};


int main(){
  int n,q;
  cin>>n>>q;
  
  BIT bit(n);
  while(q--){
    int com, x, y;
    cin>>com >> x >> y;
    if(com == 0) bit.add(x-1 , y);
    if(com == 1) cout<<bit.sum(x-1,y)<<endl;
  }

  
}
