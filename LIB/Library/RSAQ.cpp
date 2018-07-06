#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
struct BIT{
  int size;
  vector<ll> dat;
  void init(int n){
    size=n;
    dat.clear();
    dat.resize(n+1);
  }
  void Add(int i,ll x){
    while(0<i&&i<=size){
      dat[i]+=x;
      i+=(i&-i);
    }
  }
  ll Sum(int i){
    ll res=0;
    while(0<i){
      res+=dat[i];
      i-=(i&-i);
    }
    return res;
  }
};
 
 
 
int main(){
  int n,q;
  BIT A,B;
  scanf("%d %d",&n,&q);
  A.init(n);
  B.init(n);
  for(int i=1;i<=q;i++){
    int type;
    ll s,t,value;
    scanf("%d",&type);
    if(type==0){
      //スタート地点＋１
      scanf("%lld %lld %lld",&s,&t,&value);s++;
      A.Add(s,value);
      A.Add(t,-value);
      B.Add(s,-value*(s-1));
      B.Add(t,value*(s-1) + value*(t-s+1) );
    }
    if(type==1){
      scanf("%lld %lld",&s,&t);
      s--;
      printf("%lld\n", A.Sum(t)*t+B.Sum(t) - A.Sum(s)*s-B.Sum(s) );
    }
  }
  return 0;
}
