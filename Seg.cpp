#include <bits/stdc++.h>
#define int long long
using namespace std;

/*Starry Sky Tree*/
/*Range Add Min(Max) Query*/
/*区間加算、区間Min,区間Max*/
#define nullQ 0
#define addQ 1
#define updateQ 2
class RSUQ{
public: 
  
  //遅延用の型  
  struct T{
    int type; //0 - empty   , 1 - update, 2 - add
    int value;
    T():type(nullQ),value(0){}
    T(int type,int value):type(type),value(value){}
  };
  
  //マージ可能な主データ型
  struct D{
    int value;
    D():value(0){} /*適切な値にする!!!!!!*/
    D(int value):value(value){}
    bool operator < (D a)const {return value < a.value;} //merge用
  };
  
  int n;
  vector<D> dat;
  vector<T> td;
  D returnD = D(LONG_MAX/2); // 範囲外の時に返す値。
  
  RSUQ(){n=-1;}
  RSUQ(int n_){
    n=1;
    while(n<n_)n*=2;
    td.resize(2*n-1,T());
    dat.resize(2*n-1,D());
  }
  
  D merge(D a,D b){return min(a,b);}
  
  void delay(int k,int len){
    if(td[k].type==nullQ) return;
    int t = td[k].type ;
    int v = td[k].value;
    
    td[k].type = 0;
    td[k].value = 0;
    len /= 2;
    int l = k*2+1,r = k*2+2;
    
    if(t == updateQ){ // update
      dat[l].value = v; td[l] = T(updateQ,v);
      dat[r].value = v; td[r] = T(updateQ,v);
    }
    if(t == addQ){// add
      if(td[l].type != nullQ) dat[l].value += v, td[l].value += v;
      else dat[l].value += v, td[l] = T(addQ,v);
      
      if(td[r].type != nullQ) dat[r].value += v, td[r].value += v;
      else dat[r].value += v, td[r] = T(addQ,v);
    }
  }

  D update(int k,int x, int len,int type){
    if(type == updateQ){ //update
      dat[k].value = x;
      td[k].type = updateQ;
      td[k].value = x;
    }
    
    if(type == addQ){ // add
      assert(td[k].type == nullQ);
      dat[k].value += x;
      td[k].type = addQ;
      td[k].value = x;
    }
    return dat[k];
  }
  
  //[a,b)の値をx変更　add(a,b,x)
  D query(int a,int b,int x,int type=nullQ,int k=0,int l=0,int r=-1){
    if(r==-1) r=n, assert(a <= n && b <= n);
    if(r<=a||b<=l) return type? dat[k]:returnD;
    if(a<=l&&r<=b) return type? update(k, x, r - l, type):dat[k];
    
    delay(k, r - l);
    D vl = query(a,b,x,type,k*2+1,l,(l+r)/2);
    D vr = query(a,b,x,type,k*2+2,(l+r)/2,r);
    if(type) dat[k] = merge(vl,vr);
    return merge(vl,vr);
  }

  void update(int a,int b,int x){query(a,b,x,updateQ);}
  void add(int a,int b,int x){query(a,b,x,addQ);}
  
  //[a,b)の合計値を得る　find(a,b);
  int find(int a,int b){
    D res = query(a,b,0,nullQ);
    return res.value;
  }
};



signed main(){

  RSUQ A(16);
  auto ouput=[&](){
    for(int i=0;i<16;i++) cout<<A.find(i,i+1)<<" ";cout<<endl;
  };

  for(int i=0;i<16;i++) A.update(i,i+1,i);
  cout<<A.td[0].type<<endl;
  ouput();
  A.add(0,16,1);
  ouput();
  
  A.update(0,5,-10);
  ouput();


  int n,q;
  cin>>n>>q;

  RSUQ rsuq(n);
  while(q--){
    int cmd;
    cin>>cmd;
    if(cmd == 0){
      int s,t,x;
      cin>>s>>t>>x;
      rsuq.query(s,t+1,x);
    }
    if(cmd == 1){
      int s,t;
      cin>>s>>t;
      cout<<rsuq.find(s,t+1)<<endl;
    }
  }
  
  return 0;
}
