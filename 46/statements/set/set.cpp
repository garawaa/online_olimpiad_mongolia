#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

#define ll long long
#define ull unsigned ll
#define ld long double
#define pb push_back
#define mp make_pair
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sqr(x) (x)*(x)
#define db_(x) cout << x << ' ';
#define db(x) cout << x << '\n';cout.flush();
#define fastio ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define X first
#define Y second

void solver() {
    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<pair<ll, int>> b(q);
    vector<ll> c(q);
    for (int i = 0; i < q; ++i) {
        cin >> b[i].X;
        --b[i].X;
        b[i].Y = i;
    }

    sort(all(b));
    ll kex_skiped = 0;
    ll seg_begin = 0;
    int seg_endi = 0;
    for (int i = 0; i < q; ++i) {
        ll d = b[i].X - kex_skiped;
        while (seg_endi < n && seg_begin + d >= a[seg_endi]) {
            ll add = max(0LL, a[seg_endi] - seg_begin);
            kex_skiped += add;
            seg_begin = a[seg_endi] + 1;
            seg_endi++;
            d = b[i].X - kex_skiped;
        }
        c[b[i].Y] = seg_begin + d;
    }

    for (int i = 0; i < q; ++i) {
        cout << c[i] << " ";
    }
}

int main() {
//    fastio;
    solver();
}