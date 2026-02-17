#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
#include <chrono>
#include <random>
#include <functional>

using namespace std;

#define int long long

const int INF = 1e18 + 239;

int n, k, x;

vector<vector<int>> a;

void process(vector<int>& b) {
    {
        int opt = INF;
        for (int i = 0; i < k; i++) {
            opt += x;
            opt = min(opt, b[i]);
            b[i] = min(opt, b[i]);
        }
    }
    {
        int opt = INF;
        for (int i = k - 1; i >= 0; i--) {
            opt += x;
            opt = min(opt, b[i]);
            b[i] = min(opt, b[i]);
        }
    }
}

vector<vector<int>> calc_dp() {
    vector<vector<int>> dp(n + 1, vector<int> (k, INF));
    for (int j = 0; j < k; j++) {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = dp[i - 1][j] + a[i - 1][j];
        }
        process(dp[i]);
    }
    return dp;
}

vector<vector<pair<int, int>>> opt;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k >> x;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    auto dp_down = calc_dp();
    {
        int ans = *min_element(dp_down[n].begin(), dp_down[n].end());
        cout << ans << endl;
    }
    for (int i = 0; i < n - 1 - i; i++) {
        swap(a[i], a[n - 1 - i]);
    }
    auto dp_up = calc_dp();
    for (int i = 0; i < n - 1 - i; i++) {
        swap(a[i], a[n - 1 - i]);
    }
    {
        opt.resize(n);
        for (int i = 0; i < n; i++) {
            int count_down = i;
            int count_up = n - i - 1;
            for (int j = 0; j < k; j++) {
                opt[i].push_back({dp_down[count_down][j] + a[i][j] + dp_up[count_up][j], j});
            }
            sort(opt[i].begin(), opt[i].end());
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int l, t;
        cin >> t >> l;
        t--;
        l--;
        int ans = INF;
        for (auto [cost, lane] : opt[t]) {
            if (lane != l) {
                ans = cost;
                break;
            }
        }
        cout << ans << '\n';
    }
}
