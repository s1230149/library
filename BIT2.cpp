#include <bits/stdc++.h>
using namespace std;

//区間加算、区間和, 0オリジン

template<typename D = long long, int useAssert = 1>
class BIT{
public:
  int n;
  vector<D> bit0, bit1;
  BIT(){n = -1;}
  BIT(int n_){
    n = 1;
    while(n < n_) n *= 2;
    bit0.resize(n+1, 0);
    bit1.resize(n+1, 0);
  }

  D sum(vector<D> &b, int i){
    D s = 0;
    while(i > 0){
      s = (s + b[i]);// % mod;
      i -= i & -i;
    }
    return s;
  }

  void add(vector<D> &b, int i, D v){
    // v = (mod + v % mod) % mod;
    while(i <= n){
      b[i] = (b[i] + v);//% mod;
      i += i & -i;
    }
  }

  //[a,b)にxを加算 0オリジン
  void add (int a, int b, D x){
    // x = (mod + x % mod) % mod;
    if(a == b) return;
    a++;
    if(useAssert) assert(a <= b && 1 <= a && b <= n);
    add(bit0, a, -x*(a-1));
    add(bit1, a, x);
    add(bit0, b+1, x*b);
    add(bit1, b+1, -x);
  }

  //[a,b)のsumを得る 0オリジン
  D sum(int a, int b){
    if(a == b) return 0;
    a++;
    if(useAssert) assert(a <= b && 1 <= a && b <= n);
    D s = sum(bit0, b);
    D t = sum(bit1, b) * b;
    D u = sum(bit0, a-1);
    D v = sum(bit1, a-1) * (a-1);
    return s + t - u - v;
    //return ((s + t) + (mod - u%mod) + (mod - v%mod)) % mod;
  }
};

int main(){
  int n, q;
  cin>>n>>q;

  BIT <> bit(n);

  for(int i=0;i<q;i++){
    int cmd;
    cin>>cmd;
    if(cmd == 0){
      int s, t, x;
      cin>>s>>t>>x; s--, t--;
      bit.add(s, t+1, x);
    }
    else {
      int s, t;
      cin>>s>>t; s--, t--;
      long long ans = bit.sum(s, t+1);
      cout<<ans<<endl;
    }
  }

}
