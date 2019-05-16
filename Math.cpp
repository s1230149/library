#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

class Math{
public:
  typedef long long ll;
  typedef pair<int,int> P;
  ll mod;
  Math(ll mod = 1e9+7):mod(mod){}
  
  ll mod_pow(ll a,ll x){
    ll res=1;
    while(x){
      if(x%2) res=res*a%mod;
      a=a*a%mod;
      x/=2;
    }
    return res;
  }

  //逆元
  ll inv(ll a){return mod_pow(a,mod-2);}

  //階乗関数
  ll K(int i, int n = 1e6){
    static vector<ll> k(n);
    if(!k[0]){k[0]=1;for(int i=1;i<(int)k.size();i++)k[i]=i*k[i-1]%mod;}
    return k[i];
  }

  ll nPr(ll n, ll r){return K(n) * inv(K(n-r)) % mod;}

  //O(log(mod))  階上テーブルを使うので、k,rが大きすぎるとダメ。
  ll nCr(ll n,ll r){
    ll a = inv( K(r) * K(n-r) % mod);
    return K(n) * a % mod;
  }

  //O(r + log(mod))
  ll nCr2(ll n,ll r){
    ll N = 1, K = 1; 
    for(int i=0;i<r;i++) N=N*((n-i)%mod)%mod;
    for(int i=0;i<r;i++) K=K*((r-i)%mod)%mod;
    ll R = inv(K);
    return N*R%mod;
  }
  
  /*カーマイケル数ってなんだっけ忘れた*/
  static ll carmichaelLambda(ll n){
    ll res = 1;
    if(n % 8 == 0) n/=2;
    auto lcm = [](ll a,ll b){return (a/__gcd(a,b)) * b;};
    
    auto compute = [&](ll i){
      ll sub = i - 1;
      n/=i;
      while(n%i == 0) n/=i, sub *=i;
      res = lcm(res,sub);
    };
    
    for(int i=2;i*i<=n;i++) if( n % i == 0) compute(i);
    if(n != 1) compute(n);
    return res;
  }

  //n以下の素数を返す。  
  static vector<int> getPrime(int n){
    vector<bool>used(n+1,0);
    
    for(ll i=2;i*i<=n;i++)
      if(!used[i]) for(int j=2;j<=n/i;j++) used[i*j]=1;
    
    vector<int> res;
    for(int i=2;i<=n;i++)if(!used[i]) res.push_back(i);

    return res;
  }
  
  //素数判定
  static bool isPrime(ll n){
    if(n < 2) return 0;
    for(ll i=2;i*i<=n;i++) if(n%i==0) return 0;
    return 1;
  }

  //素因数分解 x == 0 || x == 1のときはその値自身を返す。
  static vector<ll> primeFactor(ll x,int flag = 0){
    if(flag == 0 && (x == 0 || x == 1)) return {x};
    if(flag == 1 && (x == 0 || x == 1)) return {};
    
    vector<ll> res;
    for(ll i=2;i*i <= x;i++)
      while(x%i == 0) x/=i, res.push_back(i);
    if(x != 1) res.push_back(x);
    return res;
  }

  static map<ll,ll> primeFactorMap(ll x,int flag = 0){
    map<ll,ll> res;
    if(flag == 0 && (x == 0 || x == 1)) {res[x]++; return res;}
    if(flag == 1 && (x == 0 || x == 1)) return res;
    
    for(ll i=2;i*i <= x;i++) while(x%i == 0) x/=i, res[i]++;
    if(x != 1) res[x]++;
    return res;
  }
  
  static ll divisor_Sum(map<ll,ll> prime){ // first : prime  second : cnt
    ll res = 1;
    for(P p : prime){
      ll sum = 1, mul = p.first;
      for(ll i=0;i<p.second;i++) sum += mul, mul *= p.first;
      res *= sum;
    }
    return res;
  }
  
  static ll divisor_Sum(ll num){
    return divisor_Sum(primeFactorMap(num));
  }
  
  //約数列挙
  static vector<ll> divisor(ll x){
    vector<ll> res;
    for(ll i=1; i*i<=x ;i++)
      if(x%i==0){
        res.push_back(i);
        if(i*i!=x) res.push_back(x/i);
      }
    sort(res.begin(), res.end());
    return res;
  }

  //a * bがオーバフローするか判定
  static bool overflow(ll a,ll b){return a > LONG_MAX/b;}

};


signed main(){
  
  Math math;
  int mod = math.mod;
  for(int i=1;i<=10000;i++) assert(i * math.inv(i)%mod == 1); //mod,inv
  
  for(int n=0;n <= 100;n++)
    for(int r=0;r <= n;r++) assert(math.nCr(n,r) == math.nCr2(n,r)); //nCr, nCr2

  //primeFcator
  for(int i=2;i<10000;i++){
    vector<int> fac = math.primeFactor(i);
    int a = 1;
    for(int f:fac) a *= f;
    assert(i == a);
  }

  //divisor
  for(int i=2;i<10000;i++){
    vector<int> div = math.divisor(i);
    auto m = math.primeFactorMap(i);
    int num = 1;
    for(auto p:m) num = num * (p.second + 1);
    cout<<pr(div.size(),num)<<endl;
    if(i) assert((int)div.size() == num);
    for(int d:div) assert(i % d == 0);
  }
  
  return 0;
}
