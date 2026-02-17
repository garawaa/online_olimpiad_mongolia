#include <bits/stdc++.h>
using namespace std;

vector<long long> a;
vector<long long> pre, suf;
long long ans;

long long gcd(long long x, long long y) {
    while (y != 0) {
        long long t = y;
        y = x % y;
        x = t;
    }
    return x;
}

void solve(int l, int r, int k) {
    if (r - l < k) {
        return;
    }

    int m = (l + r) / 2;
    pre[m] = a[m];
    for (int i = m + 1; i < m + k && i < r; i++) {
        pre[i] = gcd(pre[i - 1], a[i]);
    }
    suf[m - 1] = a[m - 1];
    for (int i = m - 2; i >= m - k && i >= l; i--) {
        suf[i] = gcd(suf[i + 1], a[i]);
    }
    for (int i = max(m - k, l); i < m && i + k - 1 < r; i++) {
        long long v = gcd(suf[i], pre[i + k - 1]);
        if (v > ans) {
            ans = v;
        }
    }

    solve(l, m, k);
    solve(m, r, k);
}

int main() {
    int n, k;
    cin >> n >> k;
    a.resize(n);
    pre.resize(n);
    suf.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ans = 1;
    solve(0, n, k);

    cout << ans << endl;

    return 0;
}
