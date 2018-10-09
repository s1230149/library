#include <bits/stdc++.h>
using namespace std;

template<typename T>
class CumulativeSum{
public:
  int n;
  vector<T> sum;
  vector<T> A;
  int added;
  CumulativeSum():n(-1),added(0){}
  CumulativeSum(int n):n(n), sum(n+1), A(n+1),added(0){}
  CumulativeSum(const vector<T> &B):n(B.size()), sum(n+1), A(n+1),added(0){
    for(int i=1;i<=n;i++) sum[i] = sum[i-1] + B[i-1];
  }

  void apply(){
    for(int i=1;i<=n;i++) A[i] = A[i] + A[i-1];
    for(int i=1;i<=n;i++) A[i] = A[i] + A[i-1];
    for(int i=1;i<=n;i++) sum[i] = sum[i] + A[i-1];
    added = 0; A.clear(); A.resize(n+1);
  }

  //[l, r)にxを加算
  void add(int l, int r, T x){
    added = 1;
    assert(l <= r && 0 <= l && r <= n);
    A[l] = A[l] + x;
    A[r] = A[r] - x;
  }

  //[l, r)の和を得る
  T get(int l,int r){
    assert(l<=r && 0<=l && r<=n);
    if(added) apply();
    return sum[r] - sum[l];
  }
};

signed main(){
  srand((unsigned)time(NULL));

  auto add = [&](vector<int> &A, int l,int r,int x){for(int i=l;i<r;i++) A[i] += x;};
  auto get = [&](vector<int> &A, int l,int r){return accumulate(A.begin() + l, A.begin()+r, 0LL);};
  
  auto verify1 = [&](){
    int n = rand() % 10;
    vector<int> A(n);
    for(int i=0;i<n;i++) A[i] = rand() % 200 - 100;
    int Q = 100000;
    CumulativeSum<int> sum(A);
    while(Q--){
      int l = rand()%n;
      int r = rand()%n + 1;
      int x = rand()%200 - 100;
      if(l > r) swap(l, r);
      if(rand()%2) add(A, l, r, x), sum.add(l, r, x);
      else assert(sum.get(l, r) == get(A, l, r));
    }
  };

  auto verify2 = [&](){
    int n = rand() % 10;
    vector<int> A(n);
    int Q = 100000;
    CumulativeSum<int> sum(n);
    while(Q--){
      int l = rand()%n;
      int r = rand()%n + 1;
      int x = rand()%200 - 100;
      if(l > r) swap(l, r);
      if(rand()%2) add(A, l, r, x), sum.add(l, r, x);
      else assert(sum.get(l, r) == get(A, l, r));
    }
  };

  verify1();
  verify2();
  cout<<"ok"<<endl;

  return 0;
}
