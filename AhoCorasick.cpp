#include <bits/stdc++.h>
using namespace std;

/* Aho Corasick */

template <int X /*文字の種類*/ >
class AhoCorasick{
public:
  struct Node{
    char c;          //頂点の文字
    int pre;         //親の頂点番号
    int val;         //重み
    int exist;       //単語が存在するか
    int dep;         //ノードの深さ
    int failEdge;    //パターンマッチに失敗した時に戻るノード
    vector<int> bto; //to[i] != -1?  (to[i]):(posからtoへのパターンマッチに失敗した時に戻るノード)
    vector<int> to;  //次の頂点番号
    Node(){};
    Node(char c,int pre,int val = 0,int exist = 0):
      c(c),pre(pre),val(val),exist(exist), to(X,-1){};
  };
  
  vector<Node> v;          //ノード
  function<int(char)> toI; //文字から数字に変換する関数
  int ok;
  
  AhoCorasick(function<int(char)> toI=[](char ch){return ch-'A';} ,char c = '$'/*根に用いる文字*/)
    :toI(toI),ok(false){v.push_back(Node(c, -1, 0/*!!!!!*/));}

  int size(){return v.size();}
  Node operator [](int i)const {return v[i];}
  
  inline void check(int pos){assert(0 <= pos && pos<size());}
  inline int go(int pos,char c, int flag = 0){check(pos);return flag == 0? v[pos].to[toI(c)]:v[pos].bto[toI(c)];}
  inline int go(const string &s,int pos = 0){
    for(char c:s){
      pos = go(pos,c);
      if(pos == -1) return -1;
    }
    return pos;
  }
  
  inline int back(int pos){check(pos);return v[pos].pre;}
  inline int getVal(int pos){check(pos);return v[pos].val;}
  inline int exist(int pos){check(pos);return v[pos].exist;}
  inline int failEdge(int pos){check(pos);assert(ok);return v[pos].failEdge;}
  inline int failEdge(int pos,char to){check(pos);assert(ok);return v[pos].bto[toI(to)];}
  inline int depth(int pos){check(pos);assert(ok);return v[pos].dep;}
  
  inline void addWord(const string &s,int val = 1){
    ok = false;
    int pos = 0, dep = 0;
    for(char c:s){
      v[pos].dep = dep++;
      if(go(pos,c) != -1){pos = go(pos,c);continue;}
      v.push_back(Node(c,pos));
      pos = v[pos].to[toI(c)] = v.size()-1;
    }
    v[pos].dep = dep;
    v[pos].exist = 1;
    v[pos].val = max(v[pos].val, val);  //min,max,+ 臨機応変に変えて
  }

  void build(){
    ok = 1;
    buildFailEdge();
    nextMatch.resize(size());
    for(int i=1;i<size();i++) nextMatch[i] = failEdge(i);
    nextMatch[0] = -1;
  }
  
  vector<int> nextMatch; //to[i] := ノードiを含めないノードiからみて最も単語長が長くなるノード
  //posから見て単語長が最も長くなるようなノードを返す。(pos自体が単語の場合はposを返す)
  int suffixMatch(int pos){
    if(pos == -1) return -1;
    if(exist(pos)) return pos;
    return nextMatch[pos] = suffixMatch(nextMatch[pos]);
  }
    
  //res[i]にはs[i]からmatchする単語の長さが入っている。
  vector<vector<int> > matchedIdx(const string &s){
    assert(exist(0) == 0); //空文字列が単語として存在する場合、たぶん壊れるので直す必要がある。
    assert(ok);
    int n = s.size();
    vector<vector<int> > res(n);
    
    for(int i=0, pos=0;i<n;i++){
      char ch = s[i];
      pos = go(pos, ch, true);
      int p = suffixMatch(pos);
      while(p != -1 && exist(p)){
	res[ i - depth(p) + 1].push_back(depth(p));
	p = suffixMatch(nextMatch[p]);
      }
    }
    return res;
  }
  
private:
  void buildFailEdge(){
    const int root = 0;
    queue<int> Q;
    Q.push(root);
    v[root].failEdge = root;
    for(int i=0;i<size();i++) v[i].bto = v[i].to;
    for(int i=0;i<X;i++) if(v[root].bto[i] == -1) v[root].bto[i] = root;
    
    while(!Q.empty()){
      int pos = Q.front(); Q.pop();
      
      for(int i=0;i<X;i++){
	int to = v[pos].to[i];
	if(to == -1) continue;
	Q.push(to);
	v[to].failEdge = (pos == root)? root:v[ v[pos].failEdge ].bto[i];
	for(int i=0;i<X;i++) if(v[to].bto[i] == -1) v[to].bto[i] = v[ v[to].failEdge ].bto[i];
      }
    }
  }
};


void check(){
  AhoCorasick <26> aho([](char ch){return ch - 'a';});
  aho.addWord("abcde");
  aho.addWord("bc");
  aho.addWord("bab");
  aho.addWord("d");
  aho.addWord("ab");
  aho.build();
  for(int i=0;i<aho.size();i++){
    //pr(i, aho[i].c, aho[i].failEdge);
  }

  string s = "abcdefgabab";
  auto Idx = aho.matchedIdx(s);
  //for(int i=0;i<(int)s.size();i++) pr(i, s[i], Idx[i]);
  
}

void AtCoder_joisc2010_dna(){
  auto func = [](char ch){
    if(ch == 'A') return 0;
    if(ch == 'T') return 1;
    if(ch == 'G') return 2;
    if(ch == 'C') return 3;
    assert(0);
    return -1;
  };
  AhoCorasick <4> aho(func);
  int n;
  cin>>n;
  string target;
  cin>>target;
  for(int i=0;i<n;i++){
    string s;
    cin>>s;
    aho.addWord(s);
  }
  aho.build();
  auto Idx = aho.matchedIdx(target);
  int len = target.size();
  const int INF = 1e9;
  vector<int> dp(len+1, INF);
  
  dp[0] = 0;
  for(int i=0;i<len;i++){
    if(dp[i] == INF) continue;
    for(int j = -20; j<=0 ;j++){
      int k = i + j;
      if(k < 0) continue;
      for(int l:Idx[k]){
	if(k + l - 1 <= i || k + l - 1 > len) continue;
	dp[k + l - 1] = min(dp[k + l - 1], dp[i] + 1);
      }
    }
  }
  cout<<dp[len-1]<<endl;
}

void AOJ_2863(){
  int n;
  cin>>n;
  AhoCorasick <26> aho([](char ch){return ch - 'a';});
  for(int i=0;i<n;i++){
    string s;
    cin>>s;
    aho.addWord(s);
  }
  aho.build();
  string t;
  cin>>t;  
  auto Idx = aho.matchedIdx(t);
  int len = t.size();
  vector<int> dp(len+1, 0);
  dp[0] = 1;
  const int mod = 1e9 + 7;
  for(int i=0;i<len;i++){
    for(int l:Idx[i]){
      dp[i+l] = (dp[i+l] + dp[i])%mod;
    }
  }
  int ans = dp[len];
  cout<<ans<<endl;
}


void AOJ_2212(){
 while(1){
    int h,w;
    cin>>h>>w;
    if(h == 0 && w == 0) return;
    vector<string> mp(h);
    for(int i=0;i<h;i++) cin>>mp[i];

    auto func = [](char ch){
      if(ch == 'U') return 0;
      if(ch == 'R') return 1;
      if(ch == 'D') return 2;
      if(ch == 'L') return 3;
      return -1;
    };
  
    AhoCorasick <4> aho(func);
  
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
      string s;
      cin>>s;
      aho.addWord(s);
    }
    aho.build();
    int sy, sx;
    for(int i=0;i<h;i++)
      for(int j=0;j<w;j++) if(mp[i][j] == 'S') sy = i, sx = j;

    auto bfs = [&]()->int{
      typedef tuple<int,int,int,string> T;
      queue<T> Q;
      Q.push(T(sy, sx, 0, ""));
      vector<vector<vector<int> > > D(h, vector<vector<int> > (w, vector<int>(aho.size(),-1)));
      D[sy][sx][0] = 0;
    
      string str = "URDL";
      int dy[] = {-1, 0, 1, 0};
      int dx[] = {0, 1, 0, -1};
      while(!Q.empty()){
	int y, x, pos;
	string his;
	tie(y, x, pos, his) = Q.front(); Q.pop();
	int cost = D[y][x][pos];
	if(aho.suffixMatch(pos) != -1) continue;
	if(mp[y][x] == 'G') return cost;


	for(int i=0;i<4;i++){
	  int ny = y + dy[i];
	  int nx = x + dx[i];
	  char dir = str[i];
	  if(ny < 0 || nx < 0 || ny >= h || nx >= w || mp[ny][nx] == '#') continue;
	  int to = aho.go(pos, dir);
	  if(to == -1) to = aho.failEdge(pos, dir);
	  if(D[ny][nx][to] != -1) continue;
	  D[ny][nx][to] = cost+1;
	  Q.push(T(ny, nx, to, his + dir));
	}
      }
      return -1;
    };

    int ans = bfs();
    cout<<ans<<endl;
  }
}


signed main(){
  //check();
  //AOJ_2212();
  //AOJ_2863();
  //AtCoder_joisc2010_dna();
  return 0;
}
