#include<bits/stdc++.h>
using namespace std;
using Int = long long;
//BEGIN CUT HERE
struct Dice{
  int s[6];
  void roll(char c){
    //the view from above
    // N
    //W E
    // S
    //s[0]:top
    //s[1]:south
    //s[2]:east
    //s[3]:west
    //s[4]:north
    //s[5]:bottom
    int b;
    if(c=='E'){
      b=s[0];
      s[0]=s[3];
      s[3]=s[5];
      s[5]=s[2];
      s[2]=b;
    }
    if(c=='W'){
      b=s[0];
      s[0]=s[2];
      s[2]=s[5];
      s[5]=s[3];
      s[3]=b;
    }
    if(c=='N'){
      b=s[0];
      s[0]=s[1];
      s[1]=s[5];
      s[5]=s[4];
      s[4]=b;
    }
    if(c=='S'){
      b=s[0];
      s[0]=s[4];
      s[4]=s[5];
      s[5]=s[1];
      s[1]=b;
    }
    // migi neji (not verified)
    if(c=='R'){
      b=s[1];
      s[1]=s[3];
      s[3]=s[4];
      s[4]=s[2];
      s[2]=b;
    }
    if(c=='L'){
      b=s[1];
      s[1]=s[2];
      s[2]=s[4];
      s[4]=s[3];
      s[3]=b;
    }
  }
  int top() {
    return s[0];
  }
  int hash(){
    int res=0;
    for(int i=0;i<6;i++) res=res*256+s[i];
    return res;
  }
};
//END CUT HERE

signed main(){
  Dice d;
  for(int i=0;i<6;i++) cin >> d.s[i];
  string s;cin >> s;
  for(int i=0;i<(int)s.size();i++) d.roll(s[i]);
  cout << d.top() << endl;
  return 0;
}