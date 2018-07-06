#include<bits/stdc++.h>
using namespace std;

struct SCC{
  int V;
  vector<vector<int> > G,rG;
  vector<int> vs,used,cmp;
  SCC(){}
  SCC(int sz):V(sz),G(sz),rG(sz),used(sz),cmp(sz){}
  void add(int from,int to){
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
  int build(){
    fill(used.begin(),used.end(),0);
    vs.clear();
    for(int v=0;v<V;v++)
      if(!used[v])dfs(v);
    fill(used.begin(),used.end(),0);
    int k=0;
    for(int i=vs.size()-1;i>=0;i--)
      if(!used[vs[i]])rdfs(vs[i],k++);
    return k;
  }
  int be(int x){
    return cmp[x];
  }
  bool same(int x,int y){
    return cmp[x]==cmp[y];
  }
};
int main(){
  int e,n;
  cin>>n>>e;
  SCC S(n);
  while(e--){
    int p1,p2;
    cin>>p1>>p2;
    S.add(p1,p2);
  }
  S.build();
  cin>>e;
  while(e--){
    int p1,p2;
    cin>>p1>>p2;
    if(S.be(p1)==S.be(p2))cout<<1<<endl;
    else cout<<0<<endl;
  }
}