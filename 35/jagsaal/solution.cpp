#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <bitset>
#include <cassert>
#include <tuple>
#include <list>
#include <iterator>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define mt make_tuple

#define forn(i, n) for (int i = 0; i < ((int)(n)); ++i)

vector<pair<int, int> >* graph;
vector<int>* rgraph;

vector<int> topsort;
vector<bool> vis;
void dfs(int u, int k) {
    vis[u] = true;
    for (auto p : graph[u]) {
        int v = p.first;
        if (p.second >= k)
            continue;
        if (!vis[v])
            dfs(v, k);
    }
    topsort.pb(u);
}

int n, m;

bool check(int k) {
    vis.assign(n, false);
    topsort.clear();
    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i, k);
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < n - 1; i++) {
        int v = topsort[i];
        bool found = false;
        for (int j = 0; j < (int)graph[v].size() && !found; j++)
            if (graph[v][j].first == topsort[i + 1] && graph[v][j].second < k)
                found = true;
        if (!found)
            return false;
    }
    return true;
}

int main() {
    // Code here:
   
    scanf("%d %d", &n, &m);
    graph = new vector<pair<int, int> >[n];
    rgraph = new vector<int>[n];
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        graph[x].pb(mp(y, i));
        rgraph[x].pb(y);
    }

    if (!check(m)) {
        printf("-1\n");
        return 0;
    }

    int l = 0, r = m;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);

    return 0;
}

