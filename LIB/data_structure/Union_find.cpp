#include<bits/stdc++.h>
using namespace std;
using Int = long long;
//BEGIN CUT HERE
struct UnionFind{
  int n;
  vector<int> ran,p,cnt;
  UnionFind(){}
  UnionFind(int sz):n(sz),ran(sz,1),p(sz,0){iota(p.begin(),p.end(),0);}
  int find(int x){
    return (x==p[x]?x:p[x]=find(p[x]));
  }
  bool same(int x,int y){
    return find(x)==find(y);
  }
  void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(ran[x]<ran[y]) swap(x,y);
    ran[x]+=ran[y];
    p[y]=x;
  }
  int sum(int x){
    return ran[find(x)];
  }
};
//END CUT HERE

signed main(){
  UnionFind U(10);
  while(1){
    for(int i=0;i<10;i++)cout<<i+1<<' '<<U.sum(i)<<endl;
    int a,b;
    cin>>a>>b;
    U.unite(a,b);
  }
}