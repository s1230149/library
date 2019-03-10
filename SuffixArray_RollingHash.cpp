#include <bits/stdc++.h>
#include "RollingHash.cpp"
using namespace std;
/*
  文字列比較にローリングハッシュを使えるSuffixArray
  RollingHashが構築済みならO(log(文字列長) * log(文字列長))でlower,upper,countができる。
  RollingHashがmod演算のせいで遅いので、unsigned long longにしてmodをなくすと10倍近く早くなる。
*/

class SA{
public:
  string S;
  int n;
  vector<int> sa;
  RollingHash rh;
  
  SA():n(-1){}
  SA(string S):S(S),n(S.size()),sa(n), rh(S){  
    vector<int> rnk(n);
    vector<int> tmp(n);
    for(int i=0;i<n;i++) sa[i]=i;
    for(int i=0;i<n;i++) rnk[i] = S[i];
    
    //k文字についてソートされているところから、2k文字でソート
    for(int Len=1;Len<=n;Len*=2){
      
      //(rnk[i],rnk[i+k])と(rnk[j],rnk[j+k])を比較
      auto compare_sa=[&](const int &i,const int &j){
        if(rnk[i]!=rnk[j])return rnk[i]<rnk[j];
        int ri=i+Len<n?rnk[i+Len]:-1;
        int rj=j+Len<n?rnk[j+Len]:-1;
        return ri<rj;
      };
      
      sort(sa.begin(),sa.end(),compare_sa);

      //いったんtmpに次のランクを計算して、rnkに代入
      for(int i=1;i<n;i++)
        tmp[sa[i]] = tmp[sa[i-1]] + compare_sa(sa[i-1],sa[i]);
      rnk = tmp;
    }
  }

  int lower_bound(string T){
    assert(n >= 0);
    int L=-1,R=S.length();
    while(L+1<R){
      int M = (L+R)/2;
      S.compare(sa[M],T.size(),T)<0? L = M:R = M;
    }
    return R;
  }

  //rh2[l, r)の文字列に対してのクエリ
  int lower_bound(const RollingHash &rh2, int l,int r, int upper = 0){ 
    auto compare = [&](int X){
      int idx = sa[X];
      int n = S.size() - idx;
      int m = r - l;
      int len = rh.count(idx, rh2, l);
      if(len >= m) return 0;
      if(len >= n) return -1;
      if(len >= m) return 1;
      assert(S[idx + len] != rh2.s[l + len]);
      return (S[idx + len] < rh2.s[l + len]) ? -1:1;
    };
    
    assert(n >= 0);
    int L=-1, R=S.length();
    while(L+1<R){
      int M = (L+R)/2;
      if(upper) compare(M)<=0? L = M:R = M;
      else compare(M)<0? L = M:R = M;
    }
    return R;
  }

  int upper_bound(string T){return lower_bound(T+char('z'+ 1));}
  int upper_bound(const RollingHash &rh2, int l,int r){return lower_bound(rh2, l, r, 1);}
  
  int count(string T){return upper_bound(T) - lower_bound(T);};
  int count(const RollingHash &rh2, int l,int r){
    return upper_bound(rh2, l, r) - lower_bound(rh2, l, r);
  }
};


/*
int main(){
  string s;
  cin>>s;
  SA sa(s);
  
  int q;
  cin>>q;
  while(q--){
    string t;
    cin>>t;
    int ans = sa.count(t) != 0;
    printf("%d\n",ans);
  }
}
*/
