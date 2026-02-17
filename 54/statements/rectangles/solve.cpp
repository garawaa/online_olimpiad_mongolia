//
// by Khlytin Grigoriy, 06.11.2022
//

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long int ll;

bool check(ll a, ll b, ll k, ll m, set<pair<ll, ll>> &ans) {
    // =====
    // (A + 1) * (B + 1) = m
    // A + B = k
    // A < a
    // B < b
    // =====
    // (A + 1) * (k - A + 1) = m
    // A * k - A^2 + A + k - A + 1 = m
    // -1 * A^2 + k * A + (k - m + 1) = 0
    // =====
    // (-1) * A^2 + (k) * A + (k - m + 1) = 0
    // =====
    // D = k^2 - 4 * (-1) * (k - m + 1)
    // =====

    ll D = k * k + 4LL * (k - m + 1LL);
    if (D < 0LL) {
        return false;
    }

    ll sqrtD = (ll) sqrt(D);
    if (sqrtD * sqrtD != D) {
        return false;
    }

    if ((k - sqrtD) >= 0LL && (k - sqrtD) % 2LL == 0LL) {
        ll x_1 = (k - sqrtD) / 2LL;
        ll y_1 = k - x_1;
        if (0LL <= x_1 && x_1 < a && 0LL <= y_1 && y_1 < b) {
            ans.insert({x_1, y_1});
        }
    }

    if ((k + sqrtD) >= 0LL && (k + sqrtD) % 2LL == 0LL) {
        ll x_2 = (k + sqrtD) / 2LL;
        ll y_2 = k - x_2;
        if (0LL <= x_2 && x_2 < a && 0LL <= y_2 && y_2 < b) {
            ans.insert({x_2, y_2});
        }
    }

    return (!ans.empty());
}

int main() {
    ll t;
    cin >> t;

    for (ll i = 0LL; i < t; i++) {
        ll a, b, k, m;
        set<pair<ll, ll>> ans;
        cin >> a >> b >> k >> m;
        if (check(a, b, k, m, ans)) {
            pair<ll, ll> p = *ans.begin();
            cout << p.first << " " << p.second << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}
