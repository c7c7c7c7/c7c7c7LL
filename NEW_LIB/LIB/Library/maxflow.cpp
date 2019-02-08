#include<bits/stdc++.h>
#define MAX_V 100000
#define INF 1<<29
using namespace std;
struct edge{int to,cap,rev;};
vector<edge>G[MAX_V];
int level[MAX_V];
int iter[MAX_V];
void add_edge(int from,int to,int cap){
  G[from].push_back((edge){to,cap,G[to].size()});
  G[to].push_back((edge){from,0,G[from].size()-1});
}
void bfs(int s){
  memset(level,-1,sizeof(level));
  queue<int>q;
  level[s]=0;
  q.push(s);
  while(!q.empty()){
    int v=q.front();q.pop();
    for(int i=0;i<G[v].size();i++){
      edge &e=G[v][i];
      if(e.cap>0&&level[e.to]<0){
        level[e.to]=level[v]+1;
        q.push(e.to);
      }
    }
  }
}
int dfs(int v,int t,int f){
  if(v==t)return f;
  for(int &i=iter[v];i<G[v].size();i++){
    edge &e=G[v][i];
    if(e.cap>0&&level[v]<level[e.to]){
      int d=dfs(e.to,t,min(f,e.cap));
      if(d>0){
        e.cap-=d;
        G[e.to][e.rev].cap+=d;
        return d;
      }
    }
  }
  return 0;
}
int max_flow(int s,int t){
  int flow=0;
  while(1){
    bfs(s);
    if(level[t]<0)return flow;
    memset(iter,0,sizeof(iter));
    int f;
    while((f=dfs(s,t,INF))>0){
      flow+=f;
    }
  }
}
int main(){
  int n,m;
  cin>>n>>m;
  while(m--){
    int a,b,c;
    cin>>a>>b>>c;
    add_edge(a,b,c);
  }
  cout<<max_flow(0,n-1)<<endl;
}