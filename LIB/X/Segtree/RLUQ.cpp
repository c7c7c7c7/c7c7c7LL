#include <bits/stdc++.h>
using namespace std;

struct RLUQ{
  struct query{
    int type;//0=empty, 1=set
    int value;
    query(int a=0,int b=0):type(a),value(b) {}
  };
  query s[(1<<18)];
  int t[(1<<18)];
  RLUQ(){
    fill(t,t+(1<<18),INT_MAX);
  }
  void compute(int k,int l,int r){
    query q=s[k];
    s[k].type=0;
    if(q.type==0||r-l==1)return;
    s[k*2+1]=s[k*2+2]=q;  
    t[k*2+1]=t[k*2+2]=q.value;
  }
  void Set(int a,int b,int x,int k=0,int l=0,int r=(1<<17)){
    if(b<=l || r<=a)return;
    compute(k,l,r);
    if(a<=l && r<=b){
      s[k]=query(1,x);
      t[k]=x;
    }else{
      int m=(l+r)/2;
      Set(a,b,x,k*2+1,l,m);
      Set(a,b,x,k*2+2,m,r);
      t[k]=min(t[k*2+1],t[k*2+2]);
    }
  }
  int Get(int a,int b,int k=0,int l=0,int r=(1<<17)){
    if(b<=l || r<=a)return INT_MAX;
    compute(k,l,r);
    if(a<=l && r<=b){
      return t[k];
    }else{
      int m=(l+r)/2;
      int lv=Get(a,b,k*2+1,l,m);
      int rv=Get(a,b,k*2+2,m,r);
      return min(lv,rv);
    }
  }
};

int main(){
  RLUQ a;
  int n,q;
  cin>>n>>q;
  int c,s,t,x;
  for(int i=0;i<q;i++){
    cin>>c;
    if(c){
      cin>>s>>t;
      cout<<a.Get(s,t+1)<<endl;
    }
    else{
      cin>>s>>t>>x;
      a.Set(s,t+1,x);
    }
  }
}