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
using Int = long long;
using _int = int;
using ll = long long;
using Double = long double;
const Int INF = (1LL<<60)+1e9; // ~ 1.15 * 1e18
const Int mod = (1e9)+7;
const Double EPS = 1e-8;
const Double PI = 6.0 * asin((Double)0.5);
using P = pair<Int,Int>;
template<class T> T Max(T &a,T b){return a=max(a,b);}
template<class T> T Min(T &a,T b){return a=min(a,b);}
template<class T1, class T2> ostream& operator<<(ostream& o,pair<T1,T2> p){return o<<"("<<p.first<<","<<p.second<<")";}
template<class T1, class T2, class T3> ostream& operator<<(ostream& o,tuple<T1,T2,T3> t){
  return o<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")";}
template<class T1, class T2> istream& operator>>(istream& i,pair<T1,T2> &p){return i>>p.first>>p.second;}
template<class T> ostream& operator<<(ostream& o,vector<T> a){Int i=0;for(T t:a)o<<(i++?" ":"")<<t;return o;}
template<class T> istream& operator>>(istream& i,vector<T> &a){for(T &t:a)i>>t;return i;}
//INSERT ABOVE HERE

class Rotation{
public:
  //時計回りに90度回転
  template <class T>
  static vector<T> rot90(const vector<T> &v){
    int h = v.size(), w = v[0].size();
    vector<T> res(w, T(h, 0));
    for(int i=0;i<h;i++)
      for(int j=0;j<w;j++) res[j][h-i-1] = v[i][j];
    return res;
  }

  //反時計回りに90度回転
  template <class T>
  static vector<T> rrot90(const vector<T> &v){
    int h = v.size(), w = v[0].size();
    vector<T> res(w, T(h, 0));
    for(int i=0;i<h;i++)
      for(int j=0;j<w;j++) res[w-1-j][i] = v[i][j];
    return res;
  }
};

signed main(){
  srand((unsigned)time(NULL));
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int h =5, w = 3;
  vector<vector<int> >a(h, vector<int>(w));
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++) a[i][j] = i * w + j;

  cout<<"start rot"<<endl;
  for(int k=0;k<4;k++){
    a = Rotation::rot90(a);
    swap(h, w);
    cout<<"--------"<<k<<"---------"<<endl;
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++) cout<<a[i][j]<<" ";
      cout<<endl;
    }
  }

  cout<<"start rrot"<<endl;
  for(int k=0;k<4;k++){
    a = Rotation::rrot90(a);
    swap(h, w);
    cout<<"--------"<<k<<"---------"<<endl;
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++) cout<<a[i][j]<<" ";
      cout<<endl;
    }
  }


  vector<string> b(h, string(w, '#'));
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++) b[i][j] = char(i * w + j + 'a');

  cout<<"start rot"<<endl;
  for(int k=0;k<4;k++){
    b = Rotation::rot90(b);
    swap(h, w);
    cout<<"--------"<<k<<"---------"<<endl;
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++) cout<<b[i][j]<<" ";
      cout<<endl;
    }
  }

  cout<<"start rrot"<<endl;
  for(int k=0;k<4;k++){
    b = Rotation::rrot90(b);
    swap(h, w);
    cout<<"--------"<<k<<"---------"<<endl;
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++) cout<<b[i][j]<<" ";
      cout<<endl;
    }
  }
  return 0;
}
