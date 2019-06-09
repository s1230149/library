#include <bits/stdc++.h>
using namespace std;

class Int{
public:
  string val;
  Int():val("0"){}
  Int(string num,bool reversed=0){if(!reversed)R(num); val = num;}
  Int(long long num){val = to_string(num); R(val);}
  
  void R(string &a){reverse(a.begin(),a.end());}
  bool neg(const string &a)const{return a.back() == '-';}
  char& operator [] (int i){assert(i<(int)val.size());return val[i];}

  bool operator ==  (Int b) {R(b.val); return *this == b.val;}
  bool operator ==  (string b) {R(b);return val == b;}
  template<class T> bool operator == (T b){return *this == Int(b);}
  
  bool operator !=  (Int b) {R(b.val); return *this != b.val;}
  bool operator !=  (string b) {R(b);return !(val == b);}
  template<class T> bool operator != (T b){return *this != Int(b);}
  
  bool operator >=  (Int b) {R(b.val); return *this >= b.val;}
  bool operator >=  (string b) {return !(*this < b);}
  template<class T> bool operator >= (T b){return *this >= Int(b);}

  bool operator >   (Int b) {R(b.val); return *this > b.val;}
  bool operator >   (string b) {return *this>=b && *this != b;}
  template<class T> bool operator > (T b){return *this > Int(b);}

  bool operator <=  (Int b) {R(b.val); return *this <= b.val;}
  bool operator <=  (string b) {return *this<b || *this == b;}
  template<class T> bool operator <= (T b){return *this <= Int(b);}

  bool operator <   (Int b) {R(b.val); return *this < b.val;}
  template<class T> bool operator < (T b){return *this < Int(b);}
 
   bool operator <   (string b) {
    R(b);
    const string &a = val;
    if(neg(a) != neg(b)) return neg(a)? 1:0;
    if(a.size() != b.size()) return !neg(a)? (a.size()<b.size()):(a.size()>b.size());
    for(int i=a.size()-1;i>=0;i--)if(a[i] != b[i]) return !neg(a)? a[i] < b[i]: a[i] > b[i];
    return 0;
  }
  
  Int operator + (string b){
    R(b);
    string a = val;
    string fa = neg(a)? "-":"";
    string fb = neg(b)? "-":"";
    if(neg(a)) a.pop_back();
    if(neg(b)) b.pop_back();
    if(Int(a,1) < Int(b,1)) swap(a,b),swap(fa,fb);
    
    if(fa == fb){
      a += '0';
      for(int i=0;i<(int)a.size()-1;i++){
        if(i < (int)b.size()) a[i] += b[i]-'0';
        a[i+1] += (a[i]-'0')/10;
        a[i] = (a[i]-'0')%10 + '0';
      }
      if(a.size() > 1 && a.back() == '0') a.pop_back();
      if((int)a.size() > 1 && a.back() == '0') a.pop_back();
      if(a != "0") a += fa;
    }
    else {
      for(int i=0;i<(int)a.size();i++){
        if(i < (int)b.size()) a[i] -= b[i]-'0';
        if(a[i]-'0' < 0) a[i]+=10, a[i+1]--; 
      }
      while((int)a.size()>1 && a.back() == '0') a.pop_back();
      if(a != "0") a += fa;
    }
    return Int(a,1);
  }

  Int operator * (string b){
    R(b);
    vector<int> res;
    string a = val;
    string fa = neg(a)? "-":"";
    string fb = neg(b)? "-":"";
    if(neg(a)) a.pop_back();
    if(neg(b)) b.pop_back();
    if(a.size() < b.size()) swap(a,b), swap(fa,fb);
    if(a == "0" || b == "0") return Int("0");
    
    for(int j=0;j<(int)b.size();j++)
      for(int i=0;i<(int)a.size();i++){
        if(i+j >= (int)res.size()) res.push_back(0);
        res[i+j] += (a[i]-'0') * (b[j]-'0');
      }
    for(int i=0; i <(int)res.size(); i++) {
      if(res[i]/10 == 0) continue;
      if(i + 1 >= (int)res.size()) res.push_back(0);
      res[i+1] += res[i]/10, res[i]=res[i]%10;
    }
    string sres;
    for(int i:res) sres += char(i + '0');
    if(fa != fb) sres += '-';
    return Int(sres,1);
  }

  Int div(string b,int flg){
    assert(b != "0");
    string a = val;
    string fa = neg(a)? "-":"";
    string fb = b[0]=='-'? "-":"";
    if(neg(a)) a.pop_back();
    if(b[0]=='-') b.erase(b.begin());
    Int mod("0");
    string d="0";
    for(int i=(int)a.size()-1;i>=0;i--){
      mod = mod * 10 + (a[i] - '0');
      while(mod >= b) mod -= b, d.back()+=1;
      if(i && d != "0") d += '0'; 
    }
    if(flg == 0 && d != "0" && (fa != fb)) d = "-" + d;
    if(flg == 1 && mod != "0" && (fa == "-")) mod *= -1;
    return flg==0? d:mod;
  }
  
  Int operator + (Int b){R(b.val); return *this + b.val;}
  template<class T> Int operator + (T b){return *this + Int(b);}
  
  Int operator * (Int b){R(b.val); return *this * b.val;}
  template<class T> Int operator * (T b){return *this * Int(b);}

  Int operator - (string b){b = (b[0] == '-')? b.substr(1):"-" + b;return *this + b;}
  Int operator - (Int b){R(b.val); return *this - b.val;} 
  template<class T> Int operator - (T b){return *this - Int(b);}
  
  Int operator / (string b){return div(b,0);}
  Int operator / (Int b){R(b.val);return div(b.val,0);}
  template<class T> Int operator / (T b){return *this / Int(b);}
  
  Int operator % (string b){return div(b,1);}
  Int operator % (Int b){R(b.val);return div(b.val,1);}
  template<class T> Int operator % (T b){return *this % Int(b);}
  
  Int operator += (Int b){return *this = *this+b;}
  Int operator += (string b){return *this = *this+b;}
  template<class T> Int operator += (T b){return *this += Int(b);}
  
  Int operator -= (Int b){return *this = *this-b;}
  Int operator -= (string b){return *this = *this-b;}
  template<class T> Int operator -= (T b){return *this -= Int(b);}
  
  Int operator *= (Int b){return *this = *this*b;}
  Int operator *= (string b){return *this = *this*b;}
  template<class T> Int operator *= (T b){return *this *= Int(b);}
  
  Int operator /= (string b){return *this = *this/b;}
  Int operator /= (Int b){return *this = *this/b;}
  template<class T> Int operator /= (T b){return *this /= Int(b);}
  
  Int operator %= (string b){return *this = *this % b;}
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
    for(int i=(int)a.val.size()-1;i>=0;i--) os<<a.val[i];
    return os;
  }

  friend istream& operator >> (istream& is,Int &a){
    string num;
    is>>num;
    a = Int(num);
    return is;
  }
  friend string to_string(Int a){reverse(a.val.begin(),a.val.end());return a.val;}
};

signed main(){
  Int a,b;
  cin>>a>>b;
  cout<<a<<" "<<b<<endl;
  cout<<to_string(a)<<" "<<to_string(b)<<endl;
  cout<<a%b<<endl;
  cout<<1%(-1000)<<endl;
  cout<<a++<<" "<<++b<<endl;
  
  for(int i=-1000;i<1000;i++)
    for(int j=-1000;j<1000;j++){
      cout<<i<<" "<<j<<endl;
      Int a(to_string(i));
      Int b(to_string(j));
      assert((i < j) == (a < b));
      assert((i <= j) == (a <= b));
      assert((i > j) == (a > b));
      assert((i >= j) == (a >= b));
      assert((i == j) == (a == b));
      assert((i != j) == (a != b));
      assert(to_string(i + j) == to_string(a + b));
      assert(to_string(i - j) == to_string(a - b));
      assert(to_string(i * j) == to_string(a * b));
      if(j == 0)continue;
      assert(to_string(i / j) == to_string(a / b));
      assert(to_string(i % j) == to_string(a % b));
    }
  return 0;
}
