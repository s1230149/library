#include <bits/stdc++.h>
#define int long long
using namespace std;

template<typename T>
class Pollards_Rho{

public:
  
  typedef long long ll;
  
  Pollards_Rho(){}
  
  T mod_pow(T x, T n, T mod){
    T res = 1;
    while(n){
      if( n % 2 ) res = res * x % mod;
      x = x * x % mod;
      n /= 2;
    }
    return res;
  }
  
  // ミラーラビンによる素数判定
  bool miller_rabin(T n){
    if( n == 2 ) return true;
    if( n == 1 || n % 2 == 0 ) return false;
    T s = 0, d = n - 1;
    random_device rd;
    while( d % 2 == 0 ) s++, d /= 2;
    T cnt = 20;
    while(cnt--){
      T a = rd() % ( n - 1 ) + 1;
      T t = d;
      T y = mod_pow( a, t, n );
      while( t != n - 1 && y != 1 && y != n - 1 ){
	y = ( y * y ) % n;
	t *= 2;
      }
      if( y != n - 1 && t % 2 == 0 ) return false;
    }
    return true;
  }
  
  // nを法とする擬似乱数発生関数
  T f(T x, T n){
    T c = 5;
    return ( x * x + c ) % n;
  }
  
  T Abs(T x){
    if( x < 0 ) x *= -1;
    return x;
  }
  
  // ポラード・ローによる素因数探し（素でない因数を見つける場合もある）
  T pollards_rho(T n){
    T y = rand() % ( n + 1 );
    T r = 1, q = 1, m = rand() + 1;
    T g, ys, x;
    do{
      x = y;
      for(T i=1;i<=r;++i) y = f( y, n );
      T k = 0;
      do{
	ys = y;
	for(T i=1;i<=min( m, r - k );++i){
	  y = f( y, n );
	  q = ( q * Abs( x - y ) ) % n;
	}
	g = __gcd( q, n );
	k = k + m;
      }
      while( k < r && g <= 1 );
      r = 2 * r;
    }
    while( g <= 1 );
    if( g == n ){
      do{
	ys = f( ys, n );
	g = __gcd( (T)Abs( x - ys ), n );
      }
      while( g <= 1 );
    }
    return g;
  }
  
  // nを素因数分解し、ソートして返す
  vector<T> factor(T n){
    assert( 1 < n );
    vector<T> res;
    while( miller_rabin(n) == false ){
      T r = pollards_rho(n);
      if( 1 < r && r < n && miller_rabin(r) == true ){
	res.push_back( r );
	n /= r;
      }
    }
    if( n != 1 ) res.push_back( n );
    sort( res.begin(), res.end() );
    return res;
  }
  
};

ostream& operator<<(ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}

signed main(){
  
  while(1){
    
    Pollards_Rho<__int128_t> pr;
    
    int n;
    cin>>n;
    
    if( n == 0 ) break;
    
    vector<__int128_t> ans = pr.factor(n);
      
    for(int i=0;i<(int)ans.size();i++) cout<<ans[i]<<' ';
    
    cout<<endl;
    
  }
  
  return 0;
}
