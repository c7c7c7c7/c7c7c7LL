#include <bits/stdc++.h>
#define int long long
using namespace std;
main(){
  bitset<64>b(0);
  //cout<<b<<endl;
  //cout<<(~b)<<endl;
  //cout<<(b<<1)<<endl;
  //cout<<(b>>1)<<endl;
  //cout<<(a&b)<<endl;
  //cout<<(a|b)<<endl;
  //cout<<(a^b)<<endl;
  int q,x,y;
  cin>>q;
  while(q--){
    cin>>x;
    if(x<4)cin>>y;
    if(x==0) cout<<b.test(y)<<endl;
    if(x==1) b.set(y);
    if(x==2) b.reset(y);
    if(x==3) b.flip(y);
    if(x==4) cout<<b.all()<<endl;
    if(x==5) cout<<b.any()<<endl;
    if(x==6) cout<<b.none()<<endl;
    if(x==7) cout<<b.count()<<endl;
    if(x==8) cout<<b.to_ullong()<<endl;
  }
}