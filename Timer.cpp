#include <bits/stdc++.h>
using namespace std;

class Timer{
public:
  chrono::system_clock::time_point start;
  Timer(){reset();}
  inline void reset(){start = now();}
  chrono::system_clock::time_point now(){return chrono::system_clock::now();}
  inline int get(){return chrono::duration_cast<chrono::milliseconds>(now()-start).count();} //ms
  friend ostream& operator << (ostream& os,Timer &t){return os<<t.get()<<"[ms]";}
};





void test(){
  int counter1 = 0;
  int counter2 = 0;
  {
    clock_t start = clock();

    while(((double)clock() - start)/CLOCKS_PER_SEC * 1000.0 < 3000) counter1++;
    cout<<"counter1="<<counter1<<endl;
  }
  {
    Timer timer;

    while(timer.get() <= 3000) counter2++;
    cout<<"counter2="<<counter2<<endl;
    cout<<timer<<endl;
  }

  cout<<((double)counter2 / counter1)<<endl;
}

int main(){
  test();
  return 0;
}
