#include<bits/stdc++.h>
using namespace std;

// ax + by = gcd(a, b)となるx, yを求める
template<typename T>
T extgcd(T a, T b, T &x, T &y){
  if(b == 0){x = 1; y = 0; return a;}
  T d = extgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return d;
}

