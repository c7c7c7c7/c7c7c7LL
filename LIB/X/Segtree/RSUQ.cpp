#include <bits/stdc++.h>
using namespace std;
 
using VS = vector<string>;    using LL = long long;
using VI = vector<int>;       using VVI = vector<VI>;
using VL = vector<LL>;        using VVL = vector<VL>;
 
#define SZ(a) int((a).size())
#define FOR(i, s, e) for (int(i) = (s); (i) < (e); (i)++)
#define debug(x) cou << #x << ": " << x << endl
 
#define int long long
 
/*--------------------
Lazy Segment Tree
再帰&非Node,Lazy実装
--------------------*/
typedef long long ll;
struct LazySegTree {
 
  int N;
  vector<int> dat;
  vector<int> lazy;
 
  const int NIL = 1010101010; //lazyの空命令を記す値 全部の値があり得るなら更新フラグを別で持たせる
  inline int merge(int a, int b) { return a + b; } //Monoid
  const int INIT_VAL = 0;
 
 
  void lazy_push(ll k, ll queryL, ll queryR) {
    LL ren = queryR - queryL;
    if (lazy[k] == NIL)return;
    dat[k] = lazy[k] * ren; // 幅分だけの値になる
    if (k < N - 1) {
      lazy[2 * k + 1] = lazy[k];
      lazy[2 * k + 2] = lazy[k];
    }
    lazy[k] = NIL;
  }
 
  inline void fix(ll k) { // ノードkに対応する　値に修正
    dat[k] = merge(dat[k * 2 + 1], dat[k * 2 + 2]);
  }
  void lazy_set(ll k, ll val) { //ノードに一致したとき遅延値を置くだけの操作、処理はlazy_pushに任せる
    lazy[k] = val;
  }
 
  //--------------setting--------------//
 
 
  LazySegTree(int _N) {
    N = 1;
    while (N < _N)N *= 2;
    dat = vector<int>(N * 2 - 1, INIT_VAL);
    lazy = vector<int>(N * 2 - 1, NIL);
  }
 
  LazySegTree(vector<int>& a, int _N) {
    N = 1;
    while (N < _N)N *= 2;
    dat = vector<int>(N * 2 - 1, INIT_VAL);
    for (int i = 0; i < _N; ++i)dat[i + N - 1] = a[i];
    build();
  }
  void build() { for (int i = N - 2; i >= 0; i--) dat[i] = merge(dat[2 * i + 1], dat[2 * i + 2]); }
 
  ~LazySegTree() { vector<int>().swap(dat); vector<int>().swap(lazy); }
 
  // set後にbuild()
  void set(int k, int val) {
    dat[k + N - 1] = val;
  }
 
  inline void lazy_update(ll queryL, ll queryR, ll val, ll k = 0, ll nodeL = 0, ll nodeR = -1) {
    if (nodeR == -1)nodeR = N;
    lazy_push(k, nodeL, nodeR);
 
    if (nodeR <= queryL || queryR <= nodeL) { return; }
    if (queryL <= nodeL && nodeR <= queryR) {
      lazy_set(k, val);
      lazy_push(k, nodeL, nodeR);
      return;
    }
 
    ll nodeM = (nodeL + nodeR) / 2;
    lazy_update(queryL, queryR, val, k * 2 + 1, nodeL, nodeM);
    lazy_update(queryL, queryR, val, k * 2 + 2, nodeM, nodeR);
 
    fix(k);
    return;
  }
  inline ll query(ll queryL, ll queryR, ll k, ll nodeL, ll nodeR) {
 
    lazy_push(k, nodeL, nodeR);
 
    if (nodeR <= queryL || queryR <= nodeL) { return 0; }
    if (queryL <= nodeL && nodeR <= queryR) { return dat[k]; }
 
    ll nodeM = (nodeL + nodeR) / 2;
    ll vl = query(queryL, queryR, k * 2 + 1, nodeL, nodeM);
    ll vr = query(queryL, queryR, k * 2 + 2, nodeM, nodeR);
    //fix(k); // いらん(はず)
    return merge(vr, vl);
  }
  inline int query(int a, int b) {
    return query(a, b, 0, 0, N);
  }
};
 
 
#include <time.h>
 
inline void InitRand()
{
  srand((unsigned int)time(NULL));
}
 
long long myrand() {
  return abs(rand() * rand() + 2311 * rand() + 1992);
}
 
 
signed main() {
 
  LL N; // N =100000
  cin>>N;
  LazySegTree seg(N);
 
  vector<int> a(N, 0);
  InitRand();
  int Q; //Q = 100000

  cin>>Q;
 
  FOR(i, 0, Q) {
    int q; scanf("%lld",&q);
    if (q == 0) {
      int L, R, val; scanf("%lld%lld%lld",&L,&R,&val);

      seg.lazy_update(L, R + 1, val); // seg
    }
    else {
      int L, R; scanf("%lld%lld",&L,&R);
      int sum = 0;

      printf("%lld\n",seg.query(L, R + 1));
      //assert(sum == seg.query(L, R + 1));
    }

  }
 
  return 0;
}
