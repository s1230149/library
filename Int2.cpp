#include <bits/stdc++.h>
using namespace std;

/*未完成*/
class Int{
public:
  typedef long long ll;
  typedef vector<ll> vec;
  ll B = 1e3, K = 3;
  int sign; // 0 - positive, 1 - negative
  vec val; 
  Int():sign(0),val(1,0){}
  Int(const string num){*this = convert(num);}
  Int(int num){*this = convert(to_string(num));}
  Int(int sign,const vec &val):sign(sign),val(val){}
  
  Int convert(const string &s)const{
    if(s[0] == '0') return Int(0,{0});
    vec num;
    int n = (int)s.size() - (s[0] == '-');
    for(int i=0;i<(n-1)/K + 1;i++){
      int v = 0, t = 1, p = min(K, n - i*K);
      for(int j=1;j<=p; j++, t *= 10) v += t * (s[s.size() - i*K - j] - '0');
      num.push_back(v);
    }
    return Int(s[0] == '-', num);
  }
  
  string convert()const{
    if(size() == 1 && val[0] == 0) return "0";
    string res;
    if(sign == 1) res += '-';
    for(int i=val.size()-1;i>=0;i--){
      int v = val[i];
      res += v == 0? string(K,'0'): to_string(v);
    }
    return res;
  }
  
  void R(string &a){reverse(a.begin(),a.end());}
  bool neg(const Int &a)const{return a.sign == 1;}
  ll& operator [] (int i){assert(i<(int)val.size());return val[i];}
  const ll& operator [] (int i)const{assert(i<(int)val.size());return val[i];}
  void push_back(int a){return val.push_back(a);}
  ll& back(){return val.back();}
  void pop_back(){val.pop_back();}
  ll size()const{return val.size();}
  
  bool operator ==  (Int b) {return sign == b.sign && val == b.val;}
  template<class T> bool operator == (T b){return *this == Int(b);}
  
  bool operator !=  (Int b) {return sign != b.sign || val != b.val;}
  template<class T> bool operator != (T b){return *this != Int(b);}
  
  bool operator >=  (Int b) {return !(*this < b);}
  template<class T> bool operator >= (T b){return *this >= Int(b);}

  bool operator >   (Int b) {return *this >= b && *this != b;}
  template<class T> bool operator > (T b){return *this > Int(b);}
  
  bool operator <=  (Int b) {return *this<b || *this == b;}
  template<class T> bool operator <= (T b){return *this <= Int(b);}

  template<class T> bool operator < (T b){return *this < Int(b);}
 
  bool operator <   (Int b){
    const Int &a = *this;
    if(neg(a) != neg(b)) return neg(a)? 1:0;
    if(a.size() != b.size()) return !neg(a)? (a.size()<b.size()):(a.size()>b.size());
    for(int i=a.size()-1;i>=0;i--)if(a[i] != b[i]) return !neg(a)? a[i] < b[i]: a[i] > b[i];
    return 0;
  }
  
  Int operator + (Int b){
    Int a = *this;
    int fa = neg(a);
    int fb = neg(b);
    a.sign = b.sign = 0;
    if(a < b) swap(a,b),swap(fa,fb);
    if(fa == fb){
      a.push_back(0);
      for(int i=0;i<a.size()-1;i++){
        if(i < b.size()) a[i] += b[i];
        a[i+1] += a[i]/B;
        a[i] = a[i]%B;
      }
      if(a.size() > 1 && a.back() == 0) a.pop_back();
      if(a.size() > 1 && a.back() == 0) a.pop_back();
      if(a != 0) a.sign = fa;
    }
    else {
      for(int i=0;i<a.size();i++){
        if(i < b.size()) a[i] -= b[i];
        if(a[i] < 0) a[i]+=B, a[i+1]--; 
      }
      while(a.size() > 1 && a.back() == 0) a.pop_back();
      if(a != 0) a.sign = fa;
    }
    return a;
  }

  Int operator * (Int b){
    Int res;
    Int a = *this;
    int fa = neg(a);
    int fb = neg(b);
    a.sign = b.sign = 0;
    if(a.size() < b.size()) swap(a,b), swap(fa,fb);
    if(a == 0 || b == 0) return Int(0);
    
    for(int j=0;j<(int)b.size();j++)
      for(int i=0;i<(int)a.size();i++){
        if(i+j >= (int)res.size()) res.push_back(0);
        res[i+j] += a[i] * b[j];
      }
    for(int i=0; i <(int)res.size(); i++) {
      if(res[i]/B == 0) continue;
      if(i + 1 >= (int)res.size()) res.push_back(0);
      res[i+1] += res[i]/B, res[i]=res[i]%B;
    }
    
    if(fa != fb) res.sign = 1;
    return res;
  }

  Int div(Int b,int flg){
    assert(b != 0);
    Int a = *this;
    int fa = neg(a);
    int fb = neg(b);
    a.sign = b.sign = 0;
    Int mod(0);
    Int d;
    for(int i=(int)a.size()-1;i>=0;i--){
      mod = mod * B + a[i];
      while(mod >= b) mod -= b, d.back()+=1;
      if(i && d != 0) d.push_back(0);
    }
    reverse(d.val.begin(),d.val.end());
    if(flg == 0 && d != 0 && (fa != fb)) d.sign = 1;
    if(flg == 1 && mod != 0 && fa) mod.sign ^= 1;
    return flg==0? d:mod;
  }
  
  Int operator + (string b){return *this + convert(b);}
  template<class T> Int operator + (T b){return *this + Int(b);}
  
  Int operator * (string b){return *this * convert(b);}
  template<class T> Int operator * (T b){return *this * Int(b);}

  Int operator - (Int b){b.sign ^= 1;return *this + b;} 
  template<class T> Int operator - (T b){return *this - Int(b);}
  
  Int operator / (Int b){return div(b,0);}
  template<class T> Int operator / (T b){return *this / Int(b);}
  
  Int operator % (Int b){return div(b,1);}
  template<class T> Int operator % (T b){return *this % Int(b);}
  
  Int operator += (Int b){return *this = *this+b;}
  template<class T> Int operator += (T b){return *this += Int(b);}
  
  Int operator -= (Int b){return *this = *this-b;}
  template<class T> Int operator -= (T b){return *this -= Int(b);}
  
  Int operator *= (Int b){return *this = *this*b;}
  template<class T> Int operator *= (T b){return *this *= Int(b);}
  
  Int operator /= (Int b){return *this = *this/b;}
  template<class T> Int operator /= (T b){return *this /= Int(b);}
  
  Int operator %= (Int b){return *this=*this%b;}
  template<class T> Int operator %= (T b){return *this %= Int(b);}
  
  Int operator ++(){return *this += 1;}
  Int operator --(){return *this -= 1;}

#ifdef int
#undef int
#define eraseIntDefine
#endif
  Int operator ++(int){
    Int tmp = *this;
    *this += 1;
    return tmp;
  }
  
  Int operator --(int){
    Int tmp = *this;
    *this -= 1;
    return tmp;
  }
#ifdef eraseIntDefine
#define int long long
#endif

  friend ostream& operator << (ostream& os,const Int a){
    os<<a.convert();
    return os;
  }

  friend istream& operator >> (istream& is,Int &a){
    string num;
    is>>num;
    a = Int(num);
    return is;
  }
  friend string to_string(Int a){return a.convert();}
};


signed main(){
  Int a,b;
  cin>>a>>b;
  cout<<"a = "<<a<<" b = "<<b<<endl;
  cout<<to_string(a)<<" "<<to_string(b)<<endl;
  cout<<"a + b = "<<a+b<<endl;
  cout<<"a - b = "<<a-b<<endl;
  cout<<"a / b = "<<a/b<<endl;
  cout<<"a % b = "<<a%b<<endl;
  cout<<1%(-1000)<<endl;
  cout<<a++<<" "<<++b<<endl;

  #define int long long
  auto check=[&](int i,int j){
    cout<<i<<" "<<j<<endl;
    Int a(to_string(i));
    Int b(to_string(j));
    assert(to_string(a) == to_string(i));
    assert(to_string(b) == to_string(j));
    assert((i < j) == (a < b));
    assert((i <= j) == (a <= b));
    assert((i > j) == (a > b));
    assert((i >= j) == (a >= b));
    assert((i == j) == (a == b));
    assert((i != j) == (a != b));
    assert(to_string(i + j) == to_string(a + b));
    assert(to_string(i - j) == to_string(a - b));
    assert(to_string(i * j) == to_string(a * b));
    if(j == 0)return ;
    assert(to_string(i / j) == to_string(a / b));
    assert(to_string(i % j) == to_string(a % b));
  };

  srand((unsigned)time(NULL));
  while(1){
    int i = rand() - INT_MAX/2;
    int j = rand() - INT_MAX/2;
    check(i,j);
  }
  
  for(int i=-1000;i<1000;i++)
    for(int j=-1000;j<1000;j++) check(i,j);

  return 0;
}
