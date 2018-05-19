#include<bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef pair<int,int>P;

int n,nex,cost;
int dis[100009],ans[100009];
vector<P>v[100009];

void SET(int x,int i){
  nex=v[x][i].first;
  cost=v[x][i].second;
}

void dfs1(int x,int pre){
  r(i,v[x].size()){
    SET(x,i);
    if(nex==pre)continue;
    dfs1(nex,x);
    SET(x,i);
    dis[x]=max(dis[x],dis[nex]+cost);
  }
}

void dfs2(int x,int d_pre,int pre){
  vector<P>child;
  child.push_back(P(0,-1));
  r(i,v[x].size()){
    SET(x,i);
    if(nex==pre)child.push_back(P(d_pre+cost,nex));
    else child.push_back(P(dis[nex]+cost,nex));
  }
  sort(child.begin(),child.end(),greater<P>());
  ans[x]=max(child[0].first,child[1].first);
  r(i,v[x].size()){
    SET(x,i);
    if(nex==pre)continue;
    dfs2(nex,child[nex==child[0].second].first,x);
  }
}

int main(){
  cin>>n;
  r(i,n-1){
    int s,t,w;
    scanf("%d%d%d",&s,&t,&w);
    v[s].push_back(P(t,w));
    v[t].push_back(P(s,w));
  }
  dfs1(0,-1);
  dfs2(0,0,-1);
  r(i,n)cout<<ans[i]<<endl;
}