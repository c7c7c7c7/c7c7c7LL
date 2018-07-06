#include<bits/stdc++.h>
using namespace std;
struct TSP{
  int n,d[16][16],dp[(1<<16)][16];
  TSP(int sz):n(sz){
    for(int i=0;i<16;i++)
      for(int j=0;j<16;j++) d[i][j]=1e8;
  }
  void add(int a,int b,int c){
    d[a][b] = c;
    //d[b][a] = c;
  }
  int solve(){
    for(int i=0;i<(1<<n);i++)
      for(int j=0;j<n;j++) dp[i][j]=1e8;
    dp[0][0]=0;
    for(int i=0;i<(1<<n);i++){
      for(int j=0;j<n;j++){
        if(!((1<<j)&i)){
          for(int k=0;k<n;k++){
            dp[i|(1<<j)][j]=min(dp[i|(1<<j)][j],dp[i][k]+d[k][j]);
          }
        }
      }
    }
    if(dp[(1<<n)-1][0]==1e8)return -1;
    return dp[(1<<n)-1][0];
  }
};
int main(){
  int n,m;
  cin>>n>>m;
  TSP T(n);
  for(int i=0;i<m;i++){
    int x,y,z;
    cin>>x>>y>>z;
    T.add(x,y,z);
  }
  cout<<T.solve()<<endl;
}