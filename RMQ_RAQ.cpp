#include <bits/stdc++.h>
#define int long long
using namespace std;

/*Range Add Min(Max) Query*/
/*区間加算、区間Min,区間Max*/

class RMAQ{
public: 
  
  //遅延用の型  
  struct T{
    bool type; //0 - empty   , 1 - update
    int value;
    T():type(0),value(0){}
    T(bool type,int value):type(type),value(value){}
  };

  //比較可能な主データ型
  struct D{
    int value;
    D():value(0){} /*適切な値にする!!!!!!*/
    D(int value):value(value){}
    bool operator < (D a)const {return value < a.value;} //merge用
  };
  
  D INF = D(1LL<<55); /*!!!!!!!!!!!!!!!!!!!!!!!!*/

  int n;
  vector<D> dat;
  vector<T> td;
  int toMax; //0 -> RangeMin, 1 -> RangeMax
  
  RMAQ(){n=-1;}
  RMAQ(int n_,int toMax = 0){
    this->toMax = toMax;
    n=1;
    while(n<n_)n*=2;
    td.resize(2*n-1,T());
    dat.resize(2*n-1,D());
  }
  
  D merge(D a,D b){return min(a,b);}
  
  void delay(int k){
    if(td[k].type==0) return;
    int v = td[k].value;
    td[k].type = 0;
    td[k].value = 0;
    
    int l = k*2+1,r = k*2+2;
    dat[l].value += v; td[l].type = 1; td[l].value += v;
    dat[r].value += v; td[r].type = 1; td[r].value += v;
  }

  D update(int k,int x){
    td[k].type = 1;
    td[k].value += x;
    dat[k].value += x;
    return dat[k];
  }
  
  //[a,b)の値をx加算　add(a,b,x)
  D add(int a,int b,int x,bool flg=true,int k=0,int l=0,int r=-1){
    if(r==-1 && toMax) x *= -1; 
    if(r==-1) r=n, assert(a <= n && b <= n);
    if(r<=a||b<=l) return flg? dat[k]:INF;
    if(a<=l&&r<=b) return flg? update(k,x):dat[k];
    
    delay(k);
    D vl = add(a,b,x,flg,k*2+1,l,(l+r)/2);
    D vr = add(a,b,x,flg,k*2+2,(l+r)/2,r);
    if(flg) dat[k] = merge(vl,vr);
    return merge(vl,vr);
  }
  
  //[a,b)の最小値を得る　find(a,b);
  int find(int a,int b){
    D res = add(a,b,0,false);
    if(toMax) res.value *= -1; 
    return res.value;
  }
};


signed main(){
  int n,q;
  cin>>n>>q;
  
  RMAQ rmaq(n);
  while(q--){
    int ord;
    cin>>ord;
    if(ord == 0){
      int s,t,x;
      cin>>s>>t>>x;
      rmaq.add(s,t+1,x);
    }
    if(ord == 1){
      int s,t;
      cin>>s>>t;
      cout<<rmaq.find(s,t+1)<<endl;
    }
  }
  
  return 0;
}
