#include <bits/stdc++.h>
using namespace std;
int par[10001];
int rank[10001];
void init(int n){
  for(int i=0;i<n;i++){
    par[i]=i;
    rank[i]=1;
  }
}
int find(int x){
  if(par[x]==x){
    return x;
  }else{
    return par[x]=find(par[x]);
  }
}
void unit(int x,int y){
  x=find(x);
  y=find(y);
  if(x==y)return;
  if(rank[x]<rank[y]){
    par[x]=y;
  }else{
    par[y]=x;
    if(rank[x]==rank[y])rank[x]++;
  }
}
bool same(int x,int y){
  return find(x)==find(y);
}
struct edge{int u,v,cost;};
bool comp(const edge& e1,const edge& e2){
  return e1.cost<e2.cost;
}
edge es[100001];
int V,E;
int kruskal(){
  sort(es,es+E,comp);
  init(V);
  int res=0;
  for(int i=0;i<E;i++){
    edge e=es[i];
    if(!same(e.u,e.v)){
      unit(e.u,e.v);
      res+=e.cost;
    }
  }
  return res;
}
int main(){
  cin>>V>>E;
  init(V);
  for(int i=0;i<E;i++)
    cin>>es[i].u>>es[i].v>>es[i].cost;
  cout<<kruskal()<<endl;
}
