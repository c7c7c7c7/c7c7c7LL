#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
#define int long long
using namespace std;
typedef pair<int,int>P;
typedef pair<P,P>P2;

int n,x[30],y[30];

set<P2>s;
map<P2,int>M;

int dfs(int lw,int lh,int rw,int rh,int xx){


  P2 p=P2(P(lw,lh),P(rw,rh));

  if(M.count(p))return M[p];

  if( rw<lw || rh<lh ) return 0; 

  int res= 0;

  r(i,n){
    int X=x[i];
    int Y=y[i];

    if(!(lw<=X&&X<=rw))continue;
    if(!(lh<=Y&&Y<=rh))continue;

    res=max(res,dfs(lw,lh,X-1,Y-1,0)+
                dfs(X+1,lh,rw,Y-1,0)+
                dfs(lw,Y+1,X-1,rh,0)+
                dfs(X+1,Y+1,rw,rh,0)+ ((rw-lw) + (rh-lh) +1)  );
  }

  M[p] = res;

  return res;
}

signed main(){
  int h,w;
  cin>>w>>h>>n;
  r(i,n)cin>>x[i]>>y[i];
  cout<<dfs(1,1,w,h,1)<<endl;
}