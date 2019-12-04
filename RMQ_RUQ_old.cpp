#include <bits/stdc++.h>
using namespace std;
/*
  RMQ and RUQ
  区間の最小値を得る(RMQ)
  区間の値を変更する(RUQ)
 */

template<typename dtype, dtype initValue /*範囲外の時に返す値*/>
class RMQ{
public : 
  
  struct data{
    bool type; //0 - empty   , 1 - update
    dtype value;
  };
  
  int n,n_;
  vector<dtype> dat;
  vector<data> td;
  int toMax;          //0 -> RangeMin 1->RangeMax;
  
  RMQ(){n=-1;}
  RMQ(int n_, int toMax = 0):n_(n_),toMax(toMax){
    n=1;
    while(n<n_)n*=2;
    td.resize(2*n-1,(data){0,initValue});
    dat.resize(2*n-1,initValue);
  }

  inline dtype merge(dtype a, dtype b){return toMax? max(a, b):min(a, b);}
  
  
  dtype dfs(int a,int b,dtype x,bool flag,int k,int l,int r){
    if(r <= a || b <= l) return flag? dat[k]:initValue;
    if(a <= l && r <= b){
      if(flag == true){
        td[k]=(data){1,x};
        dat[k]=x;
      }
      return dat[k];
    }
    
    if(td[k].type){
      td[k].type = 0;
      dat[k*2+1] = dat[k*2+2] = td[k].value;
      td[k*2+1] = td[k*2+2] = (data){1,td[k].value};
    }

    dtype vl=dfs(a, b, x, flag, k*2+1, l, (l+r)/2);
    dtype vr=dfs(a, b, x, flag, k*2+2, (l+r)/2, r);
    return flag? (dat[k] = merge(vl, vr)):merge(vl,vr);
  }
  
  //[l,r)の値をxに変更　update(l,r,x)
  void update(int l,int r,dtype x){
    assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    dfs(l, r, x, true, 0, 0, n);
  }
  
  //[l,r)の最小値を得る　find(l,r);
  dtype get(int l,int r){
    assert(l <= r), assert(l <= n && r <= n), assert(l >= 0 && r >= 0);
    return dfs(l, r, initValue , false, 0 , 0 ,n);
  }
};


int main(){
  int q,n;
  cin>>n>>q;
  typedef long long ll;
  RMQ <ll, INT_MAX> T(n, 0);

  while(q--){
    int cmd,s,t,x;
    scanf("%d%d%d",&cmd,&s,&t);
    if(cmd==0)cin>>x,T.update(s,t+1,x);
    else cout <<T.get(s,t+1)<<endl;
  }
  return 0;
}
