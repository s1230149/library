#include <bits/stdc++.h>
using namespace std;

class Time{
public:
  chrono::system_clock::time_point start;
  Time(){reset();}
  void reset(){start = now();}
  chrono::system_clock::time_point now(){return chrono::system_clock::now();}
  double time(){return chrono::duration_cast<chrono::milliseconds>(now()-start).count();}
};
