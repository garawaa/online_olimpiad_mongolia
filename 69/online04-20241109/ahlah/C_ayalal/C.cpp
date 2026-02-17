#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,mmx,tune=native")

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <bitset>

#pragma comment(linker, "/STACK:256000000")

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ld;

const int INF = 1000 * 1000 * 1000 + 21;
const ll LLINF = (1ll << 60) + 5;
const int MOD = 1000 * 1000 * 1000 + 7;

const int MAX_N = 23;

int n, group_cnt;
ull s;
ull arr[MAX_N];
int st[MAX_N];
int ed[MAX_N];
ull dp[1 << MAX_N];
bitset<1 << MAX_N> was_zero;

int main() {
#ifdef CH_EGOR
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    //freopen("", "r", stdin);
    //freopen("", "w", stdout);
#endif

    scanf("%d%llu", &group_cnt, &s);
    for (int i = 0; i < group_cnt; ++i) {
        int sz;
        scanf("%d", &sz);
        st[i] = n;
        ed[i] = n + sz;
        for (int j = st[i]; j < ed[i]; ++j) {
            scanf("%llu", &arr[j]);
        }
        n += sz;
    }

    for (int i = 0; i < (1 << n); ++i) {
        dp[i] = LLINF;
    }
    dp[0] = 1;;

    for (int cur = 0, iter = 0; true; ++iter, cur ^= 1) {
        for (int i = 0; i < (1 << n); ++i) {
            if (dp[i] != LLINF) {
                dp[i] = 0;
            } else if (!dp[i]) {
                was_zero[i] = true;
            }
        }

        for (int group_id = 0; group_id < group_cnt; ++group_id) {
            for (int i = (1 << n) - 1; i >= 0; --i) {
                if (dp[i] != LLINF && !was_zero[i]) {
                    for (int j = st[group_id]; j < ed[group_id]; ++j) {
                        if (!((i >> j) & 1)) {
                            if (ull x = dp[i] + arr[j]; x <= s && x < dp[i ^ (1 << j)]) {
                                dp[i ^ (1 << j)] = x;
                            }
                        }
                    }
                }
            }
        }

        if (dp[(1 << n) - 1] != LLINF) {
            return 0 * printf("%d\n", iter + 1);
        }
    }

    assert(false);

    return 0;
}
