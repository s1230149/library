#include <bits/stdc++.h>
using namespace std;
/*
  O(|S|)
  文字列Sが与えられた時、各i(1 <= i <= |S|)に対してS[i]から初めて何文字Sのprefixが一致しているかが求められる。
  例:
  aaabaaaab
  921034210
*/

class Zalgorithm{
public:
  int n;            // 文字列の長さ
  string S;         // 対象の文字列
  vector<int> A;    //
  int ok;           //build可能かどうか？buildしたかどうか
  Zalgorithm ():ok(false){}
  Zalgorithm (string S):n(S.size()), S(S), A(n), ok(true){build();}
  void build(string S){n = S.size(); this->S = S; A.clear(); A.resize(n); ok = true; build();}
  void build(){
    assert(ok);
    
    A[0] = S.size();
    int i = 1, cnt = 0;
    while(i < n){
      while(i + cnt < n && S[cnt] == S[i + cnt]) cnt++;
      A[i] = cnt;
      if(cnt == 0) { i++; continue;}
      int k = 1;
      while(i + k < n && k + A[k] < cnt) A[i + k] = A[k], k++;
      i += k; cnt -= k;
    }
  }
  int get(int i){assert(ok); return A[i];}
};

signed main(){
  srand((unsigned)time(NULL));
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);
  
  
  return 0;
}
