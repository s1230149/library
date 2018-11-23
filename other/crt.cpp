#include<bits/stdc++.h>
#include "extgcd.cpp"
using namespace std;

//中国余剰定理
// r % m[0] = b[0] && r % m[1] = b[1] && ... r % m[n-1] = b[n-1] となるrを求める。
template<typename T>
pair<T, T> crt(const vector<T> b, const vector<T> m){
  assert(b.size() == m.size());
  int n = b.size();
  T B = 0, lcm = 1;
  for(int i=0;i<n;i++){
    T x, y;
    T d = extgcd(lcm, m[i], x, y);
    if((b[i] - B) % d != 0) return {-1, -1}; //no solution
    T tmp = (b[i] - B) / d * x % (m[i] / d);
    B = B + lcm * tmp;
    lcm = lcm * m[i] / d;
  }
  return {(B % lcm + lcm) % lcm, lcm};
}

