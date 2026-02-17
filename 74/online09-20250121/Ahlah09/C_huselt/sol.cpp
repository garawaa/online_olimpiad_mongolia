#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long double ld;

#define all(v) v.begin(), v.end()
#define len(v) ((int)(v).size())
#define pb push_back
#define kek pop_back
#define pii pair<int, int>
#define pll pair<ll, ll>
#define mp make_pair
// #define int ll


const int INF = (is_same<int, ll>::value ? 3e18l + 666 : 1e9 + 666);
const ll INFll = 3e18l + 666;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

template<class t1, class t2>
inline bool cmin(t1 &a, const t2 &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template<class t1, class t2>
inline bool cmax(t1 &a, const t2 &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

inline int bpow(ll a, ll b, int mod) {
    a %= mod;
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = int(1ll * res * a % mod);
        }
        a *= a;
        a %= mod;
    }
    return res;
}

void run();

// #define TASK "taskname"

signed main() {
#if defined(TASK) && !defined(LOCAL)
    freopen(TASK ".in", "r", stdin);
    freopen(TASK ".out", "w", stdout);
#endif
    iostream::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    run();
}

struct CycleShiftArray {
    vector<int> arr;
    size_t start_pos = 0;

    CycleShiftArray(int n) : arr(n, 0) {}

    int front() const {
        return arr[start_pos];
    }

    void shift() {
        ++start_pos;
        if (start_pos == arr.size()) {
            start_pos = 0;
        }
    }

    void add(uint64_t idx, int val) {
        if (idx >= arr.size()) return;
        idx += start_pos;
        if (idx >= arr.size()) {
            idx -= arr.size();
        }
        arr[idx] += val;
    }
};

struct ShiftMultiset {
    multiset<uint64_t> m;
    uint64_t offset = 0;

    ShiftMultiset() {}

    void shift() {
        ++offset;
    }

    void add(uint64_t val) {
        val -= offset;
        m.insert(val);
    }

    bool remove(uint64_t val) {
        auto it = m.find(val - offset);
        if (it == m.end()) {
            return false;
        }
        m.erase(it);
        return true;
    }
};

uint64_t GetClosestBitflip(uint64_t val, int bit) {
    uint64_t tmp = val & ~((1ull << bit) - 1);
    tmp += (1ull << bit);
    return tmp - val;
}

void run() {
    constexpr int bits = 62;

    int n, q;
    cin >> n >> q;

    vector<CycleShiftArray> v;
    v.reserve(bits);
    for (int i = 0; i < bits; ++i) {
        v.emplace_back(min(1ull << i, 1ull * (q + 1)));
    }
    ShiftMultiset m;
    uint64_t res = 0;

    auto change_v = [bits, &v](uint64_t val, int delta) {
        for (int i = 0; i < bits; ++i) {
            v[i].add(GetClosestBitflip(val, i) - 1, delta);
        }
    };

    auto add = [&m, &res, &change_v](uint64_t val) {
        res ^= val;
        m.add(val);
        change_v(val, 1);
    };

    auto remove = [&m, &res, &change_v](uint64_t val) {
        if (!m.remove(val)) return;
        res ^= val;
        change_v(val, -1);
    };

    auto shift = [bits, &m, &res, &v]() {
        for (int i = 0; i < bits; ++i) {
            if (v[i].front() & 1) {
                res ^= (1ull << i);
            }
            v[i].shift();
        }
        m.shift();
    };

    for (int i = 0; i < n; ++i) {
        uint64_t v;
        cin >> v;
        add(v);
    }

    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            shift();
        } else {
            uint64_t val;
            cin >> val;
            if (t == 2) {
                add(val);
            } else {
                remove(val);
            }
        }
        cout << res << '\n';
    }
}
