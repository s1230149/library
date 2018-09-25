#include <bits/stdc++.h>
#include "RollingHash.cpp"
using namespace std;


//多分使うことはない。
class MultiCompareRollingHash{
public:
  typedef long long ll;
  int n = 5;
  vector<RollingHash> A;
  vector<ll> B = {10000019, 10000079, 10000103, 10000121, 10000139};
  vector<ll> mod = {1000000007, 1000000009, 1000000021, 1000000033, 1000000087};
  
  MultiCompareRollingHash(){}
  MultiCompareRollingHash(string s){
    A.resize(n);
    assert(n <= (int)mod.size());
    assert(n <= (int)B.size());
    assert(B.size() == mod.size());
    for(int i=0;i<n;i++) A[i] = RollingHash(s, B[i], mod[i]);
  }

  ll get(int i,int l,int r){return A[i].get(l, r);}
  
  vector<ll> get(int l,int r){
    vector<ll> res;
    for(int i=0;i<n;i++) res.push_back(get(i, l, r));
    return res;
  }

  int eq(int l1,int r1,int l2,int r2){
    for(int i=0;i<n;i++) if(get(i, l1, r1) != get(i, l2, r2)) return 0;
    return 1;
  }
};
