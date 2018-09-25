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
template<class T>void prArr(T a,string s=" "){Int i=0;for(auto t:a)cout<<(i++?s:"")<<t;cout<<endl;}

template<typename Monoid = int, typename OperatorMonoid = Monoid>
class LinkCutTree{
public:
  using F = function <Monoid(Monoid, Monoid) > ;
  using G = function <Monoid(Monoid, OperatorMonoid, int)>;
  using H = function <OperatorMonoid(OperatorMonoid, OperatorMonoid)>;
  
  struct Node{
    Node *l, *r, *p;
    int idx;
    Monoid key, sum;
    OperatorMonoid lazy;
    
    bool rev;
    int sz;
    
    bool is_root(){
      return !p || (p->l != this && p->r != this);
    }

    Node(int idx, const Monoid &key, const OpetatorMonoid &om):
      idx(idx), key(key), sum(key), lazy(om), sz(1),
      l(nullptr), r(nullptr), p(nullptr), rev(false) {}
  };
  const Monoid M1;
  const OperatorMonoid OM0;
  const F f;
  const G g;
  const H h;

  LinkCutTree(): LinkCutTree([](Monoid a, Monoid b){ return a + b;}, Monoid()){}
  
  LinkCutTree(const F &f, const Monoid &M1):
    LinkCutTree(f, G(), H(), M1, OperatorMonoid()){}

  LinkCutTree(const F &f, const G &g, const H &h,
	      const Monoid &M1, const OperatorMonoid &OM0):
    f(f), g(g), h(h), M1(M1), OM0(OM0){}

  Node *make_node(int idx, const Monoid &v = Monoid()){
    return new Node(idx, v, OM0);
  }

  void propagate(Node *t, const OperatorMonoid &x){
    if(t == nullptr) return;
    t -> lazy = h(t->lazy, x);
    t -> key = g(t->key, x, 1);
    t -> sum = g(t -> sum, x, t -> sz);
  }

  //reverseの処理
  void toggle(Node *t){
    if(t == nullptr) return;
    assert(t);
    swap(t -> l, t -> r);
    
    t -> rev ^= true;
  }

  void push(Node *t){
    if(t -> lazy != OM0) {
      if(t -> l) propagate(t -> l, t -> lazy);
      if(t -> r) propagate(t -> r, t -> lazy);
      t -> lazy = OM0;
    }

    if(t -> rev){
      if(t -> l) toggle(t -> l);
      if(t -> r) toggle(t -> r);
      t->rev = false;
    }
  }

  void update(Node *t){
    t -> sz = 1;
    t -> sum = t -> key;
    if(t -> l) t -> sz += (t -> l -> sz), t -> sum = f(t -> l -> sum, t -> sum);
    if(t -> r) t -> sz += (t -> r -> sz), t -> sum = f(t -> sum, t -> r -> sum);
  }

  
  /*********************************************/
  /*        |y|                   |y|          */ 
  /*         |                     |           */
  /*        |x|        rotR       |t|          */
  /*      /     \      ===>     /     \        */
  /*     |t|   |xr|           |tl|    |x|      */
  /*    /   \                        /   \     */
  /*  |tl| |tr|                   |tr|   |xr|  */
  /*********************************************/
  void rotR(Node *t){ //右回転
    Node *x = t -> p, *y = x -> p;
    if( (x -> l = t -> r) ) t -> r -> p = x;
    t -> r = x; x -> p = t;
    update(x), update(t);
    if( (t -> p = y) ){
      if(y -> l == x) y -> l = t;
      if(y -> r == x) y -> r = t;
      update(y);
    }
  }


  /**********************************************/
  /*     |y|                          |y|       */
  /*      |                            |        */
  /*     |x|           rotL           |t|       */
  /*    /    \         ===>         /     \     */
  /*  |xl|   |t|                  |x|    |tr|   */
  /*        /   \                /   \          */
  /*      |tl| |tr|            |xl| |tl|        */
  /**********************************************/
  void rotL(Node *t){
    Node *x = t->p, *y = x -> p;
    if( (x -> r = t -> l) ) t -> l -> p = x;
    t -> l = x; x -> p = t;
    update(x), update(t);
    if( ( t -> p = y) ){
      if(y -> l == x) y -> l = t;
      if(y -> r == x) y -> r = t;
      update(y);
    }
  }

  void splay(Node *t){
    push(t);
    while(!t -> is_root()){
      Node *q = t-> p;
      
      //zig step
      if( q->is_root()){
	push(q), push(t);
	(q -> l  == t)? rotR(t):rotL(t);
	return;
      } 
	
      Node *r = q -> p;
      push(r), push(q), push(t);
      if(r -> l == q){
	if(q -> l == t) rotR(q), rotR(t);    //zig-zig step
	else rotL(t), rotR(t);               //zig-zag step
      }
      else{
	if(q -> r == t) rotL(q), rotL(t);    //zig-zig step
	else rotR(t), rotL(t);               //zig-zag step
      }
    }
  }

  //根からxまでのパスをひとつながりにする(根からxまでのパス上のライトエッジをなくす)。
  //xの右の子は必ずnullptrになる。
  Node *expose(Node *t){
    Node *rp = nullptr;
    for(Node *p = t; p ; p = p -> p){
      splay(p);
      p -> r = rp;
      update(p);
      rp = p;
    }
    splay(t); //しとくと便利らしい。
    return rp;
  }

  //cとpを繋げる。
  void link(Node *child, Node *parent){
    expose(child);
    expose(parent);
    child -> p = parent;
    parent -> r = child;
  }
  
  void cut(Node *child){
    expose(child);
    Node *parent = child -> l;
    child -> l = nullptr;
    parent -> p = nullptr;
  }

    
  void evert(Node *t){
    expose(t);
    toggle(t);
    push(t);
  }

  Node *lca(Node *u, Node *v){
    expose(u);
    return expose(v);
  }
  
  vector<int> getPath(Node *x){
    vector<int> vs;
    function< void(Node *) > dfs = [&](Node *pos){
      if(!pos) return;
      push(pos);
      dfs( pos -> r );
      vs.push_back( pos -> idx );
      dfs( pos -> l );
    };
    expose(x);
    dfs(x);
    return vs;
  }

  void set_propagate(Node *t, const OperatorMonoid &x){
    expose(t);
    propagate(t, x);
    push(t);
  }
};



signed main(){
  srand((unsigned)time(NULL));
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int N;
  cin>>N;
  auto f = [&](int x, int y){return x + y;};
  auto g = [&](int x, int y, int z){return x + y * z;};
  
  LinkCutTree <int> lct(f, g, f, 0, 0);
  vector< LinkCutTree<int>::Node * > A(N);
  for(int i=0;i<N;i++) A[i] = lct.make_node(i);

  for(int i=0;i<N-1;i++){
    int u, v;
    cin>>u>>v;
    lct.link(A[u], A[v]);
  }

  int Q;
  cin>>Q;
  int all = 0;
  while(Q--){
    string cmd;
    int u, v, x;
    cin>>cmd>>u>>v;

    if(cmd == "link") lct.link(A[u], A[v]);
    if(cmd == "cut")  {
      lct.evert(A[u]);
      lct.cut(A[v]);
    }
    if(cmd == "add") {
      cin>>x;
      lct.evert(A[u]);
      lct.set_propagate(A[v], x);
      all += x;
    }
    if(cmd == "sum"){
      lct.evert(A[u]);
      lct.expose(A[v]);
      int ans = A[v] -> sum - all;
      cout<<ans<<endl;
    }
  }  
  return 0;
}
