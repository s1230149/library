#include <bits/stdc++.h>
#define int long long
using namespace std;

/*
  
  SparseTable
  
  値の途中変更は出来ない。最初の状態だけでQueryが欲しい時に有効。
  
  区間-(操作名) [option] 計算量(build)
  
  区間-(gcd) [0] O( N log(N) log(N) ) 
  区間-(min) [1] O( N log(N) )
  区間-(max) [2] O( N log(N) )
  
  [get]
  gcd -> O( log(N) )
  min -> O( 1 )
  max -> O( 1 )
  
  N : 要素数
  
  注意
  必ず全ての要素を初期化する。
  buildを忘れないようにする。
  
 */

class SparseTable{
public:
  typedef long long ll;
  
  int LOG = 20;
  ll N, option; // option : 0 -> gcd, 1 -> min, 2 -> max
  vector<vector<ll> > Array;
  vector<ll> Memo, Log;
  int ok = 0;
  SparseTable(){}
  
  SparseTable(ll N, ll option): 
    N(N), option(option), Array(LOG,vector<ll>(N)), Memo(N+1), Log(N+1){ 
    set<ll> pepi;
    for(ll i=0;i<LOG;i++){
      ll x = 1<<i;
      if( x <= N ) Log[x] = i;
      pepi.insert(x);
    }
    for(ll i=1;i<=N;i++) Memo[i] = *pepi.lower_bound( i + 1 ) >> 1;
  }
  
  // k番目の値をvalにする。 ( 0 origin )
  void update(ll k, ll val){assert(0<=k && k < N); ok = 0; Array[0][k] = val; }
  
  ll merge(ll A, ll B){
    if( option == 0 ) return __gcd( A, B );
    if( option == 1 ) return min( A, B );
    if( option == 2 ) return max( A, B );
    assert(0);
  }
  
  void build(){
    ok = 1;
    for(ll i=1;i<LOG;i++){
      ll len = 1<<i;
      for(ll j=0;j<N;j++){
        if( N <= j + len - 1 ) continue;
        Array[i][j] = merge( Array[i-1][j], Array[i-1][j+len/2] );
      }
    }
  }
  
  // [ l, r )の [optionを満たす値] を返す ( 0 origin )
  ll get(ll l, ll r){
    assert(ok);
    assert(l < r && 0 <= l && r <= N);
    ll k = Memo[r-l];
    return merge( Array[Log[k]][l], Array[Log[k]][r-k] );
  }
};

signed main(){
  
  int n;
  cin>>n;
  
  SparseTable A( n, 0 );
  
  for(int i=0;i<n;i++){
    int a;
    cin>>a;
    A.update( i, a );
  }
  
  A.build();
  
  while(1){
    int l, r;
    cin>>l>>r;
    cout<<A.get(l,r+1)<<endl;
  }
  
  return 0;
}
