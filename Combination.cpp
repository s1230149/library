#include <bits/stdc++.h>
using namespace std;

/* 
   組み合わせ. 
   前処理O(n)
   クエリO(1)
*/

class Combination{
public:
  typedef long long ll;
  ll N;
  ll mod;
  vector<ll> fac;
  vector<ll> finv;
  vector<ll> inv;
  
  
  Combination(ll N = 1e6,ll mod = 1e9 + 7): N(N), mod(mod), fac(N+1), finv(N+1), inv(N+1){
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for(int i = 2; i <= N; i++){
      fac[i] = fac[i-1] * i % mod;
      inv[i] = mod - inv[mod%i] * (mod / i) % mod;
      finv[i] = finv[i-1] * inv[i] % mod;
    }
  }

  function<ll(ll,ll)> get = [&](ll n,ll r){
    if( n < r ) return 0LL;
    if( n < 0 || r < 0) return 0LL;
    return fac[n] * (finv[r] * finv[n-r] % mod) % mod;
  };
  //auto nCr = (new Combination())->get;
};


signed main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int mod = 1e9 + 7;
  auto nCr = (new Combination(1e7, mod))->get;
  cout<<nCr(5, 2)<<endl;;

  Combination COM;
  cout<<COM.get(5, 2)<<endl;
  return 0;
}
