#include<bits/stdc++.h>
using namespace std;

template <typename T> struct WeightedUnionFind{
  int n;
  T d;
  vector<int> r,p;
  vector<T> ws;
  WeightedUnionFind(){}
  WeightedUnionFind(int sz,T d_):
    n(sz),d(d_),r(n,1),p(n),ws(n,d){iota(p.begin(),p.end(),0);}
  int find(int x){
    if(x==p[x]){
      return x;
    }else{
      int t=find(p[x]);
      ws[x]+=ws[p[x]];
      return p[x]=t;
    }
  }
  T weight(int x){
    find(x);
    return ws[x];
  }
  bool same(int x,int y){
    return find(x)==find(y);
  }
  void unite(int x,int y,T w){
    w+=weight(x);
    w-=weight(y);
    x=find(x);y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) swap(x,y),w=-w;
    r[x]+=r[y];
    p[y]=x;
    ws[y]=w;
  }
  T diff(int x,int y){
    return weight(y)-weight(x);
  }
};

signed main(){
  int n,m;
  while(cin>>n>>m,n||m){
    WeightedUnionFind<Int> u(n,0);
    r(i,m){
      char c;
      int x,y;
      cin>>c>>x>>y;
      if(c=='!'){
        cin>>z;
        
      }
    }
  }
  return 0;
}