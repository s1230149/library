#include <bits/stdc++.h>
using namespace std;

const int TOP = 0,FRONT = 1,LEFT = 3, RIGHT = 2,BACK = 4,BOTTOM = 5;
class Dice{
public:
  int TOP = 0,FRONT = 1,LEFT = 3, RIGHT = 2,BACK = 4,BOTTOM = 5;
  vector<int> val;
  Dice():val(6){for(int i=0;i<6;i++) val[i] = i;}
  Dice(int val[6]){for(int i=0;i<6;i++) this->val[i] = val[i];}
  Dice(vector<int> val):val(val){assert(val.size() == 6);}
  int& operator [](int a){return val[a];}
  bool operator == (Dice a)const{
    for(int i=0;i<6;(i%2? a.rotN():a.rotE()),i++)
      for(int j=0;j<4;j++){
        if(val == a.val) return 1;
        a.rotCW();
      }
    return 0;
  }

  void rot(string s){
    if(s == "N" || s == "B") rotN();
    else if(s == "S" || s == "F") rotS();
    else if(s == "E" || s == "R") rotE();
    else if(s == "W" || s == "L") rotW();
    else if(s == "CW") rotCW();
    else if(s == "CCW") rotCCW();
    else assert(!"rot error"); /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  }

  
  void rot(char ch){rot(string(1,ch));}
  
  //奥に転がす
  void rotN(){
    swap(val[TOP],val[FRONT]);
    swap(val[FRONT],val[BOTTOM]);
    swap(val[BOTTOM],val[BACK]);
  }

  //手前に転がす
  void rotS(){
    //rotN(),rotN(),rotN();
    swap(val[TOP],val[BACK]);
    swap(val[BACK],val[BOTTOM]);
    swap(val[BOTTOM],val[FRONT]);
  }
  
  //右に転がす
  void rotE(){
    swap(val[TOP],val[LEFT]);
    swap(val[LEFT],val[BOTTOM]);
    swap(val[BOTTOM],val[RIGHT]);
  }

  //左に転がす
  void rotW(){
    //rotE(),rotE(),rotE();
    swap(val[TOP],val[RIGHT]);
    swap(val[RIGHT],val[BOTTOM]);
    swap(val[BOTTOM],val[LEFT]);
  }

  //上から見て時計回りに回す
  void rotCW(){
    swap(val[FRONT],val[RIGHT]);
    swap(val[RIGHT],val[BACK]);
    swap(val[BACK],val[LEFT]);
  }

  //上からみて反時計回りに回す。
  void rotCCW(){
    //rotCW(),rotCW(),rotCW();
    swap(val[FRONT],val[LEFT]);
    swap(val[LEFT],val[BACK]);
    swap(val[BACK],val[RIGHT]);
  }

  void init(int top,int front){
    for(int i=0;i<6;(i%2? rotN():rotE()),i++)
      for(int j=0;j<4;j++){
        if(val[TOP] == top && val[FRONT] == front) return;
        rotCW();
      }
    assert(!"init error");
  }
};

int main(){
  int n;
  cin>>n;
  vector<Dice> A(n);
  for(int i=0;i<n;i++)
    for(int j=0;j<6;j++) cin>>A[i][j];
                           
  int ans = 1;
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(A[i] == A[j]) ans = 0;
  
  cout<<(ans? "Yes":"No")<<endl;
  return 0;
}
