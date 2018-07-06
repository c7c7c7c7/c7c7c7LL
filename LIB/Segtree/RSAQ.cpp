#include<bits/stdc++.h>
using namespace std;

#define int long long

struct RSAQ{
  struct BIT{
    int size;
    vector<int> dat;
    BIT(){
      size=(1<<17);
      dat.clear();
      dat.resize((1<<17)+1);
    }
    void Add(int i,int x){
      while(0<i&&i<=size){
        dat[i]+=x;
        i+=(i&-i);
      }
    }
    int Sum(int i){
      int res=0;
      while(0<i){
        res+=dat[i];
        i-=(i&-i);
      }
      return res;
    }
  };
  BIT A,B;
  void add(int l,int r,int v){
    A.Add(l,v);
    A.Add(r-1,-v);
    B.Add(l,-v*(l-1));
    B.Add(r-1,v*(l-1)+v*(r-l));
  }
  int find(int l,int r){ l--; r--;
    return A.Sum(r)*r+B.Sum(r)-A.Sum(l)*l-B.Sum(l);
  }
};

main(){
  RSAQ A;
  int n,q;
  scanf("%lld %lld",&n,&q);
  for(int i=1;i<=q;i++){
    int type;
    int s,t,value;
    scanf("%lld",&type);
    if(type==0){
      scanf("%lld %lld %lld",&s,&t,&value);
      A.add(s,t+1,value);
    }
    if(type==1){
      scanf("%lld %lld",&s,&t);
      cout<<A.find(s,t+1)<<endl;
    }
  }
}