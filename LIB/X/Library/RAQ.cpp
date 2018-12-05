#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
int bit[MAX];
  
void Add(int i,int x){
  while(i){
    bit[i]+=x;
    i-=(i&-i);
  }
}
  
int Get(int i){
  int res=0;
  while(i<MAX){
    res+=bit[i];
    i+=(i&-i);
  }
  return res;
}
  
int n,q;
  
int main(){
  scanf("%d %d",&n,&q);
  while(q--){
    int type;
    scanf("%d",&type);
    if(type==0){
      int l,r,x;
      scanf("%d %d %d",&l,&r,&x);
      Add(r,x);
      Add(l-1,-x);
    }else{
      int target;
      scanf("%d",&target);
      printf("%d\n",Get(target));
    }
  }
  return 0;
}
