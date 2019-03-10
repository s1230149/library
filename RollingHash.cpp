#include <bits/stdc++.h>
using namespace std;

/*
modをしっかりとっているので定数倍遅い。
unsigned long longにしてmodを取らないようにすると10倍近く早くなる。
*/

// 10000019, 10000079, 10000103, 10000121, 10000139
// 1000000007, 1000000009, 1000000021, 1000000033, 1000000087

class RollingHash{
public:
  typedef long long ll;
  ll B, mod;  //B: ハッシュ基数
  int n;
  string s;
  vector<ll> hash;
  vector<ll> k;

  RollingHash():n(-1){};
  RollingHash(string s,ll B = 1777771,ll mod = 1e9 + 7):
    B(B),mod(mod),n(s.size()),s(s),hash(n+1),k(n+1)
  {
    for(int i=0;i<n;i++) hash[i+1] = (hash[i] * B % mod + s[i]) % mod;
    k[0] = 1;
    for(int i=1;i<=n;i++) k[i] = (k[i-1] * B) % mod;
  }

  ll get(int l,int r)const{ //[l, r)
    assert(0<=l && r<=n && l<=r);
    return (mod + hash[r] - hash[l] * k[r-l] % mod) % mod;
  }
  
  //hash[a]とB.hash[b]からみて何文字一致してるか。
  int count(int a, const RollingHash &B, int b){
    int L = 0, R = min( n - a, B.n - b ) + 1;
    while( L + 1 < R ){
      int M = ( L + R ) / 2;
      get( a, a + M ) != B.get( b, b + M ) ? R = M : L = M;
    }
    return L;
  }
};

int main(){
  srand((unsigned)time(NULL));
  
  while(1){
    int n = rand() % 10;
    int m = rand() % 10;
    
    string s,t;
    for(int i=0;i<n;i++) s += string(rand()%10,'a' + rand()%4);
    for(int i=0;i<m;i++) t += string(rand()%10,'a' + rand()%4);
    n = s.size();
    m = t.size();
    
    auto count = [&](int i,int j){
      int k = 0;
      for(k=0;i + k < n && j + k < m;k++) if(s[i + k] != t[j + k]) return k;
      return k;
    };

    cout<<"s="<<s<<endl;
    cout<<"t="<<t<<endl;

    RollingHash A(s),B(t);
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++){
        assert(count(i,j) == A.count(i,B,j));
      }
  }

    return 0;
}
