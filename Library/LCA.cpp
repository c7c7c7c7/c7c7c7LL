#include<bits/stdc++.h>
using namespace std;
#define MAX 100000
#define MAX_LOG 30
vector<int>G[MAX];
int depth[MAX];
int parent[MAX_LOG][MAX];
int root;
void dfs(int v,int p,int d){
  parent[0][v]=p;
  depth[v]=d;
  for(int i=0;i<G[v].size();i++)
    if(G[v][i]!=p)dfs(G[v][i],v,d+1);
}
void init(int V){
  //parent??¨dfs??????????????????
  dfs(root,-1,0);
  //parent??????????????????
  for(int k=0;k+1<MAX_LOG;k++)
    for(int v=0;v<V;v++)
      if(parent[k][v]<0)parent[k+1][v]=-1;
      else parent[k+1][v]=parent[k][parent[k][v]];
}
int lca(int u,int v){
  if(depth[u]>depth[v])swap(u,v);
  for(int k=0;k<MAX_LOG;k++)
    if((depth[v]-depth[u])>>k&1)
      v=parent[k][v];
  if(u==v)return u;
  for(int k=MAX_LOG-1;k>=0;k--)
    if(parent[k][u]!=parent[k][v]){
    u=parent[k][u];
    v=parent[k][v];
  }
  return parent[0][u];
}
int main(){
  root=0;
  int n;
  cin>>n;
  for(int i=0;i<n;i++){
    int p=0;
    cin>>p;
    while(p--){
      int t;
      cin>>t;
      G[i].push_back(t);
    }
  }
  init(n);
  int p;
  cin>>p;
  while(p--){
    int q,w;
    cin>>q>>w;
    cout<<lca(q,w)<<endl;
  }
}
