#include <bits/stdc++.h>
using namespace std;

template <int X/*文字の種類*/>
class Trie{
public:
  struct Node{
    char c;         //今の文字
    int pre;        //前の頂点番号
    int val;        //
    int exist;      //単語が存在するか
    vector<int> to; //次の頂点番号
    Node(){};
    Node(char c,int pre,int val=0,int exist=0):c(c),pre(pre),val(val),exist(exist),to(X,-1){};
  };
  
  vector<Node> v;
  function<int(char)> toI; //文字から数字に変換する関数
  
  Trie(function<int(char)> toI=[](char ch){return ch-'A';} ,char c = '$')
    :toI(toI){v.push_back(Node(c,-1,0/*!!!!!*/));};

  void Assert(int pos){assert(0 <= pos && pos<(int)v.size());}
  int go(int pos,char c){Assert(pos);return v[pos].to[toI(c)];}
  int go(const string &s,int pos = 0){
    for(char c:s){
      pos = go(pos,c);
      if(pos == -1) return -1;
    }
    return pos;
  }
  int back(int pos){Assert(pos);return v[pos].pre;}
  int getVal(int pos){Assert(pos);return v[pos].val;} //0だったら単語が存在しない。
  int exist(int pos){Assert(pos);return v[pos].exist;}
  
  void add(const string &s,int val = 1){
    int pos = 0;
    for(char c:s){
      if(go(pos,c) != -1){pos = go(pos,c);continue;}
      v.push_back(Node(c,pos));
      pos = v[pos].to[toI(c)] = v.size()-1;
    }
    v[pos].exist = 1;
    v[pos].val = max(v[pos].val, val);  //min,max,+ 臨機応変に変えて
  }
};

