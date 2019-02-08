#include <bits/stdc++.h>
using namespace std;

string s;

int dp[20][2][2],p;

int dfs(int idx,bool tight=true,bool ok=false){
  if(idx==s.size())return ok;
  int &res=dp[idx][tight][ok];
  if(~res)return res;
  res=0;
  int x=s[idx]-'0';
  int r=(tight?x:9);
  for(int i=0;i<=r;i++){
    bool ret=(ok||(i==4||i==9));
    res+=dfs(idx+1,tight&&i==r,ret);
  }
  return res;
}

int main(){
  memset(dp,-1,sizeof(dp));
  cin>>p;p--;
  s=to_string(p);
  int A=dfs(0);
  memset(dp,-1,sizeof(dp));
  cin>>s;
  int B=dfs(0);
  cout<<B-A<<endl;
}
