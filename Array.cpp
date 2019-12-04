#include <bits/stdc++.h>
using namespace std;
//INSERT ABOVE HERE

/*
  平衡2分木で実装された配列。
  宣言　　　　　　　　　(Array<型> A(N, 初期値)):  O(NlogN)
  ランダムアクセス　　　(A[i]):                 　O(logN)
  任意の位置への挿入　　(A.insert(i, val)):　　　 O(logN)
  任意の位置の削除　　　(A.erase(i)):　　　　　 　 O(logN)
*/

template<typename T>
class Array{
public:
  struct Node{
    T val;
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

    Node():val(T()), priority(-1), parent(nullptr), left(nullptr), right(nullptr){refresh();};
    Node(const T &val,int priority,Node *parent):
      val(val), priority(priority), parent(parent), left(nullptr), right(nullptr){refresh();};

    Node(const T &val,int priority, Node *parent,Node *left,Node *right):
      val(val), priority(priority), parent(parent), left(left), right(right){refresh();};
  };

  mt19937 mt; //[0, 2^32]までのpriorityを決める乱数生成機
  Node *root;
  Array():mt((unsigned int) time(NULL)), root(nullptr){}
  Array(int n, T val = T()):mt((unsigned int) time(NULL)), root(nullptr){
    for(int i=0;i<n;i++) push_back(val);
  }

  inline int size(){return size(root);}
  inline int size(Node *t){return t == nullptr? 0:t->size;}
  inline int empty(){return size(root) == 0;}

  //next(t): 次接点(tの次のノード)を返す (たぶんO(1))
  Node* next(Node *t){return t->next();}

  //prev(t): 前接点(tの次のノード)を返す (たぶんO(1))
  Node* prev(Node *t){return t->prev();}

  //k番目の位置にvalを挿入 (O(logN))
  inline void insert(int k, T val){assert(0 <= k && k <= size()); root = insert(root, k, val, nullptr);}
  inline void push_back(T val){return insert(size(), val);}
  inline void push_front(T val){return insert(0, val);}

  //k番目の位置の要素を削除 (O(logN))
  inline void erase(int k){assert(0 <= k && k < size()); root = erase(root, k + 1);}
  inline void pop_front(){erase(0);}
  inline void pop_back(){erase(size()-1);}

  //k番目の位置のノードを得る (O(logN))
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
  T& operator[](int i){return getKthNode(i)->val;}

private:
  inline Node* rightRotate(Node *y){
    Node *x = y->left;
    y->left = x->right;
    x->right = y;

    x->parent = y->parent;
    y->parent = x;

    y->refresh(), x->refresh();
    return x;
  }

  inline Node* leftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    y->parent = x->parent;
    x->parent = y;

    x->refresh(), y->refresh();
    return y;
  }

  Node* insert(Node *t, int k, const T &val, Node *parent){
    if(t == nullptr) return new Node(val, mt(), parent);

    if(size(t->left) >= k){
      t->left = insert(t->left, k, val,  t);
      if( t->priority < t->left->priority ) t = rightRotate(t);
    }
    else{
      t->right = insert(t->right, k - size(t->left) - 1, val, t);
      if( t->priority < t->right->priority ) t = leftRotate(t);
    }
    t->refresh();
    return t;
  }

  Node* erase(Node *t,int k){
    int num = size(t->left) + 1;
    if(num == k) return _erase(t, k);
    if(k < num) t->left = erase(t->left, k);
    else t->right = erase(t->right, k - num);
    t->refresh();
    return t;
  }

  Node* _erase(Node *t, int k){
    if(t->left == nullptr && t->right == nullptr){delete t; return nullptr;}
    bool cmd; //0:leftRotate, 1:rightRotate
    if(t->left == nullptr) cmd = 0;
    else if(t->right == nullptr) cmd = 1;
    else cmd = t->left->priority > t->right->priority;
    t = cmd == 0? leftRotate(t):rightRotate(t);
    t->refresh();
    return erase(t, k);
  }

  /*
    int lower_bound(Node *t, int a, int b, int l, int r, T val){
    }
  */


  friend ostream& operator << (ostream& os,Array<T> &a){
    for(int i=0;i<a.size();i++){
      if(i) os<<" ";
      os<<a[i];
    }
    os<<endl;
    return os;
  }

  friend istream& operator >> (istream& is,Array<T> &a){
    for(int i=0;i<a.size();i++) is>>a[i];
    return is;
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

void test_performance(){
  Rand rand;
  using T = pair<int, int>;
  auto get=[&](){return T(rand.get(), rand.get());};
  //using T = int;
  //auto get=[&](){return (int)rand.get();};

  int n = 200000;
  int m = 1000000;
  vector<int> cmd(m);
  {
    int l = random()%m;
    int r = m - l;
    for(int i=0;i<l;i++) cmd.push_back(0); //erase
    for(int i=0;i<r;i++) cmd.push_back(1); //insert
    shuffle(cmd.begin(), cmd.end(), mt19937_64());
  }
  {
    Time timer;
    Array<T> A(n);
    for(int i=0;i<m;i++){
      if(A.size() == 0 && cmd[i] == 0) continue;
      if(cmd[i] == 0){
          int k = A.size()/2;
          A.erase(k);
      }
      if(cmd[i] == 1){
        int k = A.size()/2;
        A.insert(k, get());
      }
    }
    cout<<"Array time: "<<timer.time()<<"ms"<<endl;
  }
  {
    Time timer;
    vector<T> A(n);
    for(int i=0;i<m;i++){
      if(A.size() == 0 && cmd[i] == 0) continue;
      if(cmd[i] == 0){
        int k = A.size()/2;
        A.erase(A.begin() + k);
      }
      if(cmd[i] == 1){
        int k = A.size()/2;
        A.insert(A.begin() + k, get());
      }
    }
    cout<<"vector time: "<<timer.time()<<"ms"<<endl;
  }
}

void test_functions(){
  Rand rand;
  using T = pair<int, int>;
  auto get=[&](){return T(rand.get(), rand.get());};
  //using T = int;
  //auto get=[&](){return (int)rand.get();};

  auto same=[&](vector<T> &A, Array<T> &B){
    assert((int)A.size() == B.size());
    int n = A.size();
    for(int i=0;i<n;i++) assert(A[i] == B[i]);
  };

  auto next_prev=[&](Array<T> &B){
    int N = B.size();
    for(int i=0;i<N-1;i++){
      auto p = B.getKthNode(i);
      assert(p->next()->val == B[i+1]);
      assert(B.next(p)->val == B[i+1]);
    }

    for(int i=0;i<N-1;i++){
      auto p = B.getKthNode(N - i - 1);
      assert(p->prev()->val == B[N - i - 2]);
      assert(B.prev(p)->val == B[N - i - 2]);
    }
  };


  int num_test = 0;
  while(1){
    if(++num_test % 10 == 0) cout<<"test "<<num_test<<endl;
    const int n = random()%1000;
    const T init_val = get();
    vector<T> A(n, init_val);
    Array<T> B(n, init_val);

    const int m = 10000; //テスト回数
    vector<int> cmd(m);
    {
      int l = random()%m;
      int r = m - l;
      for(int i=0;i<l;i++) cmd.push_back(0); //erase
      for(int i=0;i<r;i++) cmd.push_back(1); //insert
      shuffle(cmd.begin(), cmd.end(), mt19937_64());
    }

    for(int i=0;i<m;i++){
      if(A.size() == 0 && cmd[i] == 0) continue;
      if(cmd[i] == 0){
        int k = random()%A.size();
        A.erase(A.begin() + k);
        B.erase(k);
      }
      if(cmd[i] == 1){
        int k = random()%(A.size() + 1);
        T val = get();
        A.insert(A.begin() + k, val);
        B.insert(k, val);
      }
      same(A, B);
      next_prev(B);
    }
  }
}

signed main(){
  test_performance();
  test_functions();
  return 0;
}
