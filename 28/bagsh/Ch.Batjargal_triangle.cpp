#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, l;
    cin >> n >> l;
    l *= 2;
    vector <int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i] *= 2;
    }
    sort(p.begin(), p.end());
    for (int i = 0; i < n; i++) p.push_back(l + p[i]);
    int v = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        while (v != 2 * n && p[v] < p[i] + l / 2)
            v++;
        int lft = v - i - 1;
        cnt += lft * (lft - 1) / 2;
    }
    int res = n * (n - 1) * (n - 2) / 6 - cnt;
    cout << res << endl;
}
