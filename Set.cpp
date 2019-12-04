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
#define prArr(a) {cerr<<(#a)<<"={";int i=0;for(auto t:(a))cerr<<(i++?", ":"")<<t;cerr<<"}"<<endl;}
using namespace std;
template<class T1, class T2> ostream& operator<<(ostream& o,pair<T1,T2> p){return o<<"("<<p.first<<","<<p.second<<")";}

/*
  平衡2分木で管理するset
  宣言　　　　　　　　　          (Set<型> A):          O(1)
  k番目に大きい要素を取得　　　    (A[i]):               O(logN)
  挿入　　                      (A.insert(val)):　　　 O(logN)
  削除　　　                    (A.erase(i)):　　　 　 O(logN)
  検索                         (A.find(i)):          O(logN)
*/

template<typename T>
class Set{
public:

  struct Node{
    T key;
    int priority;
    int size;
    Node *parent, *left, *right;
    Node *mleft, *mright; //もっとも左側の子孫と右側の子孫

    inline void refresh(){
      size = 1;
      mleft = mright = this;

      if(left != nullptr) {
        left->parent = this;
        size += left->size;
        mleft = (left->mleft != nullptr)? left->mleft:left;
      }

      if(right != nullptr){
        right->parent = this;
        size += right->size;
        mright = (right->mright != nullptr)?right->mright:right;
      }
    }

    Node* next(){
      Node *t = this;
      if(t->right != nullptr) return t->right->mleft;
      while(1){
        if(t->parent == nullptr) return nullptr;
        if(t->parent->left == t) return t->parent;
        t = t->parent;
      }
    }

    Node* prev(){
      Node *t = this;
      if(t->left != nullptr) return t->left->mright;
      while(1){
        if(t->parent == nullptr) return nullptr;
        if(t->parent->right == t) return t->parent;
        t = t->parent;
      }
    }

    Node():key(T()), priority(-1), parent(nullptr), left(nullptr), right(nullptr){refresh();};
    Node(const T &key,int priority, Node *parent):
      key(key), priority(priority), parent(parent), left(nullptr), right(nullptr){refresh();};

    Node(const T &key,int priority, Node *parent, Node *left, Node *right):
      key(key), priority(priority), parent(parent), left(left), right(right){refresh();};

  };

  mt19937 mt; //[0, 2^32]までのpriorityを決める乱数生成機
  Node *root;
  Set():mt((unsigned int) time(NULL)), root(nullptr){}

  int size(){return size(root);}
  int size(Node *t){return t == nullptr? 0:t->size;}
  int empty(){return size(root) == 0;}

  //next(t): 次接点(tの次に大きいノード)を返す (たぶんO(1))
  Node* next(Node *t){return t->next();}

  //prev(t): 前接点(tの次に小さいノード)を返す (たぶんO(1))
  Node* prev(Node *t){return t->prev();}

  //insert(key): keyが存在しなければ追加される、すでに存在すればなにもされない (O(logN))
  void insert(T key){root = insert(root, key, mt());}

  //erase(key): keyが存在すれば消す、しなければなにもしない (O(logN))
  void erase(T key){root = erase(root, key);}

  //count(key): keyの数を数える (O(logN))
  int count(T key){return find(root, key) != nullptr;}

  //find(key): keyが存在すればそのノードを返す 存在しなければnullptrを返す (O(logN))
  Node* find(T key){return find(root, key);}

  //lower_bound(key): 初めてkey以上になるノードを返す(なければnullptrを返す) (O(logN))
  Node* lower_bound(T key){return lower_bound(root, key);}

  //upper_bound(key): 初めてkeyより大きくなるノードを返す(なければnullptrを返す) (O(logN))
  Node* upper_bound(T key){return upper_bound(root, key);}

  //getKthNode(k): 昇順でk番目のノードを返す (O(logN))
  inline Node* getKthNode(int k){
    assert(0 <= k && k < size());
    k++;
    Node *t = root;
    while(size(t->left)+1 != k){
      if(size(t->left) >= k) t = t->left;
      else k -= size(t->left) + 1, t = t->right;
    }
    return t;
  }

  //[i]: 昇順でi番目の値を返す (O(logN))
  T operator[](int i){return getKthNode(i)->key;}

  //get(i): 昇順でi番目の値を返す (O(logN))
  T get(int i){return (*this)[i];}

  //get_inv(key): keyが木の中で何番目に大きいかを返す(0 origin)
  int get_inv(const T key){
    Node *t = root;
    int k = 0;
    while(t != nullptr){
      if(key < t->key) t = t->left;
      else if(key > t->key) k += size(t->left) + 1, t = t->right;
      else return k + size(t->left);
    }
    return k;
  }

private:
  Node* rightRotate(Node *y){
    Node *x = y->left;
    y->left = x->right;
    x->right = y;

    x->parent = y->parent;
    y->parent = x;

    y->refresh(), x->refresh();
    return x;
  }

  Node* leftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    y->parent = x->parent;
    x->parent = y;

    x->refresh(), y->refresh();
    return y;
  }

  Node* insert(Node *t, const T &key,const int priority, Node *parent = nullptr){
    if(t == nullptr) return new Node(key, priority, parent);
    if(key == t->key) return t;

    if(key < t->key){
      t->left = insert(t->left, key, priority,  t);
      if( t->priority < t->left->priority ) t = rightRotate(t);
    }
    else{
      t->right = insert(t->right, key, priority, t);
      if( t->priority < t->right->priority ) t = leftRotate(t);
    }
    t->refresh();
    return t;
  }


  Node* erase(Node *t,const T &key){
    if(t == nullptr) return nullptr;
    if(key == t->key) return _erase(t, key);
    if(key < t->key ) t->left = erase(t->left, key);
    else if(key > t->key ) t->right = erase(t->right, key);
    t->refresh();
    return t;
  }

  Node* _erase(Node *t,const T &key){
    if(t->left == nullptr && t->right == nullptr){delete t;return nullptr;}
    bool cmd; //0:leftRotate, 1:rightRotate
    if(t->left == nullptr) cmd = 0;
    else if(t->right == nullptr) cmd = 1;
    else cmd = t->left->priority > t->right->priority;
    t = cmd == 0? leftRotate(t):rightRotate(t);
    t->refresh();
    return erase(t, key);
  }

  Node* find(Node *t, const T &key){
    if(t == nullptr) return nullptr;
    if(key < t->key) return find(t->left, key);
    if(key > t->key) return find(t->right, key);
    return t;
  }

  Node* lower_bound(Node *t, const T &key){
    if(t == nullptr) return nullptr;
    if(key < t->key) {
      Node* s = lower_bound(t->left, key);
      return s == nullptr || (s->key < key)? t:s;
    }
    if(key > t->key) return lower_bound(t->right, key);
    return t;
  }

  Node* upper_bound(Node *t, const T &key){
    if(t == nullptr) return nullptr;
    if(key < t->key) {
      Node* s = upper_bound(t->left, key);
      return s == nullptr || (s->key <= key)? t:s;
    }
    if(key >= t->key) return upper_bound(t->right, key);
    return t;
  }

  friend ostream& operator << (ostream& os,Set<T> &a){
    for(int i=0;i<a.size();i++){
      if(i) os<<" ";
      os<<a[i];
    }
    return os;
  }
};


//ここから下は、性能チェック用のコード
class Time{
public:
  chrono::system_clock::time_point start;
  Time(){reset();}
  void reset(){start = now();}
  chrono::system_clock::time_point now(){return chrono::system_clock::now();}
  double time(){return chrono::duration_cast<chrono::milliseconds>(now()-start).count();}
};

class Rand{
public:
  typedef long long ll;
  random_device rnd;//毎回異なる乱数
  mt19937_64 mt; //unsigned 64bitメルセンヌ_ツイスタ [0, 2^66]
  //mt19937 mt; //unsigned 32bitメルセンヌ_ツイスタ [0, 2^32]

  Rand():mt(rnd()){}
  //Rand():mt((unsigned int)time(NULL)){};

  ll get(){return mt()>>1;} //[0, (2^63)-1]
  ll get(ll l,ll r){ //[l, r]
    assert(l <= r);
    return l + get() % (r - l + 1);
  }
};


//時間計測
void test1(){
  Rand rand;
  //using T = pair<int, int>;
  //auto get=[&](){return T(rand.get(), rand.get());};
  using T = int;
  auto get=[&](){return (int)rand.get();};

  Set<T> A;
  { //insert time
    Time timer;
    const int num = 2000000;
    for(int i=0;i<num;i++) A.insert(get());
    cout<<num<<" times insertion time = "<<timer.time()<<endl;
  }

  const int N = A.size();
  int a, b, c;
  { //random access time
    Time timer;
    int cnt = 0;
    for(int i=0;i<N-1;i++) cnt += A[i] < A[i+1];
    a = cnt;
    cout<<2 * N<<" times random access time= "<<timer.time()<<endl;
  }

  { //next()
    Time timer;
    int cnt = 0;
    auto t = A.getKthNode(0);
    for(int i=0; i<N-1; i++, t = t->next()) cnt += t->key < t->next()->key;
    cout<<2 * N<<" times increment cursor time= "<<timer.time()<<endl;
    b = cnt;
  }

  { //prev()
    Time timer;
    int cnt = 0;
    auto t = A.getKthNode(N-1);
    for(int i=0; i<N-1; i++, t = t->prev()) cnt += t->key > t->prev()->key;
    cout<<2 * N<<" times decrement cursor time= "<<timer.time()<<endl;
    c = cnt;
  }

  assert(a == b && b  == c);
  { //erase()
    vector<T> B(A.size());
    for(int i=0;i<A.size();i++) B[i] = A[i];
    random_shuffle(B.begin(), B.end());
    Time timer;
    for(T b:B) A.erase(b);
    cout<<N<<" times erasing time = "<<timer.time()<<endl;
  }
}

//動作確認
void test2(){
  Rand rand;
  using T = pair<int, int>;
  auto get=[&](){return T(rand.get(-1000, 1000), rand.get(-1000, 1000));};
  //using T = int;
  //auto get=[&](){return rand.get(-1000, 1000);};
  vector<T> A;
  Set<T> B;

  auto printTree=[&](){
    cout<<"print Tree"<<endl;
    int N = B.size();
    for(int i=0;i<N;i++){
      auto t = B.lower_bound(B[i]);
      assert(t->key == B[i]);
      if(t->left != nullptr) cout<<(t->key)<<" left "<<(t->left->key)<<endl;
      if(t->right != nullptr) cout<<(t->key)<<" right "<<(t->right->key)<<endl;
    }
  };

  auto insert=[&](T v){
    A.push_back(v);
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    B.insert(v);
  };

  auto erase_random=[&](){
    if((int)A.size() == 0) return;
    int idx = random()%A.size();
    T v = A[idx];
    A.erase(A.begin() + idx);
    B.erase(v);
  };

  auto count_random=[&](){
    T v = get();
    if(!A.empty() && random()%2){
      int idx = random()%A.size();
      v = A[idx];
    }
    auto a = count(A.begin(), A.end(), v);
    auto b = B.count(v);
    assert(a == b);
  };

  auto lower_upper_random=[&](){
    T v = get();
    {
      auto p = lower_bound(A.begin(), A.end(), v);
      auto q = B.lower_bound(v);
      if(p == A.end()) assert(q == nullptr);
      else assert(*p == q->key);
    }
    {
      auto p = upper_bound(A.begin(), A.end(), v);
      auto q = B.upper_bound(v);
      if(p == A.end()) assert(q == nullptr);
      else assert(*p == q->key);
    }
  };

  auto same = [&](){
    assert((int)A.size() == B.size());
    int N = A.size();
    for(int i=0;i<N;i++) assert(A[i] == B[i]);
  };

  auto get_inv=[&](){
    int N = B.size();
    for(int i=0;i<N;i++) assert(B.get_inv(B[i]) == i);

    T v = get();
    int a = lower_bound(A.begin(), A.end(), v) - A.begin();
    int b = B.get_inv(v);
    assert(a == b);
  };

  auto next_prev=[&](){
    int N = B.size();
    //pr(B);
    for(int i=0;i<N-1;i++){
      auto p = B.getKthNode(i);
      assert(p->next()->key == A[i+1]);
      assert(B.next(p)->key == A[i+1]);
    }

    for(int i=0;i<N-1;i++){
      auto p = B.getKthNode(N - i - 1);

      assert(p->prev()->key == A[N - i - 2]);
      assert(B.prev(p)->key == A[N - i - 2]);
    }
  };

  auto print = [&](){
    prArr(A);
    pr(B);
  };

  int num_test = 0;
  Time timer;
  while(num_test++ <= 100000){
    if(num_test%10000 == 0) {
      cout<<"num_test="<<num_test<<"\tsize="<<A.size()<<"\ttime:"<<timer.time()<<"ms"<<endl;
    }
    int cmd = random()%5;
    if(cmd <= 2) insert(get());
    else if(cmd <= 4) erase_random();
    //print();
    count_random();
    lower_upper_random();
    get_inv();
    next_prev();
    same();
  }
}

signed main(){
  srand((unsigned)time(NULL));
  test1();
  test2();
  return 0;
}
