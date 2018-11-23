#include <bits/stdc++.h>
using namespace std;

/*
  
  SparseTable
  構築: O(N * O(merge))
  クエリ: O(merge)
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
  SparseTable(vector<T> val, int option = 0): 
    N(val.size()), option(option), Memo(N+1), Log(N+1){
    LOG = 0;
    while(N >= (1<<LOG)) LOG++;
    Array = vector<vector<T> >(LOG,vector<T>(N));
    Array[0] = val;
    
    vector<int> num(LOG);
    for(int i=0;i<LOG;i++){
      int x = 1<<i;
      if( x <= N ) Log[x] = i;
      num[i] = x;
    }
    for(int i=1;i<=N;i++) Memo[i] = *lower_bound(num.begin(), num.end(), ( i + 1 ) >> 1);
    build();
  }
  
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

//https://code-festival-2014-qualb.contest.atcoder.jp/tasks/code_festival_qualB_d
void code_festival_qualB_d(){
  int n;
  cin>>n;
  vector<int> A(n);
  for(int i=0;i<n;i++) cin>>A[i];
  SparseTable <int> st(A, 1);
    
  auto solve=[&](int i,int f){
    int L = 0, R = n;
    while(L + 1 < R){
      int M = (L + R) / 2;
      int l = i, r = i + f * M;
      if(l > r) swap(l, r);
      0 <= l && r < n && st.get(l, r+1) <= A[i]? (L=M):(R=M);
    }
    return L;
  };

  for(int i=0;i<n;i++){
    int ans = solve(i, 1) + solve(i, -1);
    cout<<ans<<endl;
  }
}
			   

signed main(){
  code_festival_qualB_d();
  return 0;
}
