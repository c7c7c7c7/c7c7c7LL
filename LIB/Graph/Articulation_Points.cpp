#include<bits/stdc++.h>
using namespace std;

struct Articulation_Points{
  int n,t;
  vector<int>h,f;
  vector<bool> mark,ans;
  vector<vector<int> >G;
  Articulation_Points(int sz):G(sz),n(sz),mark(sz),ans(sz),h(sz),f(sz){}
  void add(int a,int b){
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void dfs(int v){
    mark[v]=true;
    f[v]=h[v];
    for(int i=0;i<G[v].size();i++){
      int u=G[v][i];
      if(!mark[u]){
        h[u]=h[v]+1;
        dfs(u);
        if(v==0) t++;
        if(v!=0 && f[u]>=h[v])
          ans[v]=true;
        f[v]=min(f[v],f[u]);
      }
      else if(h[u]<h[v]-1) f[v]=min(f[v],h[u]);
    }
  }
  void build(){
    fill(mark.begin(),mark.end(),0);
    fill(ans.begin(),ans.end(),0);
    fill(h.begin(),h.end(),0);
    fill(f.begin(),f.end(),0);
    t=0;
    dfs(0);
    if(t>1)ans[0]=true;
  }
  bool ANS(int x){
    return ans[x];
  }
};
 
int main(){
  int n,m;
  cin>>n>>m;
  Articulation_Points A(n);
  for(int i=0;i<m;i++){
    int v,u;
    cin>>v>>u;
    A.add(v,u);
  }
  A.build();
  for(int i=0;i<n;i++)
    if(A.ANS(i)) cout<<i<<endl;
}