#include<bits/stdc++.h>
#define N 100005
using namespace std;
typedef pair<int,int>P;
int n,m,s,t,low[N],used[N],depth[N];
vector<int> G[N];
set<P>ans;
void dfs(int x,int d,int prev){
  depth[x]=d;
  for(int i=0;i<G[x].size();i++){
    int nx=G[x][i];
    if(nx==prev)continue;
    if(!used[nx]){
      used[nx]=true;
      dfs(nx,d+1,x);
      if(!low[nx])
      ans.insert(P(min(x,nx),max(x,nx)));
      low[x]+=low[nx];
    }
    else if(d>depth[nx])low[nx]--,low[x]++;
  }
}
int main(){
  cin>>n>>m;
  for(int i=0;i<m;i++){
    cin>>s>>t;
    G[s].push_back(t);
    G[t].push_back(s);
  }
  used[0]=1;
  dfs(0,0,0);
  set<P>::iterator it=ans.begin();
  while(it!=ans.end()){
    cout<<(*it).first<<' '<<(*it).second<<endl;
    it++;
  }
  return 0;
}