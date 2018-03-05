#include<bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;

struct BipMatch{
  int n;
  vector<vector<int> > G;
  vector<int> match,used;
  
  BipMatch(){}
  BipMatch(int sz):n(sz),G(sz),match(sz),used(sz){}
  
  void add_edge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
  }

  bool dfs(int v){
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++){
      int u=G[v][i],w=match[u];
      if(w<0||(!used[w]&&dfs(w))){
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }

  int build(){
    int res=0;
    fill(match.begin(),match.end(),-1);
    for(int v=0;v<n;v++){
      if(match[v]<0){
        fill(used.begin(),used.end(),0);
        if(dfs(v)){
          res++;
        }
      }
    }
    return res;
  }
};

int n,a[101][101],a1,a2,a3,p[1001],t[1001],m,m2;

int main(){
while(1){
  r(i,101)r(j,101)a[i][j]=(i==j?0:1e8);
  cin>>n>>m>>m2;
  if(n==0)return 0;
  r(i,m){
    cin>>a1>>a2>>a3;
    a[a2][a1]=a[a1][a2]=a3;
  }
  r(i,m2)cin>>p[i]>>t[i];
  r(k,n)r(i,n)r(j,n)a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
  BipMatch D(m2*2);
  r(i,m2){
    r(j,m2)if(i!=j){
      if(a[p[i]][p[j]]+t[i]<=t[j]){
        D.add_edge(i,j+m2);
      }
    }
  }
  cout<<m2-D.build()<<endl;
}
}