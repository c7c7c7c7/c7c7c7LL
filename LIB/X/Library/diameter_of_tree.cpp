#include<bits/stdc++.h>
#define MAX 100000
#define INF 1<<30
using namespace std;
class Edge{
public:
  int t,w;
  Edge(){}
  Edge(int t,int w):t(t),w(w){}
};
vector<Edge>G[MAX];
int n,d[MAX];
bool vis[MAX];
int cnt;

void bfs(int s){
  for(int i=0;i<n;i++)d[i]=INF;
  queue<int>q;
  q.push(s);
  d[s]=0;
  int u;
  while(!q.empty()){
    u=q.front();q.pop();
    for(int i=0;i<G[u].size();i++){
      Edge e=G[u][i];
      if(d[e.t]==INF){
        d[e.t]=d[u]+e.w;
        q.push(e.t);
      }
    }
  }
}
void solve(){
  bfs(0);
  int maxv=0;
  int tgt=0;
  for(int i=0;i<n;i++){
    if(d[i]==INF)continue;
    if(maxv<d[i]){
      maxv=d[i];
      tgt=i;
    }
  }
  bfs(tgt);
  maxv=0;
  for(int i=0;i<n;i++){
    if(d[i]==INF)continue;
    maxv=max(maxv,d[i]);
  }
  cout<<maxv<<endl;
}
int main(){
  int s,t,w;
  cin>>n;
  for(int i=0;i<n-1;i++){
    cin>>s>>t>>w;
    G[s].push_back(Edge(t,w));
    G[t].push_back(Edge(s,w));
  }
  solve();
}