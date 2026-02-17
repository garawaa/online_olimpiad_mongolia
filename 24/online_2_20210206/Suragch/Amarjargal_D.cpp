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

vector<vector<int> > p(4, vector<int> (4, 0));
int main() {
    // FAST
    string s, t;
    cin >> s >> t;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        if(s[i] != t[i]) {
            p[s[i] - 'A'][t[i] - 'A']++;
        }
    }
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mn = min(p[i][j], p[j][i]);
            ans += mn;
            p[i][j] -= mn;
            p[j][i] -= mn;
        }
    }
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j++) {
            for(int l = 0; l < 4; l++) {
                int mn = p[i][j];
                mn = min(mn, p[j][l]);
                mn = min(mn, p[l][i]);
                p[i][j] -= mn;
                p[j][l] -= mn;
                p[l][i] -= mn;
                ans += mn * 2;
            }
        }
    }
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j++) {
            for(int l = 0; l < 4; l++) {
                for(int k = 0; k < 4; k++) {
                    int mn = p[i][j];
                    mn = min(mn, p[j][l]);
                    mn = min(mn, p[l][k]);
                    mn = min(mn, p[k][i]);
                    p[i][j] -= mn;
                    p[j][l] -= mn;
                    p[l][k] -= mn;
                    p[k][i] -= mn;
                    ans += mn * 3;
                }
            }
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