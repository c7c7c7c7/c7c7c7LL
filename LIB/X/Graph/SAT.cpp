#include <bits/stdc++.h>
 
using namespace std;
 
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
 
int main() {
  int v, e;
  cin >> v >> e;
  vector<vector<pair<int, bool>>> clauses;
  for (int i = 0; i < e; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    for (int j = 0; j < 4; ++j) {
      vector<pair<int, bool>> clause;
      clause.emplace_back(a, j % 2);
      clause.emplace_back(b, j % 2);
      clause.emplace_back(a + v, j / 2);
      clause.emplace_back(b + v, j / 2);
      clauses.emplace_back(clause);
    }
  }
  SatSolver solver(2 * v, clauses);
  solver.solve();
  for (int i = 0; i < v; ++i) {
    cout << 2 * solver.assigns[i] + solver.assigns[i + v] + 1 << endl;
  }
}
