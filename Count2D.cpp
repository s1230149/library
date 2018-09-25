#include <bits/stdc++.h>
using namespace std;

class Count2D{
public:
  int n;
  vector<vector<int> > dat;
  
  Count2D(){}
  Count2D(int n_){
    n=1;
    while(n < n_) n*=2;
    dat.resize(2*n-1);
  }

  Count2D(int n_,vector<pair<int,int> > A){ //x,y
    n=1;
    while(n < n_) n*=2;
    dat.resize(2*n-1);
    
    for(auto a:A){
      int x,y; tie(x,y) = a;
      assert(x < n);
      dat[x+n-1].push_back(y);
    }
    
    function<void(int)> init=[&](int k){
      if(k >= n-1) {sort(dat[k].begin(),dat[k].end());return;}
      init(k*2+1), init(k*2+2);
      
      const auto &a = dat[k*2+1], &b = dat[k*2+2];
      auto &c = dat[k];
      int i = 0, j = 0;
      while(i < (int)a.size() || j < (int)b.size()){
        if(i == (int)a.size()) c.push_back(b[j++]);
        else if(j == (int)b.size()) c.push_back(a[i++]);
        else if(a[i] < b[j]) c.push_back(a[i++]);
        else c.push_back(b[j++]);
      }
    };
    init(0);
  }
  
  /*!!!!! O(nlog(n)) !!!!!*/
  void update(int x,int y){

    auto insert = [&](vector<int> &A,int a){
      A.push_back(a);
      int idx = (int)A.size()-1;
      while(idx && A[idx-1] > A[idx]) swap(A[idx-1],A[idx]),idx--;
    };
    
    x += n-1;
    insert(dat[x],y);
    while(x>0) x=(x-1)/2, insert(dat[x],y);
  }
  
  //[x,X)かつ[y,Y)の点の数を求める count(x,X,y,Y,0,0,n)
  // O(log(n) * log(n))
  int count(int x,int X,int y,int Y,int k=0,int l=0,int r=-1){
    if(r == -1) r = n, assert(x < n && X <= n);
    if(r<=x||X<=l)return 0;
    if(x<=l&&r<=X){
      int a = lower_bound(dat[k].begin(),dat[k].end(),y) - dat[k].begin();
      int b = upper_bound(dat[k].begin(),dat[k].end(),Y) - dat[k].begin();
      return b - a;
    }
    
    int vl=count(x,X,y,Y,k*2+1,l,(l+r)/2);
    int vr=count(x,X,y,Y,k*2+2,(l+r)/2,r);
    return vl + vr;
  }
};
