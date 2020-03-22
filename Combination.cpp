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

  function<ll(ll, ll)> mod_pow = [&](ll x, ll y){
      ll res = 1;
      while(y){
        if(y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
      }
      return res;
  };

  function<ll(ll)> inv_ = [&](ll x){return mod_pow(x, mod - 2);};

  function<ll(ll,ll)> nCr = [&](ll n,ll r){
    if( n < r ) return 0LL;
    if( n < 0 || r < 0) return 0LL;
    if(n == r || r == 0) return 1LL;
    assert(fac[r] > 0);
    assert(fac[n - r] > 0);
    return fac[n] * (finv[r] * finv[n-r] % mod) % mod;
  };

  function<ll(ll,ll)> nCr_ = [&](ll n, ll r){ //O(r + log(mod))
    if( n < r ) return 0LL;
    if( n < 0 || r < 0) return 0LL;
    if(n == r || r == 0) return 1LL;
    ll N = 1, K = 1;
    for(int i=0;i<r;i++){
      N = N * ((n - i) % mod) % mod;
      K = K * ((r - i) % mod) % mod;
    }
    assert(K > 0);
    return N * inv_(K) % mod;
  };

  function<ll(ll, ll)> nPr=[&](ll n, ll r){
    if(n < r) return 0LL;
    if(n < 0 || r < 0) return 0LL;
    return fac[n] * finv[n - r] % mod;
  };

  //Combination Comb;
  //auto nCr = Comb.nCr;
  //auto nCr_ = Comb.nCr_;
  //auto nPr = Comb.nPr;
  //auto fac = Comb.fac;
  //auto inv = Comb.inv
  //auto inv_ = Comb.inv_
  //auto finv = Comb.finv
};


void test(){
  vector<long long> mods({2, 3, 5, 7, 1031, 10007, 113063, 171403, 15485863, 1000000007});
  while(1){
    long long mod = mods[rand()%mods.size()];
    int n = rand()%1000000;
    int r = rand()%1000000;
    Combination Comb(1000010, mod);
    auto nCr = Comb.nCr;
    auto nCr_ = Comb.nCr_;
    int a = nCr(n, r);
    int b = nCr_(n, r);
    cout<<"mod="<<mod<<" a="<<a<<" b="<<b<<endl;
    assert(a == b);

  }
}
signed main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int mod = 1e9 + 7;
  auto nCr = (new Combination(1e7, mod))->nCr;
  cout<<nCr(5, 2)<<endl;;

  Combination COM;
  cout<<COM.nCr(5, 2)<<endl;

  test();
  return 0;
}
