#include <bits/stdc++.h>
#define long long long int
#define DEBUG
using namespace std;

// @author: pashka

int main() {
    ios::sync_with_stdio(false);

    long n, k;
    cin >> n >> k;
    map<long, long> m;
    m[n] = 1;
    while (k > 0) {
        auto p = *m.rbegin();
        m.erase(p.first);
        if (p.second <= k) {
            m[p.first / 2] += p.second;
            m[(p.first + 1) / 2] += p.second;
            k -= p.second;
        } else {
            m[p.first] = p.second - k;
            m[p.first / 2] += k;
            m[(p.first + 1) / 2] += k;
            k = 0;
        }
    }
    vector<pair<long, long>> a;
    for (auto p : m) {
        a.push_back(p);
    }
    reverse(a.begin(), a.end());
    int q;
    cin >> q;
    while (q--) {
        long t;
        cin >> t;
        t--;
        for (auto p : a) {
            if (t < p.second) {
                cout << p.first << " ";
                break;
            } else {
                t -= p.second;
            }
        }
    }

    return 0;
}