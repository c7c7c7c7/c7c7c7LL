#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;

int ans,n,m,x,y,z,a[111][111],used[111];


void dfs(int d,int b){cout<<d<<' '<<b<<endl;
  if(d==n){
    int res=0;
    if(b<2)return;
    r(i,b){
      int A=1e9;
      r(j,b)if(i!=j){
        A=min(A,a[used[i]][used[j]]);
      }
      res+=A;
    }
    ans=max(ans,res);
    return;
  }
  int f=1;
  r(i,b)if(a[d][used[i]]==0)f=0;
  if(f){
    used[b]=d;
    dfs(d+1,b+1);
  }
  dfs(d+1,b);
}

int main(){
  cin>>n>>m;
  r(i,m){
    cin>>x>>y;
    x--;y--;
    a[x][y]=a[y][x]=1;
  }
  dfs(0,0);
  cout<<ans<<endl;
}