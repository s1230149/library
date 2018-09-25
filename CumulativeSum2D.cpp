#include <bits/stdc++.h>
using namespace std;

class CumulativeSum2D{
public:
  int h,w;
  vector<vector<int> > sum;
  CumulativeSum2D(){}
  CumulativeSum2D(vector<vector<int> > A){
    assert(A.size());
    h = A.size();
    w = A[0].size();
    sum.resize(h+1,vector<int>(w+1));
    for(int i=1;i<=h;i++)
      for(int j=1;j<=w;j++) sum[i][j] += sum[i][j-1] + A[i-1][j-1];

    for(int j=1;j<=w;j++)
      for(int i=1;i<=h;i++) sum[i][j] += sum[i-1][j];
    
  }
  
  //半開区間
  int get(int x,int y,int X,int Y){
    assert(x <= X && y <= Y);
    assert(0<=x && x<=w && 0<=X && x <= w);
    assert(0<=y && y<=h && 0<=Y && Y <= h);
    return sum[Y][X] - sum[y][X] - sum[Y][x] + sum[y][x];
  }
};

