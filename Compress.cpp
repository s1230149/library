#include <bits/stdc++.h>
using namespace std;

//座標圧縮

template <typename T>
class Compress{
public:
  vector<T> X;
  bool ok;
  Compress(){};
  
  int size(){return X.size();}
  void add(T a){ok = false; X.push_back(a); X.push_back(a-1); X.push_back(a+1);}
  void add(const vector<T> a){for(T x:a) add(x);}
  //void add(const vector<T> &a){for(T x:a) add(x);}
  
  void build(){
    ok = true;
    sort(X.begin(),X.end());
    X.erase(unique(X.begin(),X.end()),X.end());
  }
  
  T getL(T x){assert(ok); return lower_bound(X.begin(),X.end(),x) - X.begin();}
  T getU(T x){assert(ok); return upper_bound(X.begin(),X.end(),x) - X.begin();}
};


int main(){
  Compress <int> A;
  A.add(1);
  A.add(10);
  A.add({100, 1000});
  A.build();
}
