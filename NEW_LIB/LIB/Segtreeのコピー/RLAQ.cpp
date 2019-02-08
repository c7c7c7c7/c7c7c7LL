#include <bits/stdc++.h>
using namespace std;

struct RLAQ{
  int sst[1<<18];
  int adt[1<<18];
  RLAQ(){
    fill(sst,sst+(1<<18),0);
    fill(adt,adt+(1<<18),0);
  }
  void add(int p, int q, int x, int k=0, int l=0, int r=(1<<17)){
    if(r <= p || q <= l) return;
    if(p <= l && r <= q){
      adt[k] += x;
      return;
    }
    add(p, q, x, 2*k+1, l, (l+r)/2);
    add(p, q, x, 2*k+2, (l+r)/2, r);
    sst[k]=min(sst[2*k+1]+adt[2*k+1],sst[2*k+2]+adt[2*k+2]);
  }
  int find(int p, int q, int k=0, int l=0, int r=(1<<17)){
    if(r <= p || q <= l) return INT_MAX;
    if(p <= l && r <= q) return sst[k]+adt[k];
    int m1, m2;
    m1 = find(p,q,2*k+1,l,(l+r)/2);
    m2 = find(p,q,2*k+2,(l+r)/2,r);
    return min(m1,m2)+adt[k];
  }
};

int main(){
  RLAQ a;
  int c,x,y,n,q;
  cin>>n>>q;
  for(int i=0;i<q;i++){
    cin>>c;
    if(!c){
      cin>>x>>y>>c;
      a.add(x,y+1,c);
    }
    else{
      cin>>x>>y;
      cout<<a.find(x,y+1)<<endl;
    }
  }
}