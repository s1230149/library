#include <bits/stdc++.h>
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME
#define pr(...) cerr<< GET_MACRO(__VA_ARGS__,pr8,pr7,pr6,pr5,pr4,pr3,pr2,pr1)(__VA_ARGS__) <<endl
#define pr1(a) (#a)<<"="<<(a)<<" "
#define pr2(a,b) pr1(a)<<pr1(b)
#define pr3(a,b,c) pr1(a)<<pr2(b,c)
#define pr4(a,b,c,d) pr1(a)<<pr3(b,c,d)
#define pr5(a,b,c,d,e) pr1(a)<<pr4(b,c,d,e)
#define pr6(a,b,c,d,e,f) pr1(a)<<pr5(b,c,d,e,f)
#define pr7(a,b,c,d,e,f,g) pr1(a)<<pr6(b,c,d,e,f,g)
#define pr8(a,b,c,d,e,f,g,h) pr1(a)<<pr7(b,c,d,e,f,g,h)
using namespace std;
using Int = long long;
using _int = int;
using ll = long long;
using Double = long double;
const Int INF = (1LL<<55)+1e9; // ~ 3.6 * 1e16
const Int mod = (1e9)+7;
const Double EPS = 1e-8;
const Double PI = 6.0 * asin((Double)0.5);
using P = pair<Int,Int>;
using T = tuple<Int,Int,Int>;
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}
template<class T1, class T2> ostream& operator<<(ostream& o,pair<T1,T2> p){return o<<"("<<p.first<<","<<p.second<<")";}
template<class T1, class T2, class T3> ostream& operator<<(ostream& o,tuple<T1,T2,T3> t){
  return o<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")";}
template<class T1, class T2> istream& operator>>(istream& i,pair<T1,T2> &p){return i>>p.first>>p.second;}
template<class T> ostream& operator<<(ostream& o,vector<T> &a){Int i=0;for(T t:a)o<<(i++?" ":"")<<t;return o;}
template<class T> istream& operator>>(istream& i,vector<T> &a){for(T &t:a)i>>t;return i;}
template<class T>void prArr(T a,string s=" "){Int i=0;for(T t:a)cout<<(i++?s:"")<<t;cout<<endl;}

template<typename ctype>
class BellmanFord{
public:
  double EPS = 1e-8;
  using T = tuple<int, int, ctype>;
  int V;
  ctype INF;
  vector<T> edge;
  BellmanFord():V(-1){}
  BellmanFord(int V, ctype INF):V(V), INF(INF){}
  
  void add_edge(int from, int to,ctype cost){
    assert(0 <= from && from < V);
    assert(0 <= to && to < V);
    edge.push_back(T(from, to, cost));
  }
  
  void add_bidirectional_edge(int a,int b,ctype cost){
    add_edge(a, b, cost);
    add_edge(b, a, cost);
  }

  //s番目の頂点から各頂点への最短距離を求める。
  vector<ctype> calcD(int start){
    assert(0 <= start && start < V);
    vector<ctype> D(V, INF);   //最短距離
    D[start] = 0;
    
    int cnt = 0;
    bool update = true;
    while(update){
      if(++cnt > V) return {}; //負の閉路
      update = false;
      for(auto e:edge){
	int from, to;
	ctype cost;
	tie(from, to, cost) = e;
	ctype ncost = D[from] + cost;
	if(abs(D[from] - INF) < EPS || ncost - D[to] > -EPS) continue;
	D[to] = ncost;
	update = true;
      }
    }
    return D;
  }
};

signed main(){
  srand((unsigned)time(NULL));
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int N, M, start;
  cin>>N>>M>>start;

  typedef long long ll;
  ll INF = 1e18;
  BellmanFord <ll> bf(N,INF);
  for(int i=0;i<M;i++){
    int from, to, cost;
    cin>>from>>to>>cost;
    bf.add_edge(from, to, cost);
  }

  vector<ll> D = bf.calcD(start);
  if(D.empty()) cout<<"NEGATIVE CYCLE"<<endl;
  else {
    for(int i=0;i<N;i++)
      if(D[i] != INF) cout<<D[i]<<endl;
      else cout<<"INF"<<endl;
  }
  
  return 0;
}
