#include <bits/stdc++.h>
#define ff first
#define ss second
#define PB push_back
using namespace std;
using ii = pair<int,int>;
using vi = vector<int>;

const ii N_range = { 1, 300000 };
const int MOD = 1e9+7;

enum {READY, PROCESSING, FINISHED};

bool dfs(int u, int p, const vector<vi> & g, vi & state) {
    if (state[u] != READY)
        return true;
    state[u] = PROCESSING;
    for (int v : g[u]) {
        if (v != p && dfs(v, u, g, state)) {
            return true;
        }
    }
    state[u] = FINISHED;
    return false;
}

bool isTree(const vector<vi> & g) {
    vi state(g.size(), READY);
    if (dfs(1, -1, g, state))
        return false;
    for (int u = 1; u < (int)g.size(); ++u)
        if (state[u] != FINISHED)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    int n;
    assert(cin >> n && "Could not read N");
    vector<vi> g(n+1);
    assert(N_range.ff <= n && n <= N_range.ss && "Invalid value of N");
    assert(cin.get() == '\n' && "Something else than new line follows N");
    for (int i = 1; i < n; ++i) {
        int u, v;
        assert(cin >> u >> v && "Could not read U or V");
        assert(N_range.ff <= u && u <= n && "Invalid value of U");
        assert(N_range.ff <= v && v <= n && "Invalid value of V");
        g[u].PB(v);
        g[v].PB(u);
        assert(cin.get() == '\n' && "Something else than new line follows U and V");
    }
    assert(cin.get() && "Garbage after input");
    assert(isTree(g) && "Given graph is not tree");
    int res = 0;
    for (int u = 1; u < (int)g.size(); ++u)
        res += max((int)g[u].size(), 2) - 2;
    cout << res << endl;
    return 0;
}
