#include<bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
class Node{
public:
  int location;
  int p,l,r;
  Node(){}
};
class Point{
public:
  int id,x,y;
  Point(){}
  Point(int id,int x,int y): id(id),x(x),y(y){}
  bool operator < (const Point &p){return id<p.id;}
};
static const int MAX =1000000;
static const int NIL = -1;
int n;
Point P[MAX];
Node T[MAX];
int np;
bool lessX(const Point &p1,const Point &p2){return p1.x<p2.x;}
bool lessY(const Point &p1,const Point &p2){return p1.y<p2.y;}
int makeKDTree(int l,int r, int d){
  if(!(l<r))return NIL;
  int mid=(l+r)/2;
  int t=np++;
  if(d%2==0)sort(P+l,P+r,lessX);
  else sort(P+l,P+r,lessY);
  T[t].location=mid;
  T[t].l=makeKDTree(l,mid,d+1);
  T[t].r=makeKDTree(mid+1,r,d+1);
  return t;
}
void find(int v,int sx,int tx,int sy,int ty,int d,vector<Point> &ans){
  int x=P[T[v].location].x;
  int y=P[T[v].location].y;
  if(sx<=x&&x<=tx&&sy<=y&&y<=ty)ans.push_back(P[T[v].location]);
  if(d%2==0){
    if(T[v].l!=NIL)if(sx<=x)find(T[v].l,sx,tx,sy,ty,d+1,ans);
    if(T[v].r!=NIL)if(x<=tx)find(T[v].r,sx,tx,sy,ty,d+1,ans);
  }
  else{
    if(T[v].l!=NIL)if(sy<=y)find(T[v].l,sx,tx,sy,ty,d+1,ans);
    if(T[v].r!=NIL)if(y<=ty)find(T[v].r,sx,tx,sy,ty,d+1,ans);
  }
}
int main(){
  int x,y;
  cin>>n;
  rep(i,n){
    scanf("%d %d",&x,&y);
    P[i]=Point(i,x,y);
    T[i].l=T[i].r=T[i].p=NIL;
  }
  np=0;
  int root=makeKDTree(0,n,0);
  int q;
  cin>>q;
  int sx,sy,tx,ty;
  vector<Point>ans;
  rep(i,q){
    scanf("%d %d %d %d",&sx,&tx,&sy,&ty);
    ans.clear();
    find(root,sx,tx,sy,ty,0,ans);
    sort(ans.begin(),ans.end());
    rep(j,ans.size())printf("%d\n",ans[j].id);
    cout<<endl;
  }return 0;
}