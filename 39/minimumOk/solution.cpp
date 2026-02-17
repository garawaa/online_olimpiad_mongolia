
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::cerr;

using std::vector;
using std::map;
using std::array;
using std::set;
using std::string;

using std::pair;
using std::make_pair;

using std::tuple;
using std::make_tuple;
using std::get;

using std::min;
using std::abs;
using std::max;

using std::unique;
using std::sort;
using std::generate;
using std::reverse;
using std::min_element;
using std::max_element;

#ifdef LOCAL
#define LASSERT(X) assert(X)
#else
#define LASSERT(X) {}
#endif

template <typename T>
T input() {
    T res;
    cin >> res;
    LASSERT(cin);
    return res;
}

template <typename IT>
void input_seq(IT b, IT e) {
    std::generate(b, e, input<typename std::remove_reference<decltype(*b)>::type>);
}

#define SZ(vec)         int((vec).size())
#define ALL(data)       data.begin(),data.end()
#define RALL(data)      data.rbegin(),data.rend()
#define TYPEMAX(type)   std::numeric_limits<type>::max()
#define TYPEMIN(type)   std::numeric_limits<type>::min()

#define pb push_back
#define eb emplace_back

int main() {
    std::iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // code here
    int n = input<int>();
    int T = input<int>();

    vector<pair<int, int>> in(n);
    for (auto& elem: in)
        cin >> elem.first >> elem.second;

    sort(ALL(in));
    vector<int> tsum(n + 1), psum(n + 1);

    for (int i = 0; i != n; ++i)
        tsum[i + 1] = tsum[i] + in[i].first;

    for (int i = 0; i != n; ++i)
        psum[i + 1] = psum[i] + in[i].second;
    
    vector<int64_t> worst_performance(T + 1, TYPEMAX(int64_t) / 2);
    worst_performance[0] = 0;

    int64_t ans = TYPEMAX(int64_t) / 2;
    for (int i = n - 1; i >= 0; --i) {
        // suppose we don't take item i and take [i - 1 .. 0]

        if (tsum[i] <= T) {
            int rem = T - tsum[i];
            int shit = in[i].first;

            for (int t = 0; t <= rem; ++t)
                if (rem - t < shit)
                    ans = min(ans, psum[i] + worst_performance[t]);
        }

        int64_t w = in[i].first;
        int64_t c = in[i].second;

        for (int t = T; t >= w; --t)
            worst_performance[t] = min(worst_performance[t], worst_performance[t - w] + c);
    }

    if (tsum[n] <= T)
        ans = min<int64_t>(ans, psum[n]);
    
    cout << ans << "\n";
    
    return 0;
}
