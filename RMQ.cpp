#include <bits/stdc++.h>
using namespace std;

template<typename dtype>
class RMQ{
public:
  dtype initValue; //範囲外のときに返す値。
  int n,n_;
  vector<dtype> dat;
  int toMax;

  //初期化
  RMQ(){n=-1;}
  RMQ(int n_,dtype initValue,int toMax = 0):n_(n_),initValue(initValue),toMax(toMax){
    n=1;
    while(n<n_)n*=2;
    dat.resize(2*n-1,initValue);
  }

  inline dtype merge(dtype a,dtype b){return toMax? max(a, b):min(a, b); }

  //k番目の値をaに変更
  void update(int k,dtype a){
    k+=n-1;
    dat[k]=a;
    while(k>0){
      k=(k-1)/2;
      dat[k]=min(dat[k*2+1],dat[k*2+2]);
    }
  }
  
  dtype dfs(int a,int b,int k,int l,int r){
    if(r<=a||b<=l)return initValue;
    if(a<=l&&r<=b)return dat[k];
    dtype vl = dfs(a,b,k*2+1,l,(l+r)/2);
    dtype vr = dfs(a,b,k*2+2,(l+r)/2,r);
    return merge(vl,vr);
  }
  
  //[a,b)の最小値を求める
  dtype get(int a,int b){
    assert(a <= b), assert(a <= n_ && b <= n_), assert(a >= 0 && a >= 0);
    return dfs(a,b,0,0,n);
  }
};

int main(){
  int n,q;
  cin>>n>>q;
  typedef long long ll;
  RMQ <ll> A(n,INT_MAX,0);

  while(q--){
    int com,x,y;
    cin>>com>>x>>y;
    if(com == 0) A.update(x,y);
    if(com == 1) cout<<A.get(x,y+1)<<endl;
  }

  return 0;
}

