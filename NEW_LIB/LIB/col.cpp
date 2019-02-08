#include <bits/stdc++.h>
 
using namespace std;

#define rep(i,n) for (int i=0; i < (n); i++)
typedef double D;      // 座標値の型。doubleかlong doubleを想定
typedef complex<D> P;  // Point
typedef pair<P, P> L;  // Line
typedef vector<P> VP;
const D EPS = 1e-9;    // 許容誤差。問題によって変える
#define X real()
#define Y imag()
#define LE(n,m) ((n) < (m) + EPS)
#define GE(n,m) ((n) + EPS > (m))
#define EQ(n,m) (abs((n)-(m)) < EPS)
 
// 内積　dot(a,b) = |a||b|cosθ
D dot(P a, P b) {return (conj(a)*b).X; }
 
// 外積　cross(a,b) = |a||b|sinθ
D cross(P a, P b) {  return (conj(a)*b).Y;}
 
// 点の進行方向
int ccw(P a, P b, P c) {
  b -= a;  c -= a;
  if (cross(b,c) >  EPS) return +1;  // counter clockwise
  if (cross(b,c) < -EPS) return -1;  // clockwise
  if (dot(b,c)   < -EPS) return +2;  // c--a--b on line
  if (norm(b) < norm(c)) return -2;  // a--b--c on line or a==b
  return 0;                          // a--c--b on line or a==c or b==c
}

bool isparallel(L a,L b){
  return cross(a.first-a.second,b.first-b.second) == 0.0 ;
}
 
/* 交差判定　直線・線分は縮退してはならない。接する場合は交差するとみなす。isecはintersectの略 */
 
// 直線と点
bool isecLP(P a1, P a2, P b) {
  return abs(ccw(a1, a2, b)) != 1;  // return EQ(cross(a2-a1, b-a1), 0); と等価
}
 
// 直線と直線
bool isecLL(P a1, P a2, P b1, P b2) {
  return !isecLP(a2-a1, b2-b1, 0) || isecLP(a1, b1, b2);
}
 
// 直線と線分
bool isecLS(P a1, P a2, P b1, P b2) {
  return cross(a2-a1, b1-a1) * cross(a2-a1, b2-a1) < EPS;
}
 
// 線分と線分
bool isecSS(P a1, P a2, P b1, P b2) {
  return ccw(a1, a2, b1)*ccw(a1, a2, b2) <= 0 &&
         ccw(b1, b2, a1)*ccw(b1, b2, a2) <= 0;
}
 
// 線分と点
bool isecSP(P a1, P a2, P b) {
   return !ccw(a1, a2, b);
   //return abs(a1 - b) + abs(a2 - b) - abs(a2 - a1) < EPS;  //Perfective
}
 
 
/* 距離　各直線・線分は縮退してはならない */
 
// 点pの直線aへの射影点を返す
P proj(P a1, P a2, P p) {
  return a1 + dot(a2-a1, p-a1)/norm(a2-a1) * (a2-a1);
}
 
// 点pの直線aへの反射点を返す
P reflection(P a1, P a2, P p) {
  return 2.0*proj(a1, a2, p) - p;
}
 
D distLP(P a1, P a2, P p) {
  return abs(proj(a1, a2, p) - p);
}
 
D distLL(P a1, P a2, P b1, P b2) {
  return isecLL(a1, a2, b1, b2) ? 0 : distLP(a1, a2, b1);
}
 
D distLS(P a1, P a2, P b1, P b2) {
  return isecLS(a1, a2, b1, b2) ? 0 : min(distLP(a1, a2, b1), distLP(a1, a2, b2));
}
 
D distSP(P a1, P a2, P p) {
  P r = proj(a1, a2, p);
  if (isecSP(a1, a2, r)) return abs(r-p);
  return min(abs(a1-p), abs(a2-p));
}
 
D distSS(P a1, P a2, P b1, P b2) {
  if (isecSS(a1, a2, b1, b2)) return 0;
  return min(min(distSP(a1, a2, b1), distSP(a1, a2, b2)),
             min(distSP(b1, b2, a1), distSP(b1, b2, a2)));
}
 
// 2直線の交点
P crosspointLL(P a1, P a2, P b1, P b2) {
  D d1 = cross(b2-b1, b1-a1);
  D d2 = cross(b2-b1, a2-a1);
  if (EQ(d1, 0) && EQ(d2, 0)) return a1;  // same line
  if (EQ(d2, 0)) throw "kouten ga nai";   // 交点がない
  return a1 + d1/d2 * (a2-a1);
}
 

bool b[50][50];

int main() {

  int n,m;
  D x,y;
  while(cin>>n,n){
  memset(b,0,sizeof(b));
  vector<P>v[50];
  rep(i,n){
    cin>>m;
    rep(j,m){
      cin>>x>>y;
      v[i].push_back(P(x,y));
    }
  }

  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      for(int k=0;k<v[i].size();k++){
        for(int l=0;l<v[j].size();l++){
          P i1=v[i][k];
          P i2=v[i][(k+1)%v[i].size()];
          P j1=v[j][l];
          P j2=v[j][(l+1)%v[j].size()];
          if(!isecSS(i1,i2,j1,j2))continue;
          if(abs(i1-j1)<EPS&&!isecSP(i1,i2,j2))continue;
          if(abs(i2-j1)<EPS&&!isecSP(i1,i2,j2))continue;
          if(abs(j1-i1)<EPS&&!isecSP(j1,j2,i2))continue;
          if(abs(j2-i1)<EPS&&!isecSP(j1,j2,i2))continue;
          if(abs(i1-j2)<EPS&&!isecSP(i1,i2,j1))continue;
          if(abs(i2-j2)<EPS&&!isecSP(i1,i2,j1))continue;
          if(abs(j1-i2)<EPS&&!isecSP(j1,j2,i1))continue;
          if(abs(j2-i2)<EPS&&!isecSP(j1,j2,i1))continue;
          b[i][j]=1;
          b[j][i]=1;
        }
      }
    }
  }
  vector<vector<pair<int, bool> > > clauses;
  rep(i1,n)rep(i2,n)if(b[i1][i2]) {
    int a=i1, b=i2;
    for (int j = 0; j < 4; ++j) {
      vector<pair<int, bool> > clause;
      clause.emplace_back(a, j % 2);
      clause.emplace_back(b, j % 2);
      clause.emplace_back(a + n, j / 2);
      clause.emplace_back(b + n, j / 2);
      clauses.emplace_back(clause);
    }
  }
  SatSolver solver(2 * n, clauses);
  solver.solve();
  set<int>s;
  for (int i = 0; i < n; ++i) {
    s.insert(2 * solver.assigns[i] + solver.assigns[i + n] + 1);
  }cout<<s.size()<<endl;}
}