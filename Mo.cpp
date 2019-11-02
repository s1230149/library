#include<bits/stdc++.h>
using namespace std;

template<int X/*分割数*/, typename D/*クエリの型*/, typename E/*solveの型*/>
class Mo_super{
public:
  //[l, r]
  virtual void incL(int l) = 0;
  virtual void decL(int l) = 0;
  virtual void incR(int r) = 0;
  virtual void decR(int r) = 0;
  virtual E calc(int l, int r, D x) = 0;

  struct T{
    int l, r;
    D x;
    int ord;
    T(){}
    T(int l, int r, D x, int ord):l(l), r(r), x(x), ord(ord){}
    bool operator <(const T &a)const{return r != a.r? r < a.r: l < a.l;}
  };

  int N; //クエリの数
  vector<T> query;
  vector<vector<T> > Q;
  int ok;
  Mo_super():N(0), ok(1){}

  //[l, r];
  void addQuery(int l, int r, D x){
    assert(0 <= l && l <= r);
    query.emplace_back(l, r, x, N++);
  }

  //O((N+Q) * sqrt(N))
  vector<E> solve(){
    assert(ok == 1);
    int max_l = query[0].l;
    for(auto &t:query) max_l = max(max_l, t.l);

    const int M = max_l / X + 1;
    Q.clear(); Q.resize(M);
    for(auto &t:query) Q[t.l / X].push_back(t);
    for(auto &q:Q) sort(q.begin(), q.end());

    vector<E> res(N);
    int l = 0, r = -1; //[l, r]
    for(auto &q:Q)
      for(auto &a:q){
        while(l > a.l) decL(l), l--;
        while(r < a.r) incR(r), r++;
        while(l < a.l) incL(l), l++;
        while(r > a.r) decR(r), r--;
        res[a.ord] = calc(l, r, a.x);
      }
    return res;
  }
  /*
    template<int X, typename D, typename E>
    class Mo : public Mo_super<X, D, E>{
    //[l, r]
    void incL(int l){}
    void decL(int l){}
    void incR(int r){}
    void decR(int r){}
    E calc(int l, int r, D x){}
    };
  */
};
