#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ss second
#define ff first
#define pb push_back
#define pii pair<int, int>
#define INF INT_MAX
#define debug(n) cout << #n << " = " << n << "\n";
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;

const ll MOD = 1e9 + 7;

void solve() {
    ll a, b, dis;
    cin >> a >> b;
    dis = b - a;
    vector<ll> cnt(9, 0);
    for(int i = 0; i < 9; i++) {
        cnt[(a % 9 + i) % 9] += (b - a + 1) / 9;
    }
    for(int i = 0; i < (b - a + 1) % 9; i++) {
        cnt[(a % 9 + i) % 9] ++;
    }
    ll ans = cnt[0] * 9;
    for(int i = 1; i < 9; i++) {
        ans += cnt[i] * i;
    }
    cout << ans << "\n";

}

int main() {
    int t ;
    cin >> t;
    while(t--) {
        solve();
    }


    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/