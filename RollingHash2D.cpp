#include <bits/stdc++.h>
#include "RollingHash.cpp"
using namespace std;
//誰か作って

// 10000019, 10000079, 10000103, 10000121, 10000139
// 1000000007, 1000000009, 1000000021, 1000000033, 1000000087

class RollingHash2D{
public:
  typedef long long ll;
  ll B, mod; //B: ハッシュ基数
  int h, w, r, c;
  vector<string> A;
  vector<RollingHash> hash;
  vector<ll> k;
  
  RollingHash2D():h(-1),w(-1){};
  RollingHash2D(vector<string> A,int r,int c, ll B = 2e7-1,ll mod = 1e9 + 9):
    B(B), mod(mod), h(A.size()), w(A[0].size()), r(r), c(c), A(A), hash(h+1), k(h+1){
    
    for(int i=0;i<h;i++) hash[i] = RollingHash(A[i]);
    k[0] = 1;
    for(int i=0;i<h;i++) k[i+1] = k[i] * B % mod;
    
    for(int i=0;i<w;i++)
      for(int j=0;j<w;j++){

      }
    
  }

  ll get(){

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
