#include<bits/stdc++.h>
using namespace std;

// 連結成分分解　（連結成分ごとにグラフを再構築、Sはグラフの集合）
struct CC{
  int n;
  vector<vector<int> >G,rG;
  vector<int>used;
  vector<vector<vector<int> > >S;
  CC(int sz):n(sz),G(sz),rG(sz),used(sz){}
  void add(int from,int to){
    G[from].push_back(to);
    rG[to].push_back(from);
  }
  void CC_dfs1(int x,int &cnt,map<int,int>& m){
    m[x]=cnt++;
    used[x]=1;
    for(int i=0;i<G[x].size();i++){
      if(used[G[x][i]])continue;
      CC_dfs1(G[x][i],cnt,m);
    }
    for(int i=0;i<rG[x].size();i++){
      if(used[rG[x][i]])continue;
      CC_dfs1(rG[x][i],cnt,m);
    }
  }
  void CC_dfs2(int x,vector<vector<int> > &v,map<int,int>& m,vector<int> &vis){
    vis[m[x]]=1;
    for(int i=0;i<G[x].size();i++){
      v[m[x]].push_back(m[G[x][i]]);
      if(vis[m[G[x][i]]])continue;
      CC_dfs2(G[x][i],v,m,vis);
    }
    for(int i=0;i<rG[x].size();i++){
      if(vis[m[rG[x][i]]])continue;
      CC_dfs2(rG[x][i],v,m,vis);
    }
  }
  void build(){
    for(int i=0;i<n;i++)used[i]=0;
    for(int i=0;i<n;i++){
      if(used[i])continue;
      int cnt=0;
      map<int,int>M;
      CC_dfs1(i,cnt,M);
      vector<vector<int> >v(cnt);
      vector<int>U(cnt,0);
      CC_dfs2(i,v,M,U);
      S.push_back(v);
    }
  }
};

signed main(){
  int n,m,ans=0;
  cin>>n>>m;
  CC C(n);
  for(int i=0;i<m;i++){
    int a,b;
    cin>>a>>b;a--;b--;
    C.add(a,b);
  }
  C.build();
  int N=C.S.size();
  for(int i=0;i<N;i++,ans++){
    vector<vector<int> >V=C.S[i];
    for(int j=0;j<V.size();j++){
      ans+=V[j].size()-1;
    }
  }
  cout<<ans<<endl;
}
