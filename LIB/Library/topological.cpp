#include<bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
const int MAX = 100000;
const int INF = 1<<29;
vector<int> G[MAX];
list<int> out;
int n;
bool V[MAX];
int indeg[MAX];
void bfs(int s){
  queue<int>q;
  q.push(s);
  V[s]=true;
  while(!q.empty()){
    int u=q.front();q.pop();
    out.push_back(u);
    r(i,G[u].size()){
      int v=G[u][i];
      indeg[v]--;
      if(!indeg[v]&&!V[v]){
        V[v]=true;
        q.push(v);
      }
    }
  }
}
void Tsort(){
  r(u,n)r(i,G[u].size())indeg[G[u][i]]++;
  r(u,n)if(!indeg[u]&&!V[u])bfs(u);
  for(list<int>::iterator it=out.begin();it!=out.end();it++)
    cout<<*it<<endl;
}
//初期化してね♪
int main(){
  int s,t,m;
  cin>>n>>m;
  r(i,m){
    cin>>s>>t;
    G[s].push_back(t);
  }
  Tsort();
}