#include <bits/stdc++.h>
using namespace std;

class Rand{
public:
  typedef long long ll;
  random_device rnd;//毎回異なる乱数
  mt19937_64 mt; //unsigned 64bitメルセンヌ_ツイスタ [0, 2^66]
  //mt19937 mt; //unsigned 32bitメルセンヌ_ツイスタ [0, 2^32]
  
  Rand():mt(rnd()){}
  //Rand():mt((unsigned int)time(NULL)){};
  
  ll get(){return mt()>>1;} //[0, (2^63)-1]
  ll get(ll l,ll r){ //[l, r]
    assert(l <= r);
    return l + get() % (r - l + 1);
  }
};

int main(){
  Rand rand;
  cout<<rand.get(-10, 10)<<endl;
  while(1){
    long long l = rand.get(), r = rand.get();
    if(l > r) swap(l, r);
    assert(0 <= l && 0 <= r);
    long long m = rand.get(l, r);
    cout<<l<<" "<<r<<" "<<m<<" "<<log10(l)<<" "<<log10(r)<<" "<<log10(m)<<endl;
    assert(l <= m && m <= r);
  }

}
