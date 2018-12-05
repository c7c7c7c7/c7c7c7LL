#include <bits/stdc++.h>

using namespace std;

struct twoEdgeComponents {
    int n;
    vector<vector<int>> g;             // 入力のグラフ
    vector<int> cmp;                         // 頂点iが属する連結成分
    vector<vector<int>> each_bcc;  // 連結成分iに属する頂点
    vector<pair<int,int>> bridge; // 橋の辺を列挙
    vector<int> order;                       // 頂点iを訪れた順番
    vector<bool> inS;                            // 頂点iがSに存在している
    stack<int> roots, S;                 // 根の候補、訪れた頂点のうちまだ見ていない頂点

    twoEdgeComponents() {}
    twoEdgeComponents(vector<vector<int>> g_) : n(g_.size()), g(g_) {}
    // 辺(p,q)を追加
    void add_edge(int p, int q) {
        g[p].push_back(q);
        g[q].push_back(p);
    }
    // 橋、二重辺連結成分
    void dfs(int cur, int prev, int &k) {
        order[cur] = ++k;
        S.push(cur); inS[cur] = true;
        roots.push(cur);
        for(auto to: g[cur]) {
            if(order[to]==0) dfs(to, cur, k);
            else if(to!=prev && inS[to]) {
                while(order[roots.top()] > order[to]) roots.pop();
            }
        }
        if(cur == roots.top()) {
            if(prev!=-1) bridge.push_back({prev, cur});
            vector<int> bcc;
            while(1) {
                int node = S.top(); S.pop(); inS[node] = false;
                bcc.push_back(node);
                if(node==cur) break;
            }
            each_bcc.push_back(bcc);
            roots.pop();
        }
    }
    // 橋と二重辺連結成分
    void bcc() {
        order.assign(n, 0);
        inS.assign(n, false);
        cmp.assign(n, -1);
        int k = 0;
        for(int i=0; i<n; ++i) {
            if(order[i] == 0) {
                dfs(i, -1, k);
            }
        }
        for(int i=0; i<(int)each_bcc.size(); ++i) {
            for(auto j: each_bcc[i]) {
                cmp[j] = i;
            }
        }
    }
    // 二重編連結成分分解したあとのグラフ（木）を取得
    vector<vector<int>> getbcc() {
        vector<vector<int>> h(each_bcc.size(), vector<int>());
        for(auto i: bridge) {
            int a = cmp[i.first], b = cmp[i.second];
            h[a].push_back(b);
            h[b].push_back(a);
        }
        return h;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for(int i=0; i<n; ++i) cin >> w[i];
    vector<vector<int>> g(n);
    for(int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    twoEdgeComponents graph(g);
    graph.bcc();
    vector<vector<int>> tree = graph.getbcc();
    cout<<tree.size()<<endl;

    vector<int> W(graph.each_bcc.size());
    for(int i=0; i<(int)graph.each_bcc.size(); ++i) {
        for(int j=0; j<(int)graph.each_bcc[i].size(); ++j) {
            W[i] += w[graph.each_bcc[i][j]];
        }
    }

    vector<bool> v(n, false);
    function<bool(int,int)> dfs = [&](int x, int p) {
        bool ret = false;
        if(graph.each_bcc[x].size() >= 2) ret = true;
        for(auto i: tree[x]) {
            if(i == p) continue;
            ret |= dfs(i, x);
        }
        return v[x] = ret;
    };

    dfs(graph.cmp[0], -1);

    int ans = 0;
    for(int i=0; i<(int)graph.each_bcc.size(); ++i) {
        if(v[i]) ans += W[i];
    }

    int tmp = 0;
    vector<int> v2(n, 0);
    function<void(int,int,int)> dfs2 = [&](int x, int p, int cost) {
        if(!v[x]) cost += W[x];
        tmp = max(tmp, cost);
        for(auto i: tree[x]) {
            if(i == p) continue;
            dfs2(i, x, cost);
        }
    };
    dfs2(graph.cmp[0], -1, 0);

    ans += tmp;
    cout << ans << endl;

    return 0;
}