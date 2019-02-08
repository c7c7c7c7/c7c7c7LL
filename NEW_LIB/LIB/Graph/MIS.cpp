#include <bits/stdc++.h>
using namespace std;
int MaximumIndependentSet(const int n, const vector<long long> &g) {
	int res = 0;
	function<void (long long, int)> dfs = [&](long long remain, int cnt) {
		for (bool update = true; update; ) {
			update = false;
			for (int i = 0; i < n; i ++) if (remain & (1LL << i)) {
				int deg = __builtin_popcountll(remain & g[i]);
				if (deg <= 1) {
					cnt ++;
					remain &= ~((1LL << i) | g[i]);
					update = true;
				}
			}
		}
		res = max(res, cnt);
		if (remain) {
			int k = __builtin_ctzll(remain);
			dfs(remain & ~(1LL << k), cnt);
			dfs(remain & ~(g[k] | (1LL << k)), cnt + 1);
		}
	};
	dfs((1LL << n) - 1, 0);
	return res;
}
int main() {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<long long> g(n);
        for (int i = 0; i < m; i ++) {
                int a, b;
                scanf("%d%d", &a, &b);
                a --, b --;
                g[a] |= 1LL << b;
                g[b] |= 1LL << a;
        }
        printf("%d\n", MaximumIndependentSet(n, g));
        return 0;
}