#include <bits/stdc++.h>
using namespace std;
int dp[1009][1009];
int main(){
  int n;
  cin>>n;
  while(n--){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    dp[a][b]++;
    dp[a][d]--;
    dp[c][b]--;
    dp[c][d]++;
  }
  int ans=0;
  for(int i=0;i<1009;i++){
    for(int j=1;j<1009;j++){
      dp[i][j]+=dp[i][j-1];
    }
  }
  for(int j=0;j<1009;j++){
    for(int i=1;i<1009;i++){
      dp[i][j]+=dp[i-1][j];
      ans=max(ans,dp[i-1][j]);
    }
  }
  cout<<ans<<endl;
}