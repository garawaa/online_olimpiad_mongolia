#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calc(int t, int z, int y, int lim) {
    int cyc = t * z + y;
    int full = lim / cyc;
    int tot = full * z;
    int rem = lim % cyc;
    tot += min(z, rem / t);
    return tot;
}

bool poss(int lim, vector<int> &t, vector<int> &z, vector<int> &y, int m) {
    int s = 0;
    for (int i = 0; i < t.size(); i++) {
        s += calc(t[i], z[i], y[i], lim);
        if (s >= m) return true;
    }
    return false;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> t(n), z(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> z[i] >> y[i];
    }

    int l = 0, r = 1e7, best = r;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (poss(mid, t, z, y, m)) {
            best = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    vector<int> res(n, 0);
    int rem = m;
    for (int i = 0; i < n && rem > 0; i++) {
        int inf = calc(t[i], z[i], y[i], best);
        res[i] = min(inf, rem);
        rem -= res[i];
    }

    cout << best << endl;
    for (int c : res) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
