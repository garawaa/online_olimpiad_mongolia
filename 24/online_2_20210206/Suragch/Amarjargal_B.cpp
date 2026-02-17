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

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<bool> p_sum(1e6 + 1, 0);
    int sum = 0;
    p_sum[0] = 1;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        sum += p[i];
        // cout << "here\n";
        for(int j = sum; j - p[i] >= 0; j--) {
            if(p_sum[j - p[i]]) {
                p_sum[j] = 1;
            }
        }
    }
    int cnt = 0;
    ll ans = 0;
    for(int i = 0; i <= sum; i++) {
        if(p_sum[i]) {
            if(!p_sum[sum - i]) {
                break;
            }
            if(sum != i * 2) {
                ans += (sum + 1) * 2 - 1 - cnt * 4;
            } else {
                ans += sum + 1 - cnt * 2;
            }
            cnt++;
            p_sum[i] = 0;
            // cout << i << " " << ans << "\n";
        }
    }
    cout << ans << "\n";





    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/