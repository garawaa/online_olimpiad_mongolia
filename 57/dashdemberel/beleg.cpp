#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
typedef long double ld;
typedef long long ll;

const int maxn = 100500;

int n;
unordered_set<int> a[maxn];
vi ord;
int ds[maxn];
int total;

void scan() {
    int t;
    cin >> n >> t;
    forn(i, n) {
        int s;
        cin >> s;
        total += s;
        forn(j, s) {
            int x;
            cin >> x;
            a[i].insert(x);
        }
    }
}

void solve() {
    forn(i, n) ord.push_back(i);
    sort(all(ord), [](int i, int j) {
        return a[i].size() > a[j].size();
    });
    int rem = n;
    for (int i : ord) {
        ds[i] = (total + rem - 1) / rem;
        total -= ds[i];
        --rem;
    }

    vector<tuple<int, int, int>> res;

    int L = 0, R = n-1;
    while (L < R) {
        vi used;
        int l = ord[L], r = ord[R];
        int need = min((int)a[l].size() - ds[l], ds[r] - (int)a[r].size());
        assert(need >= 0);
        if (need) {
            for (int x : a[l]) {
                if (!a[r].count(x)) {
                    a[r].insert(x);
                    used.push_back(x);
                    res.emplace_back(l, r, x);
                    if (--need == 0) {
                        break;
                    }
                }
            }
            for (auto x : used) a[l].erase(x);
        }
        if ((int)a[l].size() == ds[l]) ++L;
        if ((int)a[r].size() == ds[r]) --R;
    }
    cout << res.size() << "\n";
   // for (auto t : res) {
      //  cout << get<0>(t)+1 << " " << get<1>(t)+1 << " " << get<2>(t) << "\n";
  //  }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    scan();
    solve();

#ifdef LOCAL
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
