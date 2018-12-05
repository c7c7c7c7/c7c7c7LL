#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>P;
struct Bridge{
  int n;
  vector<vector<int> > G;
  vector<int>low,used,depth;
  set<pair<int,int> >ans;
  Bridge(){}
  Bridge(int sz):n(sz),low(sz),used(sz),depth(sz),G(sz){}
  void add(int a,int b){
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void dfs(int x,int d,int prev){
    depth[x]=d;
    for(int i=0;i<G[x].size();i++){
      int nx=G[x][i];
      if(nx==prev)continue;
      if(!used[nx]){
        used[nx]=true;
        dfs(nx,d+1,x);
        if(!low[nx]) ans.insert(P(min(x,nx),max(x,nx)));
        low[x]+=low[nx];
      }
      else if(d>depth[nx])low[nx]--,low[x]++;
    }
  }
  void build(){
    fill(used.begin(),used.end(),0);
    fill(low.begin(),low.end(),0);
    fill(depth.begin(),depth.end(),0);
    used[0]=1;
    dfs(0,0,0);
  }
  void prin(){
    set<P>::iterator it=ans.begin();
    while(it!=ans.end()){
      cout<< (*it).first <<' '<< (*it).second <<endl;
      it++;
    }
  }
};
int main(){
  int n,m,s,t;
  cin>>n>>m;
  Bridge B(n);
  for(int i=0;i<m;i++){
    cin>>s>>t;
    B.add(s,t);
  }
  B.build();
  B.prin();
  return 0;
}