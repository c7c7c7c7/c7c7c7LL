#include<bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
#define MAX 15
#define INF 1<<28
int n;
int d[MAX][MAX];
int dp[1<<MAX][MAX];
//s=訪問済み,v=現在位置
int rec(int s,int v){
  if(dp[s][v]>=0)return dp[s][v];
  if(s==(1<<n)-1&&v==0)return dp[s][v]=0;
  int res=INF;
  for(int u=0;u<n;u++)
    if(!(s>>u&1))
      res=min(res,rec(s|1<<u,u)+d[v][u]);
  return dp[s][v]=res;
}
int main(){
  memset(dp,-1,sizeof(dp));
  r(i,MAX)r(j,MAX)d[i][j]=INF;
  int m;
  cin>>n>>m;
  while(m--){
    int s,t,dd;
    cin>>s>>t>>dd;
    d[s][t]=dd;
  }
  int p=rec(0,0);
  if(p==INF)p=-1;
  cout<<p<<endl;
}