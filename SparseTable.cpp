#include <bits/stdc++.h>
#define int long long
using namespace std;

/*
  
  SparseTable
  
  値の途中変更は出来ない。最初の状態だけでQueryが欲しい時に有効。
  
  区間-(操作名) [option] 計算量(build)
  
  区間-(min) [0] O( N log(N) )
  区間-(max) [1] O( N log(N) )
  区間-(gcd) [2] O( N log(N) log(N) ) 
  
  [get]
  gcd -> O( log(N) )
  min -> O( 1 )
  max -> O( 1 )
  
  N : 要素数
  
  注意
  必ず全ての要素を初期化する。
  buildを忘れないようにする。
  
 */

template<typename T>
class SparseTable{
public:
  int LOG;
  int N, option; // option : 0 -> min, 1 -> max, 2 -> gcd
  vector<vector<T> > Array;
  vector<int> Memo, Log;
  int ok = 0;
  SparseTable(){}
  
  SparseTable(int N, int option): 
    N(N), option(option), Memo(N+1), Log(N+1){
    LOG = 0;
    while(N >= (1<<LOG)) LOG++;
    Array = vector<vector<T> >(LOG,vector<T>(N));
    
    vector<int> num(LOG);
    for(int i=0;i<LOG;i++){
      int x = 1<<i;
      if( x <= N ) Log[x] = i;
      num[i] = x;
    }
    for(int i=1;i<=N;i++) Memo[i] = *lower_bound(num.begin(), num.end(), ( i + 1 ) >> 1);
  }
  
  // k番目の値をvalにする。 ( 0 origin )
  void update(int k, T val){assert(0<=k && k < N); ok = 0; Array[0][k] = val; }
  
  inline T merge(const T &A,const T &B){
    if( option == 0 ) return min( A, B );
    if( option == 1 ) return max( A, B );
    //if( option == 2 ) return __gcd( A, B );
    assert(0);
  }
  
  void build(){
    ok = 1;
    for(int i=1;i<LOG;i++){
      int len = 1<<i;
      for(int j=0;j<N;j++){
        if( N <= j + len - 1 ) continue;
        Array[i][j] = merge( Array[i-1][j], Array[i-1][j+len/2] );
      }
    }
  }
  
  // [ l, r )の [optionを満たす値] を返す ( 0 origin )
  T get(int l, int r){
    assert(ok);
    assert(l < r && 0 <= l && r <= N);
    int k = Memo[r-l];
    return merge( Array[Log[k]][l], Array[Log[k]][r-k] );
  }
};

signed main(){
  
  int n;
  cin>>n;
  SparseTable<long long> A( n, 0 );
  
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
