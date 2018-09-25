#include <bits/stdc++.h>
#define GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME
#define pr(...) cerr<< GET_MACRO(__VA_ARGS__,pr6,pr5,pr4,pr3,pr2,pr1)(__VA_ARGS__) <<endl
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
using ll = long long;
using Double = long double;
const Int INF = 1LL<<55;
const Int mod = (1e9)+7;
using P = pair<Int,Int>;
using T = tuple<Int,Int,Int>;
const Double EPS = 1e-8;
const Double PI = 6.0 * asin((Double)0.5);
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}
ostream& operator<<(ostream& o,P p){return o<<"("<<p.first<<","<<p.second<<")";}
ostream& operator<<(ostream& o,T t){return o<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")";}
istream& operator>>(istream& i,P &p){return i>>p.first>>p.second;}
ostream& operator<<(ostream& o,vector<auto> &a){Int i=0;for(auto t:a)o<<(i++?" ":"")<<t;return o;}
istream& operator>>(istream& i,vector<auto> &a){for(auto &t:a)i>>t;return i;}
void prArr(auto a,string s=" "){Int i=0;for(auto t:a)cout<<(i++?s:"")<<t;cout<<endl;}


class Treap{
public:
  struct Node{
    int key;
    int priority;
    int size;
    Node *parent, *left, *right;

    void refresh(){
      size = 1;
      if(left != nullptr) size += left->size;
      if(right != nullptr) size += right->size;
    }
    
    Node():key(-1), priority(-1), parent(nullptr), left(nullptr), right(nullptr){refresh();};
    Node(int key,int priority,Node *parent):
      key(key), priority(priority), parent(parent), left(nullptr), right(nullptr){refresh();};

    Node(int key,int priority, Node *parent,Node *left,Node *right):
      key(key), priority(priority), parent(parent), left(left), right(right){refresh();};
  };
  
  int n;
  Node *root;
  Treap():n(0){}
  int size(){return n;}
  int size(Node *t){return t == nullptr? 0:t->size;}
  int empty(){return n == 0;}
  
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

  Node* insert(Node *t,int key,int priority, Node *parent = nullptr){
    if(t == nullptr){n++; return new Node(key, priority, parent);}
    
    if(key == t->key) return t;
    
    if(key < t->key){
      t->left = insert(t->left, key, priority,  t);
      if( t->priority < t->left->priority ) t = rightRotate(t);
    }
    else{
      t->right = insert(t->right, key, priority, t);
      if( t->priority < t->right->priority ) t = leftRotate(t);
    }
    return t;
  }

  Node* insert(int key,int priority){
    if(n == 0){n++; return root = new Node(key, priority, nullptr);}
    return root = insert(root, key, priority);
  }

  Node* erase(Node *t,int key){
    if( t == nullptr) return nullptr;
    if(key == t->key) return _erase(t, key);
    
    if(key < t->key ) t->left = erase(t->left, key);
    else if(key > t->key ) t->right = erase(t->right, key);
    return t;
  }
  
  Node* _erase(Node *t,int key){
    if(t->left == nullptr && t->right == nullptr) {
      n--;
      delete t;
      return nullptr;
    }
    
    if(t->left == nullptr) t = leftRotate(t);
    else if(t->right == nullptr) t = rightRotate(t);
    else {
      if( t->left->priority > t->right->priority ) t = rightRotate(t);
      else t = leftRotate(t);
    }
    
    return erase(t, key);
  }

  void erase(int key){root = erase(root, key);}

  Node* find(Node *t,int key){
    if( t == nullptr) return nullptr;
    if(key < t->key ) return find(t->left, key);
    if(key > t->key ) return find(t->right, key);
    return t;
  }

  Node* find(int key){return find(root, key);}

  Node* getKthNode(Node *t, int K){
    if(K == 0) return t;
    if(size(t->left) <= K) return getKthNode(t->left, K);
    return getKthNode(t->right, K - size(t->left)+1);
  }

  Node* getKthNode(int K){
    assert(K < n);
    return getKthNode(root, K);
  }
  
  void print(Node* t,int a=0,int b=0,int c=0){
    if(t == nullptr) return;
    if(a) cout<<" "<<(t->key);
    if(t->left != nullptr) print(t->left, a, b, c);
    if(b) cout<<" "<<(t->key);
    
    if(t->right != nullptr) print(t->right, a, b, c);
    if(c) cout<<" "<<(t->key);
  }
  
  void print(){
    print(root, 0, 1, 0);cout<<endl;
    print(root, 1, 0, 0);cout<<endl;
  }
    
};

signed main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);
  
  Treap T;
  
  int n;
  cin>>n;
  while(n--){
    string str;
    cin>>str;
    if(str == "insert"){
      int key, priority;
      cin>>key>>priority;
      T.insert(key, priority);
    }
    
    if(str == "find"){
      int key;
      cin>>key;
      int ans = T.find(key) != nullptr;
      cout<<(ans?"yes":"no")<<endl;
    }
    
    if(str == "delete"){
      int key;
      cin>>key;
      T.erase(key);
    }
    if(str == "print"){
      T.print();
    }
  }
  
  return 0;
}
