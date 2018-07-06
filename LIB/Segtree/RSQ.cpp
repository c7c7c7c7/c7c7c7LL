#include<bits/stdc++.h>
using namespace std;

// semi-open   Range minimum query

struct RSQ{
  int n=(1<<18),data[(1<<19)];
  RSQ(){
    memset(data,0,sizeof(data));
  }
  // 1 index
  void add(int i,int v){
    while(i<=n){
      data[i]+=v;
      i+=i&-i;
    }
  }
  // 0 index
  void add(int i,int v){
    i++;
    while(i<=n){
      data[i]+=v;
      i+=i&-i;
    }
  }
  int sum(int i){
    int res=0;
    while(i>0){
      res+=data[i];
      i-=i&-i;
    }
    return res;
  }
  //[a,b) 1indexed
  int sum(int x,int y){
    return sum(y-1)-sum(x-1);
  }
  //[a,b) 0indexed
  int sum(int x,int y){
    return sum(y)-sum(x);
  }
  //K番目に小さい値
  int K_number(int k){
    int l = 0,r = (1<<18)+1;
    while( l < r ) {
      int mid = (l+r) / 2;
      if( sum( 1 , mid+1 ) >= k ) r = mid;
      else l = mid+1;
    }
    return l;
  }
  //K番目に大きい値
  int K_L_number(int k){
    int p=sum(1,(1<<18));
    return K_number(p-k+1);
  }
};


int main(){
  RSQ a;
  int c,x,y,n,q;
  cin>>n>>q;
  for(int i=0;i<q;i++){
    scanf("%d%d%d",&c,&x,&y);
    if(c)cout<<a.sum(x,y+1)<<endl;
    else a.add(x,y);
  }
}