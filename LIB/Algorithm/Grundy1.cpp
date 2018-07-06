#include<bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
int dp[100][100];
int Grundy(int h,int w){
  int &g=dp[h][w];
  if(g!=-1)return g;
  if(h==0&&w==0)return g=0;
  set<int>V;
  V.insert(Grundy(0,0));
  for(int i=1;i<h;i++)V.insert(Grundy(i,w));
  for(int i=1;i<w;i++)V.insert(Grundy(h,i));
  g=0;
  while(V.count(g))++g;
  return g;
}
int main(){
  memset(dp,0,sizeof(dp));
}