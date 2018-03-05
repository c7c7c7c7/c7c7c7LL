#include<bits/stdc++.h>
using namespace std;

// semi-open   Range minimum query

struct RBQ{
  int n=(1<<17),data[(1<<18)];
  RBQ(){
    memset(data,0,sizeof(data));
  }
  void update(int k,int x){
    k+=n-1;
    data[k]=x;
    while(k>0){
      k=(k-1)/2;
      data[k]=max(data[k*2+1],data[k*2+2]);
    }
  }
  int find(int a,int b,int k=0,int l=0,int r=(1<<17)){
    if(r<=a || b<=l)return INT_MAX;
    if(a<=l && r<=b)return data[k];
    int v1=find(a,b,k*2+1,l,(l+r)/2);
    int v2=find(a,b,k*2+2,(l+r)/2,r);
    return max(v1,v2);
  }
};


int main(){
  RBQ a;
  int c,x,y,n,q;
  cin>>n>>q;
  for(int i=0;i<q;i++){
    scanf("%d%d%d",&c,&x,&y);
    if(c)cout<<a.find(x,y+1)<<endl;
    else a.update(x,y);
  }
}