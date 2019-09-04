#include <bits/stdc++.h>
using namespace std;

class ArgSort{
public:

  //pair<T, T>(x, y)の入力に対して反時計偏角ソートする。
  template<typename T>
  static vector<pair<T, T> > Sort(vector<pair<T, T> > A){
    sort(A.begin(), A.end(), [&](const auto &p1,const auto &p2){
        return atan2(p1.second, p1.first) < atan2(p2.second, p2.first);
      });
    return A;
  }

  //complex<T>(x, y)の入力に対して反時計偏角ソートする。
  template<typename T>
  static vector<complex<T> > Sort(vector<complex<T> > A){
    sort(A.begin(), A.end(), [&](const auto &p1,const auto &p2){
        return atan2(p1.imag(), p1.real()) < atan2(p2.imag(), p2.real());
      });
    return A;
  }
};

void ABC139_F_pair(){
  using Int = long long;
  using Double = long double;
  using P = pair<Int, Int>;

  Int N;
  cin>>N;
  vector<P> A(N);
  for(int i=0;i<N;i++){
    int x, y;
    cin>>x>>y;
    A[i] = P(x, y);
  }

  A = ArgSort::Sort(A);

  Int ans = 0;
  for(Int i=0;i<N;i++)
    for(Int j=0;j<N;j++){
      Int idx = i;
      Int x = 0, y = 0;
      while(1){
        x += A[idx].first;
        y += A[idx].second;
        ans = max(ans, x * x + y * y);
        if(idx == j) break;
        idx = (idx + 1)%N;
      }
    }
  cout << fixed << setprecision(12);
  cout<<sqrt((Double)ans)<<endl;


}
void ABC139_F_complex(){
  using Int = long long;
  using Double = long double;
  using P = complex<Int>;

  Int N;
  cin>>N;
  vector<P> A(N);
  for(int i=0;i<N;i++){
    int x, y;
    cin>>x>>y;
    A[i] = P(x, y);
  }

  A = ArgSort::Sort(A);

  Int ans = 0;
  for(Int i=0;i<N;i++)
    for(Int j=0;j<N;j++){
      Int idx = i;
      Int x = 0, y = 0;
      while(1){
        x += A[idx].real();
        y += A[idx].imag();
        ans = max(ans, x * x + y * y);
        if(idx == j) break;
        idx = (idx + 1)%N;
      }
    }
  cout << fixed << setprecision(12);
  cout<<sqrt((Double)ans)<<endl;
}

signed main(){
  //ABC139_F_complex();
  //ABC139_F_pair();
  return 0;
}
