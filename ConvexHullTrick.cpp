#include <bits/stdc++.h>
using namespace std;


template <typename T, T INF>
class ConvexHullTrick{
public:
  typedef pair<T, T> P;
  deque<P> L;
  int toMax;
  T preX; //getMonotone関数のassert用変数
  ConvexHullTrick(int toMax = 0):toMax(toMax), preX(-INF){}
  inline int size()const{return L.size();}
  
  T getY(const P &l, T x){return l.first * x + l.second;}
  
  bool check(P l1, P l2, P l3){
    return
      (l2.first - l1.first) * (l3.second - l2.second) >=
      (l2.second - l1.second) * (l3.first - l2.first);
  }

  void add(T a, T b){
    if(toMax) a *= -1, b *= -1;
    assert(size() == 0 || L[size() - 1].first >= a); //追加する直線の傾きは単調減少でなければならない。
    
    P l = P(a, b);
    if(size() != 0 && L[size() - 1].first == a){
      l = min(l, L[size()-1]);
      L.pop_back();
    }
    while(size() >= 2 && check(L[size() - 2], L[size() - 1], l)) L.pop_back();
    L.push_back(l);
  }

  //直線集合の中でgetY(x)が最小または最大になる値を返す。O( logN )
  T get(T x){
    if(size() == 0) return toMax? -INF:INF;
    int low = -1, high = size() - 1;
    while(low + 1 < high){
      int mid = (low + high) / 2;
      getY(L[mid], x) >= getY(L[mid+1], x)? (low = mid):(high = mid);
    }
    return (toMax? -1:1) * getY(L[high], x);
  }

  //クエリの引数xが単調増加順で与えられるときgetMonotoneを使うと全体でO(N)で行える
  T getMonotone(T x){
    assert(x >= preX); //xは単調増加でないといけない
    preX = x;    
    if(size() == 0) return toMax? -INF:INF;
    while(size() >= 2 && getY(L[0], x) >= getY(L[1], x)) L.pop_front();
    return (toMax? -1:1) * getY(L[0], x);
  }
};

//https://beta.atcoder.jp/contests/colopl2018-final-open/tasks/colopl2018_final_c
void AtCoder_colopl2018_final_c_test_getMonotone(){
  int n;
  cin>>n;
  using T = long long;
  ConvexHullTrick <T, T(1e18)> cht;
  for(T i=0;i<n;i++){
    T a;
    cin>>a;
    cht.add(-2 * i, i * i + a);
  }

  for(T i=0;i<n;i++){
    T ans = i * i + cht.getMonotone(i);
    cout<<ans<<endl;
  }
}

void AtCoder_colopl2018_final_c_test_get(){
  int n;
  cin>>n;
  using T = long long;
  ConvexHullTrick <T, T(1e18)> cht;
  for(T i=0;i<n;i++){
    T a;
    cin>>a;
    cht.add(-2 * i, i * i + a);
  }

  for(T i=0;i<n;i++){
    T ans = i * i + cht.get(i);
    cout<<ans<<endl;
  }
}
  
signed main(){
  //AtCoder_colopl2018_final_c_test_getMonotone();
  AtCoder_colopl2018_final_c_test_get();
  return 0;
}
