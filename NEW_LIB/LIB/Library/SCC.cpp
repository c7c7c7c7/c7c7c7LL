#include<bits/stdc++.h>
using namespace std;
#define MAX_V 10000
int V,cmp[MAX_V];
vector<int> G[MAX_V],rG[MAX_V],vs;
bool used[MAX_V];
void addedge(int from,int to){
  G[from].push_back(to);
  rG[to].push_back(from);
} 
void dfs(int v){
  used[v]=1;
  for(int i=0;i<G[v].size();i++)
    if(!used[G[v][i]])dfs(G[v][i]);
  vs.push_back(v);
}
void rdfs(int v,int k){
  used[v]=1;
  cmp[v]=k;
  for(int i=0;i<rG[v].size();i++)
    if(!used[rG[v][i]])rdfs(rG[v][i],k);
}
int scc(){
  memset(used,0,sizeof(used));
  vs.clear();
  for(int v=0;v<V;v++)
    if(!used[v])dfs(v);
  memset(used,0,sizeof(used));
  int k=0;
  for(int i=vs.size()-1;i>=0;i--)
    if(!used[vs[i]])rdfs(vs[i],k++);
  return k;
}
int main(){
  int e;
  cin>>V>>e;
  while(e--){
    int p1,p2;
    cin>>p1>>p2;
    addedge(p1,p2);
  }
  scc();
  cin>>e;
  while(e--){
    int p1,p2;
    cin>>p1>>p2;
    if(cmp[p1]==cmp[p2])cout<<1<<endl;
    else cout<<0<<endl;
  }
}
