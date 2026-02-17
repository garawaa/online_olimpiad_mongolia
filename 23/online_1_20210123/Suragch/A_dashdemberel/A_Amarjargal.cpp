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

int ans = 0;

int main() {
    FAST
    int n;
    cin >> n;
    vector<vector<int> > G(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        // u--, v--;
        G[u].pb(v);
        G[v].pb(u);
    }
    for(int i = 1; i <= n; i++) {
        if(G[i].size() > 2) {
            ans += G[i].size() - 2;
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