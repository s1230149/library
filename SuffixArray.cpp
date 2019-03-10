#include <bits/stdc++.h>
using namespace std;

class SA{
public:
  string S;
  int n;
  vector<int> sa;
  
  SA():n(-1){}
  SA(string S):S(S),n(S.size()),sa(n){  
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

  int upper_bound(string T){return lower_bound(T+char('z'+ 1));} 
  int count(string T){return upper_bound(T) - lower_bound(T);};
};

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
