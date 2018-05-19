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
 
struct Initializer {
  Initializer() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout << fixed << setprecision(15);
  }
} initializer;
 
class SatSolver {
 private:
  vector<vector<pair<int, bool>>> cl;
  map<pair<int, bool>, vector<int>> w;
  vector<int> reason, level, que, activity;
  int n, qi;
 
  void enqueue(int v, bool a, int r = -1) {
    assigns[v] = a;
    reason[v] = r;
    level[v] = (que.empty() ? 1 : level[que.back()]);
    que.emplace_back(v);
  }
 
  void add(const vector<pair<int, bool>> &clause) {
    for (auto l : clause) w[l].emplace_back(cl.size());
    cl.emplace_back(clause);
  }
 
  void analyze(int confl) {
    int i = que.size(), lv = 1;
    unordered_set<int> used;
    vector<pair<int, bool>> learnt;
    for (int cnt = 0; cnt || used.empty(); --cnt) {
      for (auto q : cl[confl]) {
        if (!used.emplace(q.first).second) continue;
        activity[q.first] += 1e5;
        if (level[q.first] == level[que.back()]) {
          ++cnt;
        } else {
          learnt.emplace_back(q);
          lv = max(lv, level[q.first]);
        }
      }
      while (!used.count(que[--i]));
      confl = reason[que[i]];
    }
    learnt.emplace_back(que[i], !assigns[que[i]]);
    for (; !que.empty() && level[que.back()] > lv; que.pop_back()) level[que.back()] = 0;
    qi = que.size();
    enqueue(learnt.back().first, learnt.back().second, cl.size());
    add(learnt);
  }
 
  int propagate() {
    for (; qi < int(que.size()); ++qi) {
      for (int cr : w[make_pair(que[qi], !assigns[que[qi]])]) {
        int undef = -1;
        for (int i = 0; i < int(cl[cr].size()); ++i) {
          if (level[cl[cr][i].first] == 0) {
            if (undef != -1) goto next;
            undef = i;
          } else if (assigns[cl[cr][i].first] == cl[cr][i].second) {
            swap(cl[cr][i], cl[cr][0]);
            goto next;
          }
        }
        if (undef == -1) return cr;
        enqueue(cl[cr][undef].first, cl[cr][undef].second, cr);
     next:;
      }
    }
    return -1;
  }
 
 public:
  vector<bool> assigns;
 
  SatSolver(int n, const vector<vector<pair<int, bool>>>& clauses) :
      reason(n), level(n), activity(n), n(n), qi(0), assigns(n) {
    for (const auto& clause : clauses) add(clause);
  }
 
  bool solve() {
    while (true) {
      int confl = propagate();
      if (confl != -1) {
        if (level[que.back()] == 1u) return false;
        for (auto& a : activity) a /= 1.05;
        analyze(confl);
      } else {
        int k = -1;
        for (int i = 0; i < n; ++i) {
          if (level[i] == 0 && (k == -1 || activity[k] < activity[i])) k = i;
        }
        if (k == -1) return true;
        enqueue(k, assigns[k]);
        ++level[k];
      }
    }
  }
};

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