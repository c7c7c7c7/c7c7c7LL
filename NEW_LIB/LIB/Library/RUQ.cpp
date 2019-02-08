#include<bits/stdc++.h>
using namespace std;
  
int t[(1<<18)];
  
void Set(int a,int b,int x,int k=0,int l=0,int r=(1<<17)){
  if(b<=l || r<=a)return;
  if(a<=l && r<=b){
    t[k]=max(t[k],x);
    return;
  }
  int m=(l+r)/2;
  Set(a,b,x,k*2+1,l,m);
  Set(a,b,x,k*2+2,m,r);
}
  
int Get(int i){
  i+=(1<<17)-1;
  int res=t[i];
  while(i){
    i=(i-1)/2;
    res=max(res,t[i]);
  }
  return res;
}
           
int n,q;
int value[100005];
  
int main(){
  value[0]=2147483647;
    
  scanf("%d %d",&n,&q);
  for(int i=1;i<=q;i++){
    int type;
    scanf("%d",&type);
    if(type==0){
      int l,r;
      scanf("%d %d %d",&l,&r,&value[i]);
      r++;
      Set(l,r,i);
    }else{
      int target;
      scanf("%d",&target);
      int ans=Get(target);
      printf("%d\n",value[ans]);
    }
  }
  return 0;
}
