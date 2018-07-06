#include<bits/stdc++.h>
#define INF 1e17
#define N 1145
#define M 1145
using namespace std;
long long han[N][M];
void dfs(int d){
  if(d==N)return;
  for(int i=1;i<M;i++){
    long long x=INF;
    if(i>=d)for(int j=i-1,p=1;j>=0;j--,p++){
      long long t=han[d-1][p]+han[d][j]*2;
      if(x>=t)x=t;
      else break;
    }
    else x=i*2-1;
    han[d][i]=x;
  }
  dfs(d+1);
}
int main(){
  for(int i=1;i<55;i++)
    han[3][i]=pow(2,i)-1;
  dfs(4);
  int x,y;
  while(cin>>x>>y){
    cout<<han[x][y]<<endl;
  }
}